#ifndef SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_PERMISSIONS_H_
#define SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_PERMISSIONS_H_

#include "simple_tuner/interfaces/IPermissions.h"

namespace simple_tuner {

class MockPermissions : public IPermissions {
 public:
  MockPermissions() = default;
  ~MockPermissions() override = default;

  PermissionStatus get_microphone_status() const noexcept override;
  void request_microphone_permission(
      void (*callback)(PermissionStatus)) noexcept override;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_PLATFORM_DESKTOP_MOCK_PERMISSIONS_H_
