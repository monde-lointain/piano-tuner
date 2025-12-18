#include "simple_tuner/ui/NoteDisplayComponent.h"

#include <cmath>
#include <iomanip>
#include <sstream>

#include "simple_tuner/algorithms/FrequencyCalculator.h"
#include "simple_tuner/ui/UIConstants.h"

namespace simple_tuner {

NoteDisplayComponent::NoteDisplayComponent(
    std::shared_ptr<FrequencyCalculator> freq_calc)
    : frequency_calculator_(std::move(freq_calc)),
      note_letter_("--"),
      accidental_(""),
      reference_freq_(""),
      current_midi_note_(0),
      current_cents_(0.0f),
      has_signal_(false) {}

void NoteDisplayComponent::update_note(int midi_note,
                                       double confidence) noexcept {
  (void)confidence;  // Unused for now
  update_display_from_midi(midi_note);
  has_signal_ = true;
  current_cents_ = 0.0f;  // Default to neutral color
  repaint();
}

void NoteDisplayComponent::update_note_with_cents(int midi_note,
                                                  double confidence,
                                                  float cents) noexcept {
  (void)confidence;  // Unused for now
  update_display_from_midi(midi_note);
  has_signal_ = true;
  current_cents_ = cents;
  repaint();
}

void NoteDisplayComponent::set_no_signal() noexcept {
  note_letter_ = "--";
  accidental_ = "";
  reference_freq_ = "";
  has_signal_ = false;
  current_cents_ = 0.0f;
  repaint();
}

void NoteDisplayComponent::update_display_from_midi(int midi_note) noexcept {
  try {
    current_midi_note_ = midi_note;

    // Get note name with accidental
    std::string note_name = frequency_calculator_->midi_to_note_name(midi_note);

    // Parse note letter and accidental
    if (note_name.length() >= 1) {
      note_letter_ = juce::String::charToString(note_name[0]);

      if (note_name.length() == 2) {
        // Has accidental (# or b)
        accidental_ = juce::String::charToString(note_name[1]);
      } else {
        accidental_ = "";
      }
    } else {
      note_letter_ = "--";
      accidental_ = "";
    }

    // Calculate reference frequency for this MIDI note
    double ref_freq = frequency_calculator_->midi_to_frequency(midi_note);
    std::ostringstream freq_stream;
    freq_stream << std::fixed << std::setprecision(2) << ref_freq << " Hz";
    reference_freq_ = freq_stream.str();

  } catch (...) {
    note_letter_ = "--";
    accidental_ = "";
    reference_freq_ = "";
  }
}

void NoteDisplayComponent::paint(juce::Graphics& g) {
  // No background fill - let parent's background show through

  if (!has_signal_) {
    // No signal - show placeholder
    g.setColour(ui::kTextInactive);
    g.setFont(juce::FontOptions(getHeight() * ui::kNoteLetterHeightRatio,
                                juce::Font::bold));
    g.drawText(note_letter_, getLocalBounds(), juce::Justification::centred);
    return;
  }

  // Determine color: green if in tune, neutral otherwise
  juce::Colour note_color = ui::get_tuning_color_for_text(current_cents_);

  auto bounds = getLocalBounds();
  int note_letter_height =
      static_cast<int>(getHeight() * ui::kNoteLetterHeightRatio);
  int accidental_height =
      static_cast<int>(getHeight() * ui::kAccidentalHeightRatio);
  int ref_freq_height =
      static_cast<int>(getHeight() * ui::kReferenceFreqHeightRatio);

  // Draw note letter (large, centered)
  g.setColour(note_color);
  g.setFont(juce::FontOptions(note_letter_height, juce::Font::bold));

  auto note_area = bounds.removeFromTop(note_letter_height);

  // Calculate width for positioning accidental
  juce::GlyphArrangement glyphs;
  glyphs.addLineOfText(g.getCurrentFont(), note_letter_, 0.0f, 0.0f);
  int note_width =
      static_cast<int>(glyphs.getBoundingBox(0, -1, true).getWidth());
  int center_x = getWidth() / 2;

  // Draw note centered in its area
  g.drawText(note_letter_, note_area, juce::Justification::centred);

  // Draw accidental if present (smaller, to the right of note)
  if (accidental_.isNotEmpty()) {
    g.setFont(juce::FontOptions(accidental_height, juce::Font::bold));

    // Calculate accidental width and position it to the right of note
    juce::GlyphArrangement accidental_glyphs;
    accidental_glyphs.addLineOfText(g.getCurrentFont(), accidental_, 0.0f,
                                    0.0f);
    int accidental_width = static_cast<int>(
        accidental_glyphs.getBoundingBox(0, -1, true).getWidth());
    int accidental_x = center_x + note_width / 2 + 5;  // 5px spacing

    // Give extra space to prevent truncation
    juce::Rectangle<int> accidental_area(accidental_x, note_area.getY(),
                                         accidental_width + 20,
                                         accidental_height);
    g.drawText(accidental_, accidental_area, juce::Justification::centredLeft);
  }

  // Frequency text removed per UI requirements
}

void NoteDisplayComponent::resized() {
  // Layout handled in paint()
}

}  // namespace simple_tuner
