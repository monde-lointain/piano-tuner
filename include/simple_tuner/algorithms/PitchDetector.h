#ifndef SIMPLE_TUNER_ALGORITHMS_PITCH_DETECTOR_H_
#define SIMPLE_TUNER_ALGORITHMS_PITCH_DETECTOR_H_

#include <cstddef>
#include <vector>

namespace simple_tuner {

// Window types for signal pre-processing
enum class WindowType { kRectangular, kHann, kHamming };

// Pitch detection result with confidence and validity
struct DetectionResult {
  double frequency;   // Detected frequency in Hz (0.0 if invalid)
  double confidence;  // Detection confidence [0.0, 1.0]
  bool is_valid;      // True if detection meets quality thresholds

  DetectionResult() : frequency(0.0), confidence(0.0), is_valid(false) {}
  DetectionResult(double freq, double conf, bool valid)
      : frequency(freq), confidence(conf), is_valid(valid) {}
};

// McLeod Pitch Period Method (MPM) pitch detector
// Thread-safe for audio callbacks (zero allocations in detect methods)
class PitchDetector {
 public:
  // Constructor pre-allocates buffers for given sample rate and buffer size
  // sample_rate: Audio sample rate (typically 44100 or 48000 Hz)
  // buffer_size: Maximum buffer size for detection (default 4096)
  explicit PitchDetector(double sample_rate, std::size_t buffer_size = 4096);

  ~PitchDetector() = default;

  // Simple API: returns detected frequency in Hz, or 0.0 if no pitch detected
  double detect_pitch(const float* samples, std::size_t num_samples) noexcept;

  // Extended API: returns detailed detection result with confidence
  DetectionResult detect_pitch_detailed(const float* samples,
                                        std::size_t num_samples) noexcept;

  // Configuration methods
  void set_threshold_db(double threshold_db) noexcept;
  void set_min_frequency(double min_freq) noexcept;
  void set_max_frequency(double max_freq) noexcept;
  void set_window_type(WindowType type) noexcept;
  void set_base_clarity_threshold(double threshold) noexcept;

  // Getters for configuration
  double get_threshold_db() const noexcept { return threshold_db_; }
  double get_min_frequency() const noexcept { return min_freq_; }
  double get_max_frequency() const noexcept { return max_freq_; }
  WindowType get_window_type() const noexcept { return window_type_; }
  double get_base_clarity_threshold() const noexcept {
    return base_clarity_threshold_;
  }

 private:
  // NSDF computation (Normalized Square Difference Function)
  void compute_nsdf(const float* samples, std::size_t num_samples) noexcept;

  // Find highest clarity peak in NSDF
  int find_highest_clarity_peak() const noexcept;

  // Parabolic interpolation for sub-sample accuracy
  double parabolic_interpolation(int peak_index) const noexcept;

  // Signal validation (RMS threshold check)
  bool validate_signal(const float* samples,
                       std::size_t num_samples) const noexcept;

  // RMS calculation
  double calculate_rms(const float* samples,
                       std::size_t num_samples) const noexcept;

  // Pre-processing helpers
  void compute_window() noexcept;
  void remove_dc_offset(float* samples, std::size_t num_samples) const noexcept;
  void apply_window(float* samples, std::size_t num_samples) const noexcept;

  // Configuration
  double sample_rate_;
  std::size_t buffer_size_;
  double threshold_db_;  // Signal threshold in dB (default -60dB)
  double min_freq_;      // Minimum detectable frequency (default 32.7 Hz, C1)
  double max_freq_;      // Maximum detectable frequency (default 4186 Hz, C8)
  WindowType window_type_;         // Window function type (default Hann)
  double base_clarity_threshold_;  // Base clarity threshold (default 0.01)

  // Lag range for autocorrelation
  int min_lag_;
  int max_lag_;

  // Pre-allocated buffers (avoid audio thread allocations)
  std::vector<double> nsdf_;            // Normalized square difference function
  std::vector<double> autocorr_;        // Autocorrelation values
  std::vector<double> square_sum_;      // Running square sums for normalization
  std::vector<double> window_;          // Pre-computed window coefficients
  mutable std::vector<float> working_;  // Working buffer for pre-processing
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_ALGORITHMS_PITCH_DETECTOR_H_
