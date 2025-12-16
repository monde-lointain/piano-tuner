#include "simple_tuner/controllers/PitchDetectionController.h"

#include <algorithm>
#include <cstring>

#include "simple_tuner/algorithms/PitchDetector.h"

namespace simple_tuner {

PitchDetectionController::PitchDetectionController(std::size_t buffer_size,
                                                   double sample_rate)
    : fast_detector_(std::make_unique<PitchDetector>(sample_rate, 512)),
      medium_detector_(std::make_unique<PitchDetector>(sample_rate, 1024)),
      full_detector_(std::make_unique<PitchDetector>(sample_rate, buffer_size)),
      accumulation_buffer_(buffer_size, 0.0f),
      fast_buffer_(512, 0.0f),
      medium_buffer_(1024, 0.0f),
      full_buffer_(buffer_size, 0.0f),
      write_index_(0),
      buffer_size_(buffer_size),
      samples_since_detection_(0),
      previous_energy_(0.0),
      latest_frequency_(0.0),
      latest_confidence_(0.0),
      has_valid_result_(false),
      confidence_threshold_(0.5),
      sample_rate_(sample_rate) {
  // Configure detection tiers
  // Fast: 512 samples, ~86Hz min (E2), 128-sample hop (~3ms @ 48kHz)
  tiers_.push_back({512, 128, 86.0});
  // Medium: 1024 samples, ~43Hz min (F#1), 256-sample hop (~6ms @ 48kHz)
  tiers_.push_back({1024, 256, 43.0});
  // Full: 4096 samples, 32.7Hz min (C1), 1024-sample hop (~23ms @ 48kHz)
  tiers_.push_back({buffer_size, 1024, 32.7});
}

PitchDetectionController::~PitchDetectionController() = default;

void PitchDetectionController::process_audio(const float* samples,
                                             std::size_t num_samples) noexcept {
  if (samples == nullptr || num_samples == 0) {
    return;
  }

  // Copy samples into circular buffer
  for (std::size_t i = 0; i < num_samples; ++i) {
    accumulation_buffer_[write_index_] = samples[i];
    write_index_ = (write_index_ + 1) % buffer_size_;
  }

  samples_since_detection_ += num_samples;

  // Phase 2: Onset detection - force immediate detection on energy spike
  double current_energy = calculate_energy(samples, num_samples);
  bool onset_detected = current_energy > previous_energy_ * kOnsetThreshold;
  previous_energy_ = current_energy;

  // Run detection on onset or when minimum hop interval reached
  bool should_detect =
      onset_detected || (samples_since_detection_ >= tiers_[0].hop_size);

  if (should_detect) {
    samples_since_detection_ = 0;
    run_tiered_detection();
  }
}

void PitchDetectionController::run_tiered_detection() noexcept {
  // Phase 1: Try fast tier first (512 samples for C4+)
  linearize_buffer(fast_buffer_, 512);
  auto result = fast_detector_->detect_pitch_detailed(fast_buffer_.data(), 512);

  if (result.is_valid && result.confidence >= confidence_threshold_) {
    latest_frequency_.store(result.frequency, std::memory_order_release);
    latest_confidence_.store(result.confidence, std::memory_order_release);
    has_valid_result_.store(true, std::memory_order_release);
    return;
  }

  // Fast tier failed, try medium tier (1024 samples for C2+)
  linearize_buffer(medium_buffer_, 1024);
  result = medium_detector_->detect_pitch_detailed(medium_buffer_.data(), 1024);

  if (result.is_valid && result.confidence >= confidence_threshold_) {
    latest_frequency_.store(result.frequency, std::memory_order_release);
    latest_confidence_.store(result.confidence, std::memory_order_release);
    has_valid_result_.store(true, std::memory_order_release);
    return;
  }

  // Medium tier failed, use full tier (4096 samples for C1+)
  linearize_buffer(full_buffer_, buffer_size_);
  result =
      full_detector_->detect_pitch_detailed(full_buffer_.data(), buffer_size_);

  if (result.is_valid && result.confidence >= confidence_threshold_) {
    latest_frequency_.store(result.frequency, std::memory_order_release);
    latest_confidence_.store(result.confidence, std::memory_order_release);
    has_valid_result_.store(true, std::memory_order_release);
  } else {
    has_valid_result_.store(false, std::memory_order_release);
  }
}

double PitchDetectionController::calculate_energy(
    const float* samples, std::size_t num_samples) const noexcept {
  if (num_samples == 0) {
    return 0.0;
  }

  double sum = 0.0;
  for (std::size_t i = 0; i < num_samples; ++i) {
    sum += samples[i] * samples[i];
  }
  return sum / static_cast<double>(num_samples);
}

void PitchDetectionController::linearize_buffer(
    std::vector<float>& dest, std::size_t size) const noexcept {
  // Copy most recent 'size' samples from circular buffer to linear buffer
  for (std::size_t i = 0; i < size; ++i) {
    dest[i] = accumulation_buffer_[(write_index_ + buffer_size_ - size + i) %
                                   buffer_size_];
  }
}

bool PitchDetectionController::get_latest_result(
    double& frequency, double& confidence) const noexcept {
  bool valid = has_valid_result_.load(std::memory_order_acquire);
  if (valid) {
    frequency = latest_frequency_.load(std::memory_order_acquire);
    confidence = latest_confidence_.load(std::memory_order_acquire);
  }
  return valid;
}

void PitchDetectionController::set_confidence_threshold(
    double threshold) noexcept {
  confidence_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

double PitchDetectionController::get_confidence_threshold() const noexcept {
  return confidence_threshold_;
}

}  // namespace simple_tuner
