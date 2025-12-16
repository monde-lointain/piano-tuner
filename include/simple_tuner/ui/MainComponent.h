#ifndef SIMPLE_TUNER_UI_MAIN_COMPONENT_H_
#define SIMPLE_TUNER_UI_MAIN_COMPONENT_H_

#include <juce_gui_basics/juce_gui_basics.h>

namespace simple_tuner {

class PitchDetectionController;
class FrequencyCalculator;

class MainComponent : public juce::Component, private juce::Timer {
 public:
  MainComponent();
  ~MainComponent() override;

  void paint(juce::Graphics& g) override;
  void resized() override;

  // Set controller for pitch detection results
  void set_pitch_controller(PitchDetectionController* controller) noexcept;

 private:
  juce::Label mode_label_;
  juce::Label note_label_;
  juce::Label frequency_label_;

  PitchDetectionController* pitch_controller_;
  std::unique_ptr<FrequencyCalculator> frequency_calculator_;

  void initialize_ui() noexcept;
  void timerCallback() override;
  void update_display(double frequency) noexcept;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_UI_MAIN_COMPONENT_H_
