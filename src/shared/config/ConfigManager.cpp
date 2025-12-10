#include "simple_tuner/config/ConfigManager.h"

#include <algorithm>

namespace simple_tuner {

ConfigManager::ConfigManager(std::unique_ptr<IConfigStorage> storage)
    : storage_(std::move(storage)) {}

double ConfigManager::get_reference_pitch() const noexcept {
  auto stored_value = storage_->get_double(kReferencePitchKey);
  if (stored_value.has_value()) {
    // Clamp stored value to valid range (corruption protection)
    return std::clamp(*stored_value, kMinReferencePitch, kMaxReferencePitch);
  }
  return kDefaultReferencePitch;
}

bool ConfigManager::set_reference_pitch(double frequency_hz) noexcept {
  // Clamp to valid range
  double clamped =
      std::clamp(frequency_hz, kMinReferencePitch, kMaxReferencePitch);
  return storage_->set_double(kReferencePitchKey, clamped);
}

bool ConfigManager::reset_reference_pitch() noexcept {
  return storage_->set_double(kReferencePitchKey, kDefaultReferencePitch);
}

}  // namespace simple_tuner
