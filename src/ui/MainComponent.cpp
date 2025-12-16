#include "simple_tuner/ui/MainComponent.h"

#include <iomanip>
#include <sstream>

#include "simple_tuner/algorithms/FrequencyCalculator.h"
#include "simple_tuner/controllers/PitchDetectionController.h"

namespace simple_tuner {

MainComponent::MainComponent()
    : pitch_controller_(nullptr),
      frequency_calculator_(std::make_unique<FrequencyCalculator>()) {
  initialize_ui();
  setSize(400, 600);
  startTimerHz(60);  // 60 FPS update rate for lower latency
}

MainComponent::~MainComponent() { stopTimer(); }

void MainComponent::initialize_ui() noexcept {
  try {
    // Mode label (Tuner/Tone Generator)
    mode_label_.setText("Tuner Mode", juce::dontSendNotification);
    mode_label_.setFont(juce::FontOptions(24.0f, juce::Font::bold));
    mode_label_.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(mode_label_);

    // Note display
    note_label_.setText("--", juce::dontSendNotification);
    note_label_.setFont(juce::FontOptions(72.0f, juce::Font::bold));
    note_label_.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(note_label_);

    // Frequency display
    frequency_label_.setText("0 Hz", juce::dontSendNotification);
    frequency_label_.setFont(juce::FontOptions(20.0f));
    frequency_label_.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(frequency_label_);
  } catch (...) {
    DBG("Exception in MainComponent::initialize_ui()");
  }
}

void MainComponent::paint(juce::Graphics& g) {
  try {
    g.fillAll(juce::Colours::darkgrey);

    // Draw title bar background
    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, getWidth(), 60);

    // Draw title text
    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(28.0f, juce::Font::bold));
    g.drawText("SimpleTuner", 0, 0, getWidth(), 60,
               juce::Justification::centred);
  } catch (...) {
    // Suppress paint exceptions
  }
}

void MainComponent::resized() {
  try {
    auto bounds = getLocalBounds();

    // Reserve top 60px for title bar
    bounds.removeFromTop(60);
    bounds.reduce(20, 20);

    // Mode label at top
    mode_label_.setBounds(bounds.removeFromTop(40));
    bounds.removeFromTop(40);  // Spacing

    // Note display in center
    note_label_.setBounds(bounds.removeFromTop(120));
    bounds.removeFromTop(20);  // Spacing

    // Frequency display below note
    frequency_label_.setBounds(bounds.removeFromTop(40));
  } catch (...) {
    DBG("Exception in MainComponent::resized()");
  }
}

void MainComponent::set_pitch_controller(
    PitchDetectionController* controller) noexcept {
  pitch_controller_ = controller;
}

void MainComponent::timerCallback() {
  if (pitch_controller_ == nullptr) {
    return;
  }

  double frequency = 0.0;
  double confidence = 0.0;

  if (pitch_controller_->get_latest_result(frequency, confidence)) {
    update_display(frequency);
  } else {
    // No valid pitch detected
    note_label_.setText("--", juce::dontSendNotification);
    frequency_label_.setText("0.00 Hz", juce::dontSendNotification);
  }
}

void MainComponent::update_display(double frequency) noexcept {
  try {
    // Convert frequency to MIDI note
    int midi_note = frequency_calculator_->frequency_to_midi(frequency);
    std::string note_name = frequency_calculator_->midi_to_note_name(midi_note);
    int octave = frequency_calculator_->midi_to_octave(midi_note);

    // Format note display (e.g., "A4")
    std::ostringstream note_stream;
    note_stream << note_name << octave;
    note_label_.setText(note_stream.str(), juce::dontSendNotification);

    // Format frequency display (e.g., "440.00 Hz")
    std::ostringstream freq_stream;
    freq_stream << std::fixed << std::setprecision(2) << frequency << " Hz";
    frequency_label_.setText(freq_stream.str(), juce::dontSendNotification);
  } catch (...) {
    DBG("Exception in MainComponent::update_display()");
  }
}

}  // namespace simple_tuner
