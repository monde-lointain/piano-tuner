#ifndef SIMPLE_TUNER_ALGORITHMS_TONE_GENERATOR_H_
#define SIMPLE_TUNER_ALGORITHMS_TONE_GENERATOR_H_

#include <cstddef>

namespace simple_tuner {

// Stub implementation for Phase 4
class ToneGenerator {
 public:
  ToneGenerator() = default;
  ~ToneGenerator() = default;

  void set_frequency(double frequency_hz) noexcept;
  void generate_samples(float* buffer, std::size_t num_samples,
                        double sample_rate) noexcept;

 private:
  double frequency_;
  double phase_;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_ALGORITHMS_TONE_GENERATOR_H_
