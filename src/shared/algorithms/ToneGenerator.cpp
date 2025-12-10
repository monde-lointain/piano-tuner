#include "simple_tuner/algorithms/ToneGenerator.h"

namespace simple_tuner {

void ToneGenerator::set_frequency(double frequency_hz) noexcept {
  frequency_ = frequency_hz;
}

void ToneGenerator::generate_samples(float* buffer, std::size_t num_samples,
                                     double sample_rate) noexcept {
  // Stub: Phase 4 implementation (sine wave generation)
  (void)buffer;
  (void)num_samples;
  (void)sample_rate;
}

}  // namespace simple_tuner
