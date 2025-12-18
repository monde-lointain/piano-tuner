#include "simple_tuner/ui/MainComponent.h"

#include <iomanip>
#include <sstream>

#include "simple_tuner/algorithms/FrequencyCalculator.h"
#include "simple_tuner/controllers/PitchDetectionController.h"
#include "simple_tuner/ui/AlertHelpers.h"
#include "simple_tuner/ui/ModeSelector.h"
#include "simple_tuner/ui/NoteDisplayComponent.h"
#include "simple_tuner/ui/StatusIndicatorComponent.h"
#include "simple_tuner/ui/TuningMeterComponent.h"
#include "simple_tuner/ui/UIConstants.h"

namespace simple_tuner {

MainComponent::MainComponent(std::shared_ptr<FrequencyCalculator> freq_calc)
    : pitch_controller_(nullptr),
      frequency_calculator_(std::move(freq_calc)),
      current_mode_(AppMode::kMeter) {
  initialize_ui();
  setSize(400, 600);
  startTimerHz(60);  // 60 FPS update rate for lower latency
}

MainComponent::~MainComponent() { stopTimer(); }

void MainComponent::initialize_ui() noexcept {
  try {
    // Create note display component
    note_display_ =
        std::make_unique<NoteDisplayComponent>(frequency_calculator_);
    addAndMakeVisible(note_display_.get());

    // Create tuning meter component (placeholder for Week 1)
    tuning_meter_ = std::make_unique<TuningMeterComponent>();
    addAndMakeVisible(tuning_meter_.get());

    // Create status indicator component
    status_indicator_ = std::make_unique<StatusIndicatorComponent>();
    addAndMakeVisible(status_indicator_.get());

    // Create mode selector
    mode_selector_ = std::make_unique<ModeSelector>();
    mode_selector_->on_mode_changed = [this](ModeSelector::Mode mode) {
      handle_mode_change(mode);
    };
    addAndMakeVisible(mode_selector_.get());

    // Create settings button
    settings_button_ = std::make_unique<juce::DrawableButton>(
        "Settings", juce::DrawableButton::ImageOnButtonBackground);
    settings_button_->setButtonText("⚙");
    settings_button_->onClick = [this]() {
      show_alert(juce::AlertWindow::InfoIcon, "Settings",
                 "Settings screen coming in Phase 6");
    };
    addAndMakeVisible(settings_button_.get());

    // Cent value label removed per UI requirements

  } catch (...) {
    DBG("Exception in MainComponent::initialize_ui()");
  }
}

void MainComponent::paint(juce::Graphics& g) {
  try {
    g.fillAll(ui::kBackgroundDark);
  } catch (...) {
    // Suppress paint exceptions
  }
}

void MainComponent::resized() {
  try {
    auto bounds = getLocalBounds();

    // Query safe area insets for notches (desktop will return 0)
    juce::BorderSize<int> safe_insets;
    if (auto* display =
            juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()) {
      safe_insets = display->safeAreaInsets;
    }
    bounds = safe_insets.subtractedFrom(bounds);

    // Settings button: top-right, 44x44pt
    auto settings_area = bounds.removeFromTop(ui::kMinTouchTargetSize);
    settings_button_->setBounds(
        settings_area.removeFromRight(ui::kMinTouchTargetSize));

    // Detect orientation
    bool is_landscape = getWidth() > getHeight();

    if (is_landscape) {
      // Landscape layout (existing)
      // Top Zone: Note Display (20% height)
      int note_display_height =
          static_cast<int>(getHeight() * ui::kNoteDisplayHeightRatio);
      note_display_->setBounds(bounds.removeFromTop(note_display_height));

      // Bottom Zone: Controls (15% height)
      int controls_height =
          static_cast<int>(getHeight() * ui::kControlsHeightRatio);
      auto bottom = bounds.removeFromBottom(controls_height);
      mode_selector_->setBounds(
          bottom.removeFromTop(ui::kMinTouchTargetSize).reduced(40, 0));

      // Center Zone: Status + Meter
      int status_height = 40;

      status_indicator_->setBounds(bounds.removeFromTop(status_height));
      bounds.removeFromTop(10);  // Spacing
      tuning_meter_->setBounds(bounds);

    } else {
      // Portrait layout (new)
      // Top Zone: Note Display (15% height - smaller in portrait)
      constexpr float kPortraitNoteDisplayRatio = 0.15f;
      int note_display_height =
          static_cast<int>(getHeight() * kPortraitNoteDisplayRatio);
      note_display_->setBounds(bounds.removeFromTop(note_display_height));

      // Center Zone: Status + Meter
      int status_height = 40;

      status_indicator_->setBounds(bounds.removeFromTop(status_height));
      bounds.removeFromTop(10);  // Spacing

      constexpr float kPortraitMeterRatio = 0.40f;
      int meter_height = static_cast<int>(getHeight() * kPortraitMeterRatio);
      tuning_meter_->setBounds(bounds.removeFromTop(meter_height));

      // Bottom Zone: Controls (stacked horizontally)
      bounds.removeFromTop(10);  // Spacing
      mode_selector_->setBounds(
          bounds.removeFromTop(ui::kMinTouchTargetSize).reduced(40, 0));
    }

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
    // Valid pitch detected
    int midi_note = frequency_calculator_->frequency_to_midi(frequency);
    double cents = frequency_calculator_->calculate_cents(frequency, midi_note);

    // Update all components
    note_display_->update_note_with_cents(midi_note, confidence,
                                          static_cast<float>(cents));
    tuning_meter_->update_needle_position(static_cast<float>(cents));
    status_indicator_->update_status(static_cast<float>(cents));

  } else {
    // No valid pitch detected - set all to "no signal" state
    note_display_->set_no_signal();
    tuning_meter_->set_no_signal();
    status_indicator_->set_no_signal();
  }
}

void MainComponent::handle_mode_change(ModeSelector::Mode mode) noexcept {
  // Update internal app mode state
  if (mode == ModeSelector::Mode::kMeter) {
    current_mode_ = AppMode::kMeter;
  } else {
    current_mode_ = AppMode::kSound;
  }

  // Phase 3: Visual-only change (Sound mode not implemented yet)
  DBG("Mode changed to: " +
      juce::String(current_mode_ == AppMode::kMeter ? "Meter" : "Sound"));
}

juce::String MainComponent::format_cents(double cents) const noexcept {
  try {
    std::ostringstream stream;
    stream << std::showpos << std::fixed << std::setprecision(1) << cents
           << " cents";
    return stream.str();
  } catch (...) {
    return "--";
  }
}

}  // namespace simple_tuner
