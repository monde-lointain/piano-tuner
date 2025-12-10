#include "simple_tuner/platform/desktop/MockAudioOutput.h"

namespace simple_tuner {

MockAudioOutput::MockAudioOutput(double sample_rate)
    : sample_rate_(sample_rate), active_(false) {}

bool MockAudioOutput::initialize() noexcept { return true; }

bool MockAudioOutput::start() noexcept {
  active_ = true;
  return true;
}

void MockAudioOutput::stop() noexcept { active_ = false; }

std::size_t MockAudioOutput::write_samples(const float* buffer,
                                           std::size_t num_samples) noexcept {
  if (!active_ || buffer == nullptr) {
    return 0;
  }

  captured_samples_.insert(captured_samples_.end(), buffer,
                           buffer + num_samples);
  return num_samples;
}

double MockAudioOutput::get_sample_rate() const noexcept {
  return sample_rate_;
}

bool MockAudioOutput::is_active() const noexcept { return active_; }

const std::vector<float>& MockAudioOutput::get_captured_samples()
    const noexcept {
  return captured_samples_;
}

void MockAudioOutput::clear_captured_samples() noexcept {
  captured_samples_.clear();
}

}  // namespace simple_tuner
