#ifndef SIMPLE_TUNER_INTERFACES_ICONFIG_STORAGE_H_
#define SIMPLE_TUNER_INTERFACES_ICONFIG_STORAGE_H_

#include <optional>
#include <string>

namespace simple_tuner {

class IConfigStorage {
 public:
  virtual ~IConfigStorage() = default;

  virtual bool set_double(const std::string& key, double value) noexcept = 0;
  virtual std::optional<double> get_double(
      const std::string& key) const noexcept = 0;
  virtual bool remove(const std::string& key) noexcept = 0;
  virtual void clear() noexcept = 0;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_INTERFACES_ICONFIG_STORAGE_H_
