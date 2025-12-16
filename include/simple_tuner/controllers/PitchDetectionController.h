#ifndef SIMPLE_TUNER_CONTROLLERS_PITCH_DETECTION_CONTROLLER_H_
#define SIMPLE_TUNER_CONTROLLERS_PITCH_DETECTION_CONTROLLER_H_

#include <atomic>
#include <cstddef>
#include <memory>
#include <vector>

namespace simple_tuner {

class PitchDetector;

// Detection tier for adaptive multi-tier pitch detection
struct DetectionTier {
  std::size_t buffer_size;  // Samples for this tier
  std::size_t hop_size;     // Hop interval in samples
  double min_frequency;     // Minimum detectable frequency for this tier
};

// Thread-safe controller for pitch detection with circular buffer accumulation
// Audio thread writes samples, UI thread reads results atomically
class PitchDetectionController {
 public:
  // buffer_size: Size of accumulation buffer (e.g., 4096)
  // sample_rate: Audio sample rate in Hz
  explicit PitchDetectionController(std::size_t buffer_size,
                                    double sample_rate);
  ~PitchDetectionController();

  // Called from audio thread: accumulates samples and runs detection
  // samples: Input audio samples
  // num_samples: Number of samples (typically 256)
  void process_audio(const float* samples, std::size_t num_samples) noexcept;

  // Called from UI thread: reads latest detection results atomically
  // Returns false if no valid pitch detected
  bool get_latest_result(double& frequency, double& confidence) const noexcept;

  // Configuration
  void set_confidence_threshold(double threshold) noexcept;
  double get_confidence_threshold() const noexcept;

  PitchDetectionController(const PitchDetectionController&) = delete;
  PitchDetectionController& operator=(const PitchDetectionController&) = delete;

 private:
  // Multi-tier detectors
  std::unique_ptr<PitchDetector> fast_detector_;    // 512 samples, C4+
  std::unique_ptr<PitchDetector> medium_detector_;  // 1024 samples, C2+
  std::unique_ptr<PitchDetector> full_detector_;    // 4096 samples, C1+

  // Detection tiers configuration
  std::vector<DetectionTier> tiers_;

  // Circular buffer for sample accumulation
  std::vector<float> accumulation_buffer_;
  std::vector<float> fast_buffer_;    // 512-sample buffer
  std::vector<float> medium_buffer_;  // 1024-sample buffer
  std::vector<float> full_buffer_;    // 4096-sample buffer
  std::size_t write_index_;
  std::size_t buffer_size_;
  std::size_t samples_since_detection_;

  // Onset detection
  double previous_energy_;
  static constexpr double kOnsetThreshold = 3.0;  // 3x energy increase

  // Atomic results for thread-safe communication
  std::atomic<double> latest_frequency_;
  std::atomic<double> latest_confidence_;
  std::atomic<bool> has_valid_result_;

  // Configuration
  double confidence_threshold_;
  double sample_rate_;

  // Helper methods
  void run_tiered_detection() noexcept;
  double calculate_energy(const float* samples,
                          std::size_t num_samples) const noexcept;
  void linearize_buffer(std::vector<float>& dest,
                        std::size_t size) const noexcept;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_CONTROLLERS_PITCH_DETECTION_CONTROLLER_H_
