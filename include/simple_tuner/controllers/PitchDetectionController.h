#ifndef SIMPLE_TUNER_CONTROLLERS_PITCH_DETECTION_CONTROLLER_H_
#define SIMPLE_TUNER_CONTROLLERS_PITCH_DETECTION_CONTROLLER_H_

#include <atomic>
#include <cstddef>
#include <memory>
#include <vector>

namespace simple_tuner {

class PitchDetector;

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
  std::unique_ptr<PitchDetector> detector_;

  // Circular buffer for sample accumulation
  std::vector<float> accumulation_buffer_;
  std::vector<float> detection_buffer_;  // Pre-allocated for audio thread
  std::size_t write_index_;
  std::size_t buffer_size_;
  std::size_t hop_size_;  // 50% overlap
  std::size_t samples_since_detection_;

  // Atomic results for thread-safe communication
  std::atomic<double> latest_frequency_;
  std::atomic<double> latest_confidence_;
  std::atomic<bool> has_valid_result_;

  // Configuration
  double confidence_threshold_;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_CONTROLLERS_PITCH_DETECTION_CONTROLLER_H_
