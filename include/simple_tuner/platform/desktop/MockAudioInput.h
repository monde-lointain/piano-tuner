#ifndef SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_AUDIO_INPUT_H_
#define SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_AUDIO_INPUT_H_

#include <cstddef>

#include "simple_tuner/interfaces/IAudioInput.h"

namespace simple_tuner {

class MockAudioInput : public IAudioInput {
 public:
  explicit MockAudioInput(double sample_rate = 44100.0);
  ~MockAudioInput() override = default;

  bool initialize() noexcept override;
  bool start() noexcept override;
  void stop() noexcept override;
  std::size_t read_samples(float* buffer,
                           std::size_t num_samples) noexcept override;
  double get_sample_rate() const noexcept override;
  bool is_active() const noexcept override;

  // Test control
  void set_test_frequency(double frequency_hz) noexcept;

 private:
  double sample_rate_;
  double test_frequency_ = 440.0;
  double phase_ = 0.0;
  bool active_ = false;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_AUDIO_INPUT_H_
