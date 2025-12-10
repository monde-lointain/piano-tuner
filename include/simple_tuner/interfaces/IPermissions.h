#ifndef SIMPLE_TUNER_INTERFACES_IPERMISSIONS_H_
#define SIMPLE_TUNER_INTERFACES_IPERMISSIONS_H_

namespace simple_tuner {

enum class PermissionStatus { NOT_DETERMINED, GRANTED, DENIED, RESTRICTED };

class IPermissions {
 public:
  virtual ~IPermissions() = default;

  virtual PermissionStatus get_microphone_status() const noexcept = 0;
  virtual void request_microphone_permission(
      void (*callback)(PermissionStatus)) noexcept = 0;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_INTERFACES_IPERMISSIONS_H_
