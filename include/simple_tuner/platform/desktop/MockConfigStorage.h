#ifndef SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_CONFIG_STORAGE_H_
#define SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_CONFIG_STORAGE_H_

#include <optional>
#include <string>
#include <unordered_map>

#include "simple_tuner/interfaces/IConfigStorage.h"

namespace simple_tuner {

class MockConfigStorage : public IConfigStorage {
 public:
  MockConfigStorage() = default;
  ~MockConfigStorage() override = default;

  bool set_double(const std::string& key, double value) noexcept override;
  std::optional<double> get_double(
      const std::string& key) const noexcept override;
  bool remove(const std::string& key) noexcept override;
  void clear() noexcept override;

 private:
  std::unordered_map<std::string, double> storage_;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_CONFIG_STORAGE_H_
