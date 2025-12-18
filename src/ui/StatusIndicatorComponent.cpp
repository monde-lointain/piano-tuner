#include "simple_tuner/ui/StatusIndicatorComponent.h"

#include <cmath>

#include "simple_tuner/ui/UIConstants.h"

namespace simple_tuner {

StatusIndicatorComponent::StatusIndicatorComponent()
    : current_status_(Status::kNoSignal), status_text_("--") {}

void StatusIndicatorComponent::update_status(float cents) noexcept {
  ui::TuningStatus status = ui::get_tuning_status(cents);
  switch (status) {
    case ui::TuningStatus::kFlat:
      current_status_ = Status::kFlat;
      break;
    case ui::TuningStatus::kInTune:
      current_status_ = Status::kInTune;
      break;
    case ui::TuningStatus::kSharp:
      current_status_ = Status::kSharp;
      break;
  }
  update_text();
  repaint();
}

void StatusIndicatorComponent::set_no_signal() noexcept {
  current_status_ = Status::kNoSignal;
  update_text();
  repaint();
}

void StatusIndicatorComponent::update_text() noexcept {
  switch (current_status_) {
    case Status::kFlat:
      status_text_ = juce::String::fromUTF8("\xE2\x99\xAD");  // ♭
      break;
    case Status::kInTune:
      status_text_ = juce::String::fromUTF8("\xE2\x96\xBC");  // ▼
      break;
    case Status::kSharp:
      status_text_ = juce::String::fromUTF8("\xE2\x99\xAF");  // ♯
      break;
    case Status::kNoSignal:
      status_text_ = "";
      break;
  }
}

void StatusIndicatorComponent::draw_wedge_triangle(juce::Graphics& g,
                                                   float center_x,
                                                   float center_y,
                                                   juce::Colour color) {
  // Draw wedge-shaped triangle pointing downward
  // Base shorter than sides (wedge shape)
  constexpr float triangle_height = 12.0f;
  constexpr float base_width = 8.0f;  // Shorter base for wedge appearance

  // Tip points down
  float tip_x = center_x;
  float tip_y = center_y + (triangle_height * 2.0f / 3.0f);

  // Base is above tip
  float base_center_y = center_y - (triangle_height / 3.0f);
  float base_left_x = center_x - (base_width / 2.0f);
  float base_right_x = center_x + (base_width / 2.0f);

  juce::Path wedge;
  wedge.addTriangle(tip_x, tip_y, base_left_x, base_center_y, base_right_x,
                    base_center_y);

  g.setColour(color);
  g.fillPath(wedge);
}

void StatusIndicatorComponent::paint(juce::Graphics& g) {
  // No background fill - let parent's background show through

  // Draw all three symbols positioned horizontally:
  // Flat (♭) on left, Wedge in center, Sharp (♯) on right
  // All at same vertical position, closer spacing

  auto bounds = getLocalBounds();
  float center_y = bounds.getCentreY();
  float center_x = bounds.getCentreX();

  // Tighter spacing: symbols 60px apart
  constexpr float symbol_spacing = 60.0f;

  // Doubled font size for ♭ and ♯
  float font_size = 40.0f;
  g.setFont(juce::FontOptions(font_size, juce::Font::bold));

  // Color constants
  const juce::Colour kMutedRed = juce::Colour(0xFFD32F2F);
  const juce::Colour kGray = ui::kTextNeutral;

  // Flat symbol on left - red when active (flat), gray when inactive
  juce::Colour flat_color =
      (current_status_ == Status::kFlat) ? kMutedRed : kGray;
  g.setColour(flat_color);
  float flat_x = center_x - symbol_spacing;
  g.drawText(
      juce::String::fromUTF8("\xE2\x99\xAD"),
      juce::Rectangle<float>(flat_x - 20.0f, center_y - 20.0f, 40.0f, 40.0f),
      juce::Justification::centred);

  // Wedge triangle in center - green when active (in tune), gray when inactive
  juce::Colour wedge_color =
      (current_status_ == Status::kInTune) ? ui::kTextInTune : kGray;
  draw_wedge_triangle(g, center_x, center_y, wedge_color);

  // Sharp symbol on right - red when active (sharp), gray when inactive
  juce::Colour sharp_color =
      (current_status_ == Status::kSharp) ? kMutedRed : kGray;
  g.setColour(sharp_color);
  float sharp_x = center_x + symbol_spacing;
  g.drawText(
      juce::String::fromUTF8("\xE2\x99\xAF"),
      juce::Rectangle<float>(sharp_x - 20.0f, center_y - 20.0f, 40.0f, 40.0f),
      juce::Justification::centred);
}

void StatusIndicatorComponent::resized() {
  // No special layout needed - text is centered in paint()
}

}  // namespace simple_tuner
