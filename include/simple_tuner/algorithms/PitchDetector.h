#ifndef SIMPLE_TUNER_ALGORITHMS_PITCH_DETECTOR_H_
#define SIMPLE_TUNER_ALGORITHMS_PITCH_DETECTOR_H_

#include <cstddef>

namespace simple_tuner {

// Stub implementation for Phase 2
class PitchDetector {
 public:
  PitchDetector() = default;
  ~PitchDetector() = default;

  // Returns detected frequency in Hz, or 0.0 if no pitch detected
  double detect_pitch(const float* samples, std::size_t num_samples,
                      double sample_rate) noexcept;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_ALGORITHMS_PITCH_DETECTOR_H_
