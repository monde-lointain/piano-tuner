#ifndef SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_AUDIO_OUTPUT_H_
#define SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_AUDIO_OUTPUT_H_

#include <cstddef>
#include <vector>

#include "simple_tuner/interfaces/IAudioOutput.h"

namespace simple_tuner {

class MockAudioOutput : public IAudioOutput {
 public:
  explicit MockAudioOutput(double sample_rate = 44100.0);
  ~MockAudioOutput() override = default;

  bool initialize() noexcept override;
  bool start() noexcept override;
  void stop() noexcept override;
  std::size_t write_samples(const float* buffer,
                            std::size_t num_samples) noexcept override;
  double get_sample_rate() const noexcept override;
  bool is_active() const noexcept override;

  // Test access
  const std::vector<float>& get_captured_samples() const noexcept;
  void clear_captured_samples() noexcept;

 private:
  double sample_rate_;
  bool active_ = false;
  std::vector<float> captured_samples_;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_AUDIO_OUTPUT_H_
