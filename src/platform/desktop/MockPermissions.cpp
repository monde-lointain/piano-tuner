#include "simple_tuner/platform/desktop/MockPermissions.h"

namespace simple_tuner {

PermissionStatus MockPermissions::get_microphone_status() const noexcept {
  return PermissionStatus::GRANTED;
}

void MockPermissions::request_microphone_permission(
    void (*callback)(PermissionStatus)) noexcept {
  if (callback != nullptr) {
    callback(PermissionStatus::GRANTED);
  }
}

}  // namespace simple_tuner
