#include "simple_tuner/platform/desktop/MockAudioInput.h"

#include <cmath>

namespace simple_tuner {

namespace {
constexpr double kTwoPi = 2.0 * M_PI;
}

MockAudioInput::MockAudioInput(double sample_rate)
    : sample_rate_(sample_rate),
      test_frequency_(440.0),
      phase_(0.0),
      active_(false) {}

bool MockAudioInput::initialize() noexcept { return true; }

bool MockAudioInput::start() noexcept {
  active_ = true;
  phase_ = 0.0;
  return true;
}

void MockAudioInput::stop() noexcept { active_ = false; }

std::size_t MockAudioInput::read_samples(float* buffer,
                                         std::size_t num_samples) noexcept {
  if (!active_ || buffer == nullptr) {
    return 0;
  }

  for (std::size_t i = 0; i < num_samples; ++i) {
    buffer[i] = static_cast<float>(std::sin(phase_));
    phase_ += kTwoPi * test_frequency_ / sample_rate_;

    // Wrap phase to prevent accumulation errors
    if (phase_ >= kTwoPi) {
      phase_ -= kTwoPi;
    }
  }

  return num_samples;
}

double MockAudioInput::get_sample_rate() const noexcept { return sample_rate_; }

bool MockAudioInput::is_active() const noexcept { return active_; }

void MockAudioInput::set_test_frequency(double frequency_hz) noexcept {
  test_frequency_ = frequency_hz;
}

}  // namespace simple_tuner
