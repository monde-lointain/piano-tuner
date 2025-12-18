#ifndef SIMPLE_TUNER_UI_STATUS_INDICATOR_COMPONENT_H_
#define SIMPLE_TUNER_UI_STATUS_INDICATOR_COMPONENT_H_

#include <juce_gui_basics/juce_gui_basics.h>

namespace simple_tuner {

class StatusIndicatorComponent : public juce::Component {
 public:
  StatusIndicatorComponent();
  ~StatusIndicatorComponent() override = default;

  // Update status based on cents deviation
  void update_status(float cents) noexcept;

  // Show placeholder when no signal detected
  void set_no_signal() noexcept;

  // Component overrides
  void paint(juce::Graphics& g) override;
  void resized() override;

 private:
  enum class Status { kFlat, kInTune, kSharp, kNoSignal };

  Status current_status_;
  juce::String status_text_;

  void update_text() noexcept;
  void draw_wedge_triangle(juce::Graphics& g, float center_x, float center_y,
                           juce::Colour color);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StatusIndicatorComponent)
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_UI_STATUS_INDICATOR_COMPONENT_H_
