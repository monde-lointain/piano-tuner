#ifndef SIMPLE_TUNER_INTERFACES_IAUDIO_OUTPUT_H_
#define SIMPLE_TUNER_INTERFACES_IAUDIO_OUTPUT_H_

#include <cstddef>

namespace simple_tuner {

class IAudioOutput {
 public:
  virtual ~IAudioOutput() = default;

  virtual bool initialize() noexcept = 0;
  virtual bool start() noexcept = 0;
  virtual void stop() noexcept = 0;
  virtual std::size_t write_samples(const float* buffer,
                                    std::size_t num_samples) noexcept = 0;
  virtual double get_sample_rate() const noexcept = 0;
  virtual bool is_active() const noexcept = 0;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_INTERFACES_IAUDIO_OUTPUT_H_
