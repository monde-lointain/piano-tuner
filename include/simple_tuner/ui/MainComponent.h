#ifndef SIMPLE_TUNER_UI_MAIN_COMPONENT_H_
#define SIMPLE_TUNER_UI_MAIN_COMPONENT_H_

#include <memory>

#include "simple_tuner/ui/ModeSelector.h"

#include <juce_gui_basics/juce_gui_basics.h>

namespace simple_tuner {

class PitchDetectionController;
class FrequencyCalculator;
class NoteDisplayComponent;
class TuningMeterComponent;
class StatusIndicatorComponent;

class MainComponent : public juce::Component, private juce::Timer {
 public:
  enum class AppMode { kMeter, kSound };

  explicit MainComponent(std::shared_ptr<FrequencyCalculator> freq_calc);
  ~MainComponent() override;

  void paint(juce::Graphics& g) override;
  void resized() override;

  // Set controller for pitch detection results
  void set_pitch_controller(PitchDetectionController* controller) noexcept;

 private:
  // UI Components
  std::unique_ptr<NoteDisplayComponent> note_display_;
  std::unique_ptr<TuningMeterComponent> tuning_meter_;
  std::unique_ptr<StatusIndicatorComponent> status_indicator_;
  std::unique_ptr<ModeSelector> mode_selector_;
  std::unique_ptr<juce::DrawableButton> settings_button_;

  // Controllers and calculators
  PitchDetectionController* pitch_controller_;
  std::shared_ptr<FrequencyCalculator> frequency_calculator_;

  // State
  AppMode current_mode_;

  // Helpers
  void initialize_ui() noexcept;
  void timerCallback() override;
  void handle_mode_change(ModeSelector::Mode mode) noexcept;
  juce::String format_cents(double cents) const noexcept;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_UI_MAIN_COMPONENT_H_
