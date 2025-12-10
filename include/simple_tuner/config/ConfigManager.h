#ifndef SIMPLE_TUNER_CONFIG_CONFIG_MANAGER_H_
#define SIMPLE_TUNER_CONFIG_CONFIG_MANAGER_H_

#include <memory>

#include "simple_tuner/interfaces/IConfigStorage.h"

namespace simple_tuner {

class ConfigManager {
 public:
  explicit ConfigManager(std::unique_ptr<IConfigStorage> storage);
  ~ConfigManager() = default;

  // Reference pitch management
  double get_reference_pitch() const noexcept;
  bool set_reference_pitch(double frequency_hz) noexcept;
  bool reset_reference_pitch() noexcept;

 private:
  static constexpr double kDefaultReferencePitch = 440.0;
  static constexpr double kMinReferencePitch = 410.0;
  static constexpr double kMaxReferencePitch = 480.0;
  static constexpr const char* kReferencePitchKey = "reference_pitch";

  std::unique_ptr<IConfigStorage> storage_;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_CONFIG_CONFIG_MANAGER_H_
