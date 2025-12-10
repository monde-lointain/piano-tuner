#include "simple_tuner/algorithms/FrequencyCalculator.h"

#include <array>
#include <cmath>

namespace simple_tuner {

namespace {
constexpr int kMidiNoteA4 = 69;
constexpr int kNotesPerOctave = 12;
constexpr int kOctaveOffset = 1;
constexpr double kCentsPerOctave = 1200.0;

const std::array<const char*, 12> kNoteNames = {
    "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
}  // namespace

FrequencyCalculator::FrequencyCalculator() : reference_a4_(440.0) {}

FrequencyCalculator::FrequencyCalculator(double reference_a4_hz)
    : reference_a4_(reference_a4_hz) {}

double FrequencyCalculator::midi_to_frequency(int midi_note) const noexcept {
  // f(n) = f_A4 * 2^((n - 69) / 12)
  return reference_a4_ * std::pow(2.0, (midi_note - kMidiNoteA4) / 12.0);
}

int FrequencyCalculator::frequency_to_midi(double frequency) const noexcept {
  // n = 69 + 12 * log2(f / f_A4)
  return static_cast<int>(std::round(
      kMidiNoteA4 + kNotesPerOctave * std::log2(frequency / reference_a4_)));
}

double FrequencyCalculator::calculate_cents(double frequency,
                                            int target_midi) const noexcept {
  double target_frequency = midi_to_frequency(target_midi);
  // cents = 1200 * log2(f_detected / f_target)
  return kCentsPerOctave * std::log2(frequency / target_frequency);
}

std::string FrequencyCalculator::midi_to_note_name(
    int midi_note) const noexcept {
  int note_index = midi_note % kNotesPerOctave;
  return kNoteNames[note_index];
}

int FrequencyCalculator::midi_to_octave(int midi_note) const noexcept {
  // MIDI octave: middle C (MIDI 60) is C4
  return (midi_note / kNotesPerOctave) - kOctaveOffset;
}

void FrequencyCalculator::set_reference_a4(double frequency) noexcept {
  reference_a4_ = frequency;
}

double FrequencyCalculator::get_reference_a4() const noexcept {
  return reference_a4_;
}

}  // namespace simple_tuner
