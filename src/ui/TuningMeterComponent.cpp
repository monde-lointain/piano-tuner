#include "simple_tuner/ui/TuningMeterComponent.h"

#include <cmath>

#include "simple_tuner/ui/UIConstants.h"

namespace simple_tuner {

namespace {
constexpr float kPi = 3.14159265359f;
constexpr float kDegreesToRadians = kPi / 180.0f;
}  // namespace

TuningMeterComponent::TuningMeterComponent()
    : TuningMeterComponent(TuningMeterConfig{}) {}

TuningMeterComponent::TuningMeterComponent(const TuningMeterConfig& config)
    : config_(config),
      target_needle_position_(0.0f),
      current_needle_position_(0.0f),
      has_signal_(false),
      meter_center_x_(0.0f),
      meter_center_y_(0.0f),
      meter_radius_(0.0f) {
  startTimerHz(60);  // 60 FPS for smooth animation
}

TuningMeterComponent::~TuningMeterComponent() { stopTimer(); }

void TuningMeterComponent::update_needle_position(float cents) noexcept {
  // Clamp to valid range to prevent needle from getting stuck at extremes
  target_needle_position_ =
      std::max(-config_.cents_range, std::min(config_.cents_range, cents));
  has_signal_ = true;
}

void TuningMeterComponent::set_no_signal() noexcept {
  has_signal_ = false;
  target_needle_position_ = 0.0f;
}

void TuningMeterComponent::timerCallback() {
  // Apply damping to needle position
  float delta = target_needle_position_ - current_needle_position_;

  // Snap to target if very close (avoids asymptotic crawl)
  constexpr float kSnapThreshold = 0.01f;
  if (std::abs(delta) < kSnapThreshold) {
    current_needle_position_ = target_needle_position_;
  } else {
    current_needle_position_ += delta * config_.damping;
  }

  repaint();
}

float TuningMeterComponent::cents_to_angle(float cents) const noexcept {
  // Map cents range [-config.cents_range, +config.cents_range] to arc span
  // Center (0 cents) = config.center_angle_deg
  // Negative cents (flat) -> larger angle (LEFT)
  // Positive cents (sharp) -> smaller angle (RIGHT)

  float half_arc_span = config_.arc_span_deg / 2.0f;

  // Normalize cents to [-1, 1] range
  float normalized = cents / config_.cents_range;
  normalized = std::max(-1.0f, std::min(1.0f, normalized));

  // Map to angle: flat (negative) increases angle (goes left/counterclockwise)
  // sharp (positive) decreases angle (goes right/clockwise)
  float angle_degrees = config_.center_angle_deg + (normalized * half_arc_span);
  return angle_degrees * kDegreesToRadians;
}

void TuningMeterComponent::draw_radial_lines(juce::Graphics& g) {
  // Draw radial lines from center for every 2.5 cents (±config.cents_range)
  // Lines extend from 1/3 to 98% of radius (bottom 1/3 cut off)
  g.setColour(ui::kMeterNeutral.withAlpha(0.4f));  // Lighter gray

  // Use float for loop to handle 2.5 cent increments
  for (float cents = -config_.cents_range; cents <= config_.cents_range;
       cents += 2.5f) {
    float angle = cents_to_angle(cents);

    float line_start_x =
        meter_center_x_ + (meter_radius_ * kLineStartRatio) * std::cos(angle);
    float line_start_y =
        meter_center_y_ + (meter_radius_ * kLineStartRatio) * std::sin(angle);

    float line_end_x =
        meter_center_x_ + (meter_radius_ * kLineEndRatio) * std::cos(angle);
    float line_end_y =
        meter_center_y_ + (meter_radius_ * kLineEndRatio) * std::sin(angle);

    g.drawLine(line_start_x, line_start_y, line_end_x, line_end_y, 1.0f);
  }
}

void TuningMeterComponent::draw_cent_dots(juce::Graphics& g) {
  // Draw dots at every 5 cents from -config.cents_range to +config.cents_range
  // Small dots at every 5 cents, large dots at every 10 cents
  // Skip center (0 cents) - replaced by triangle
  g.setColour(ui::kMeterNeutral);

  int cents_range_int = static_cast<int>(config_.cents_range);
  for (int cents = -cents_range_int; cents <= cents_range_int; cents += 5) {
    if (cents == 0) {
      continue;  // Skip center - triangle drawn separately
    }

    float angle = cents_to_angle(static_cast<float>(cents));

    float dot_x = meter_center_x_ + meter_radius_ * std::cos(angle);
    float dot_y = meter_center_y_ + meter_radius_ * std::sin(angle);

    // Large dots at every 10 cents, small dots at every 5 cents
    bool is_major = (cents % 10 == 0);
    float dot_radius = is_major ? kLargeDotRadius : kSmallDotRadius;

    g.fillEllipse(dot_x - dot_radius, dot_y - dot_radius, dot_radius * 2.0f,
                  dot_radius * 2.0f);
  }

  // Draw labels: "0" above center, "-20" and "+20" at their positions
  g.setFont(juce::FontOptions(12.0f, juce::Font::bold));
  g.setColour(ui::kMeterNeutral);

  // "0" label - positioned above the center dot (beyond the dot, on radial
  // line)
  float center_angle = cents_to_angle(0.0f);
  float center_label_distance = meter_radius_ + kCenterLabelDistance;
  float center_label_x =
      meter_center_x_ + center_label_distance * std::cos(center_angle);
  float center_label_y =
      meter_center_y_ + center_label_distance * std::sin(center_angle);
  g.drawText("0",
             juce::Rectangle<float>(center_label_x - 12.0f,
                                    center_label_y - 12.0f, 24.0f, 24.0f),
             juce::Justification::centred);

  // "-20" label - positioned at -20 cents, beyond the dot
  float minus_20_angle = cents_to_angle(-20.0f);
  float minus_20_distance = meter_radius_ + kCenterLabelDistance;
  float minus_20_x =
      meter_center_x_ + minus_20_distance * std::cos(minus_20_angle);
  float minus_20_y =
      meter_center_y_ + minus_20_distance * std::sin(minus_20_angle);
  g.drawText("-20",
             juce::Rectangle<float>(minus_20_x - 16.0f, minus_20_y - 12.0f,
                                    32.0f, 24.0f),
             juce::Justification::centred);

  // "+20" label - positioned at +20 cents, beyond the dot
  float plus_20_angle = cents_to_angle(20.0f);
  float plus_20_distance = meter_radius_ + kCenterLabelDistance;
  float plus_20_x =
      meter_center_x_ + plus_20_distance * std::cos(plus_20_angle);
  float plus_20_y =
      meter_center_y_ + plus_20_distance * std::sin(plus_20_angle);
  g.drawText("+20",
             juce::Rectangle<float>(plus_20_x - 16.0f, plus_20_y - 12.0f, 32.0f,
                                    24.0f),
             juce::Justification::centred);
}

void TuningMeterComponent::draw_center_triangle(juce::Graphics& g) {
  // Draw equilateral triangle at center (0 cents)
  // 4/3 larger than major interval dots (which have radius 2.0)
  constexpr float triangle_size = kLargeDotRadius * 1.5f;

  float angle = cents_to_angle(0.0f);
  float center_x =
      meter_center_x_ + (meter_radius_ * kTriangleStartRatio) * std::cos(angle);
  float center_y =
      meter_center_y_ + (meter_radius_ * kTriangleStartRatio) * std::sin(angle);

  // Create equilateral triangle pointing toward meter center
  // Direction vector from triangle center to meter center
  float dx = meter_center_x_ - center_x;
  float dy = meter_center_y_ - center_y;
  float dist = std::sqrt(dx * dx + dy * dy);
  float dir_x = dx / dist;  // Normalized
  float dir_y = dy / dist;

  // Perpendicular vector
  float perp_x = -dir_y;
  float perp_y = dir_x;

  // Height of equilateral triangle: h = (sqrt(3)/2) * side
  float side_length = triangle_size * 2.0f;
  float height = side_length * kSqrt3Over2;

  // Tip points toward center (2/3 from base)
  float tip_x = center_x + dir_x * (height * 2.0f / 3.0f);
  float tip_y = center_y + dir_y * (height * 2.0f / 3.0f);

  // Base vertices (perpendicular to direction)
  float base_offset = height / 3.0f;
  float base_center_x = center_x - dir_x * base_offset;
  float base_center_y = center_y - dir_y * base_offset;

  float half_base = side_length / 2.0f;
  float base_left_x = base_center_x + perp_x * half_base;
  float base_left_y = base_center_y + perp_y * half_base;
  float base_right_x = base_center_x - perp_x * half_base;
  float base_right_y = base_center_y - perp_y * half_base;

  juce::Path triangle;
  triangle.addTriangle(tip_x, tip_y, base_left_x, base_left_y, base_right_x,
                       base_right_y);

  g.setColour(ui::kMeterNeutral);
  g.fillPath(triangle);
}

void TuningMeterComponent::draw_interval_wedge(juce::Graphics& g, float cents) {
  // Draw wedge triangle at interval position
  // Size matches large dots (major interval dots)
  // Wedge: base is 90% of side length
  // Tips point inward toward center, aligned with radial line ends
  constexpr float triangle_size = kLargeDotRadius;

  float angle = cents_to_angle(cents);

  // Position tip at radial line end (pointing toward center)
  float tip_x =
      meter_center_x_ + (meter_radius_ * kLineEndRatio) * std::cos(angle);
  float tip_y =
      meter_center_y_ + (meter_radius_ * kLineEndRatio) * std::sin(angle);

  // Direction toward meter center (tip points inward)
  float dx = meter_center_x_ - tip_x;
  float dy = meter_center_y_ - tip_y;
  float dist = std::sqrt(dx * dx + dy * dy);
  float dir_x = dx / dist;
  float dir_y = dy / dist;

  // Perpendicular vector
  float perp_x = -dir_y;
  float perp_y = dir_x;

  // Wedge: base is 5/6 of side length
  float side_length = triangle_size * 2.0f;
  float base_length = side_length * (5.0f / 6.0f);
  float height = side_length * kSqrt3Over2;

  // Base is outward from tip (tip points toward center)
  float base_center_x = tip_x - dir_x * height;
  float base_center_y = tip_y - dir_y * height;

  float half_base = base_length / 2.0f;
  float base_left_x = base_center_x + perp_x * half_base;
  float base_left_y = base_center_y + perp_y * half_base;
  float base_right_x = base_center_x - perp_x * half_base;
  float base_right_y = base_center_y - perp_y * half_base;

  juce::Path wedge;
  wedge.addTriangle(tip_x, tip_y, base_left_x, base_left_y, base_right_x,
                    base_right_y);

  g.setColour(ui::kMeterNeutral);
  g.fillPath(wedge);
}

void TuningMeterComponent::draw_needle(juce::Graphics& g) {
  if (!has_signal_) {
    return;
  }

  float needle_angle = cents_to_angle(current_needle_position_);

  // Needle extends from center to arc
  float needle_end_x = meter_center_x_ +
                       (meter_radius_ * kLineEndRatio) * std::cos(needle_angle);
  float needle_end_y = meter_center_y_ +
                       (meter_radius_ * kLineEndRatio) * std::sin(needle_angle);

  // Determine needle color based on in-tune status
  juce::Colour needle_color =
      ui::get_tuning_color_for_meter(current_needle_position_);

  g.setColour(needle_color);

  // Draw main needle line
  g.drawLine(meter_center_x_, meter_center_y_, needle_end_x, needle_end_y,
             ui::kNeedleThickness);
}

void TuningMeterComponent::paint(juce::Graphics& g) {
  // Draw in order from back to front:
  draw_radial_lines(g);     // Radial lines radiating from center
  draw_cent_dots(g);        // Dots at 10-cent intervals
  draw_center_triangle(g);  // Center triangle at 0 cents
  draw_interval_wedge(g, ui::kPureMajorThirdCents);  // Major third wedge
  draw_interval_wedge(g, ui::kPureMinorThirdCents);  // Minor third wedge
  draw_needle(g);                                    // Needle on top

  // Draw "CENT" labels at bottom left and bottom right corners
  auto bounds = getLocalBounds();
  g.setFont(juce::FontOptions(12.0f, juce::Font::bold));
  g.setColour(ui::kTextNeutral);

  constexpr int kCentLabelOffset = 10;  // Offset from edge toward center
  int bottom_y = bounds.getBottom() - 15;

  // Left "CENT" label
  g.drawText(
      "CENT",
      juce::Rectangle<int>(bounds.getX() + kCentLabelOffset, bottom_y, 40, 20),
      juce::Justification::centredLeft);

  // Right "CENT" label
  g.drawText("CENT",
             juce::Rectangle<int>(bounds.getRight() - 40 - kCentLabelOffset,
                                  bottom_y, 40, 20),
             juce::Justification::centredRight);
}

void TuningMeterComponent::resized() {
  auto bounds = getLocalBounds();

  // Calculate meter geometry
  meter_radius_ = bounds.getWidth() * ui::kMeterRadiusRatio;
  meter_center_x_ = bounds.getCentreX();

  // Position center at 85% down for visual balance
  meter_center_y_ = bounds.getY() + bounds.getHeight() * 0.85f;

  // Precompute tick angles
  tick_angles_.clear();
  for (int cents = -ui::kMeterRange; cents <= ui::kMeterRange;
       cents += ui::kTickMarkInterval) {
    tick_angles_.push_back(cents_to_angle(static_cast<float>(cents)));
  }
}

}  // namespace simple_tuner
