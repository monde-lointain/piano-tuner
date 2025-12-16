#include "simple_tuner/algorithms/PitchDetector.h"

#include <algorithm>
#include <cmath>
#include <limits>

namespace simple_tuner {

namespace {
// Constants
constexpr double kDefaultThresholdDb = -40.0;
constexpr double kDefaultMinFrequency = 32.7;    // C1
constexpr double kDefaultMaxFrequency = 4186.0;  // C8
constexpr double kClarityThreshold = 0.01;       // Minimum NSDF peak value
constexpr double kEpsilon = 1e-10;               // Numerical stability
}  // namespace

PitchDetector::PitchDetector(double sample_rate, std::size_t buffer_size)
    : sample_rate_(sample_rate),
      buffer_size_(buffer_size),
      threshold_db_(kDefaultThresholdDb),
      min_freq_(kDefaultMinFrequency),
      max_freq_(kDefaultMaxFrequency) {
  // Calculate lag range from frequency limits
  // period = sample_rate / frequency
  // For max frequency (min period): min_lag = sample_rate / max_freq
  // For min frequency (max period): max_lag = sample_rate / min_freq
  max_lag_ = static_cast<int>(sample_rate_ / min_freq_);
  min_lag_ = static_cast<int>(sample_rate_ / max_freq_);

  // Clamp to buffer size
  max_lag_ = std::min(max_lag_, static_cast<int>(buffer_size_) - 1);
  min_lag_ = std::max(min_lag_, 1);

  // Pre-allocate buffers
  nsdf_.resize(max_lag_ + 1, 0.0);
  autocorr_.resize(max_lag_ + 1, 0.0);
  square_sum_.resize(max_lag_ + 1, 0.0);
}

double PitchDetector::detect_pitch(const float* samples,
                                   std::size_t num_samples) noexcept {
  DetectionResult result = detect_pitch_detailed(samples, num_samples);
  return result.frequency;
}

DetectionResult PitchDetector::detect_pitch_detailed(
    const float* samples, std::size_t num_samples) noexcept {
  // Validate input
  if (samples == nullptr || num_samples == 0) {
    return DetectionResult(0.0, 0.0, false);
  }

  // Validate signal strength
  if (!validate_signal(samples, num_samples)) {
    return DetectionResult(0.0, 0.0, false);
  }

  // Compute NSDF
  compute_nsdf(samples, num_samples);

  // Find highest clarity peak
  int peak_index = find_highest_clarity_peak();
  if (peak_index < 0) {
    return DetectionResult(0.0, 0.0, false);
  }

  // Refine peak position with parabolic interpolation
  double refined_period = parabolic_interpolation(peak_index);

  // Convert period to frequency
  double frequency = sample_rate_ / refined_period;

  // Get confidence from NSDF peak value
  double confidence = nsdf_[peak_index];

  return DetectionResult(frequency, confidence, true);
}

void PitchDetector::set_threshold_db(double threshold_db) noexcept {
  threshold_db_ = threshold_db;
}

void PitchDetector::set_min_frequency(double min_freq) noexcept {
  min_freq_ = min_freq;
  max_lag_ = static_cast<int>(sample_rate_ / min_freq_);
  max_lag_ = std::min(max_lag_, static_cast<int>(buffer_size_) - 1);
}

void PitchDetector::set_max_frequency(double max_freq) noexcept {
  max_freq_ = max_freq;
  min_lag_ = static_cast<int>(sample_rate_ / max_freq_);
  min_lag_ = std::max(min_lag_, 1);
}

void PitchDetector::compute_nsdf(const float* samples,
                                 std::size_t num_samples) noexcept {
  const int max_lag = std::min(max_lag_, static_cast<int>(num_samples) - 1);

  // Initialize accumulators
  std::fill(autocorr_.begin(), autocorr_.end(), 0.0);
  std::fill(square_sum_.begin(), square_sum_.end(), 0.0);

  // Compute autocorrelation and square sums for each lag
  for (int lag = 0; lag <= max_lag; ++lag) {
    double r = 0.0;  // Autocorrelation r(tau)
    double m = 0.0;  // Square sum m(tau)

    const std::size_t valid_samples = num_samples - lag;
    for (std::size_t i = 0; i < valid_samples; ++i) {
      const double x_i = samples[i];
      const double x_i_lag = samples[i + lag];
      r += x_i * x_i_lag;
      m += x_i * x_i + x_i_lag * x_i_lag;
    }

    autocorr_[lag] = r;
    square_sum_[lag] = m;
  }

  // Compute NSDF: NSDF(tau) = 2 * r(tau) / m(tau)
  for (int lag = 0; lag <= max_lag; ++lag) {
    if (square_sum_[lag] > kEpsilon) {
      nsdf_[lag] = 2.0 * autocorr_[lag] / square_sum_[lag];
    } else {
      nsdf_[lag] = 0.0;
    }
  }
}

int PitchDetector::find_highest_clarity_peak() const noexcept {
  // MPM algorithm: find the first peak that exceeds the clarity threshold
  // Search from min_lag (skip DC component at lag=0)
  // Ensure we have room for three-point test
  const int start_lag = std::max(min_lag_, 1);
  const int end_lag = std::min(max_lag_, static_cast<int>(nsdf_.size()) - 1);

  // First try to find a local maximum (peak)
  for (int lag = start_lag; lag < end_lag; ++lag) {
    // Three-point local maximum test
    if (nsdf_[lag] > nsdf_[lag - 1] && nsdf_[lag] > nsdf_[lag + 1]) {
      // Return first peak that exceeds clarity threshold
      if (nsdf_[lag] >= kClarityThreshold) {
        return lag;
      }
    }
  }

  // If no peak found (e.g., very low frequencies near buffer limit),
  // find the lag with highest NSDF value in the valid range
  int best_lag = -1;
  double best_nsdf = kClarityThreshold;
  for (int lag = start_lag; lag <= end_lag; ++lag) {
    if (nsdf_[lag] > best_nsdf) {
      best_nsdf = nsdf_[lag];
      best_lag = lag;
    }
  }

  return best_lag;
}

double PitchDetector::parabolic_interpolation(int peak_index) const noexcept {
  // Bounds check - need room for neighbors
  if (peak_index <= 0 || peak_index >= static_cast<int>(nsdf_.size()) - 1) {
    return static_cast<double>(peak_index);
  }

  // Three-point parabolic interpolation
  const double alpha = nsdf_[peak_index - 1];
  const double beta = nsdf_[peak_index];
  const double gamma = nsdf_[peak_index + 1];

  // Calculate parabola vertex offset: delta = (alpha - gamma) / (2 * (alpha -
  // 2*beta + gamma))
  const double denominator = 2.0 * (alpha - 2.0 * beta + gamma);

  // Avoid division by zero or near-zero (flat peak)
  if (std::abs(denominator) < kEpsilon) {
    return static_cast<double>(peak_index);
  }

  const double delta = (alpha - gamma) / denominator;

  // Refined peak position (sub-sample accuracy)
  return static_cast<double>(peak_index) + delta;
}

bool PitchDetector::validate_signal(const float* samples,
                                    std::size_t num_samples) const noexcept {
  const double rms = calculate_rms(samples, num_samples);

  // Convert threshold from dB to linear
  const double threshold_linear = std::pow(10.0, threshold_db_ / 20.0);

  return rms >= threshold_linear;
}

double PitchDetector::calculate_rms(const float* samples,
                                    std::size_t num_samples) const noexcept {
  if (num_samples == 0) {
    return 0.0;
  }

  double sum_squares = 0.0;
  for (std::size_t i = 0; i < num_samples; ++i) {
    sum_squares += samples[i] * samples[i];
  }

  return std::sqrt(sum_squares / static_cast<double>(num_samples));
}

}  // namespace simple_tuner
