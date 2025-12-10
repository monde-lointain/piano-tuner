#include "simple_tuner/platform/desktop/MockConfigStorage.h"

namespace simple_tuner {

bool MockConfigStorage::set_double(const std::string& key,
                                   double value) noexcept {
  storage_[key] = value;
  return true;
}

std::optional<double> MockConfigStorage::get_double(
    const std::string& key) const noexcept {
  auto it = storage_.find(key);
  if (it != storage_.end()) {
    return it->second;
  }
  return std::nullopt;
}

bool MockConfigStorage::remove(const std::string& key) noexcept {
  return storage_.erase(key) > 0;
}

void MockConfigStorage::clear() noexcept { storage_.clear(); }

}  // namespace simple_tuner
