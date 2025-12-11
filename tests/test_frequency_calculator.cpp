#include <gtest/gtest.h>

#include <cmath>

#include "simple_tuner/algorithms/FrequencyCalculator.h"

namespace simple_tuner {
namespace {

constexpr double kEpsilon = 0.01;  // ±1 cent tolerance

TEST(FrequencyCalculatorTest, A4_440Hz) {
  FrequencyCalculator calc;
  EXPECT_NEAR(440.0, calc.midi_to_frequency(69), kEpsilon);
}

TEST(FrequencyCalculatorTest, MiddleC_C4) {
  FrequencyCalculator calc;
  // Middle C (MIDI 60) should be 261.626 Hz at A4=440
  EXPECT_NEAR(261.626, calc.midi_to_frequency(60), kEpsilon);
}

TEST(FrequencyCalculatorTest, RoundTripFrequencyToMidiToFrequency) {
  FrequencyCalculator calc;
  double original_frequency = 440.0;
  int midi = calc.frequency_to_midi(original_frequency);
  double result_frequency = calc.midi_to_frequency(midi);
  EXPECT_NEAR(original_frequency, result_frequency, kEpsilon);
}

TEST(FrequencyCalculatorTest, CentDeviationPositiveSharp) {
  FrequencyCalculator calc;
  // 445 Hz is sharp of A4 (440 Hz)
  double cents = calc.calculate_cents(445.0, 69);
  EXPECT_GT(cents, 0.0);
  EXPECT_NEAR(19.6, cents, 1.0);  // Approximately +19.6 cents
}

TEST(FrequencyCalculatorTest, CentDeviationNegativeFlat) {
  FrequencyCalculator calc;
  // 435 Hz is flat of A4 (440 Hz)
  double cents = calc.calculate_cents(435.0, 69);
  EXPECT_LT(cents, 0.0);
  EXPECT_NEAR(-19.8, cents, 1.0);  // Approximately -19.8 cents
}

TEST(FrequencyCalculatorTest, CentDeviationZeroInTune) {
  FrequencyCalculator calc;
  // Exactly 440 Hz should be 0 cents from A4
  double cents = calc.calculate_cents(440.0, 69);
  EXPECT_NEAR(0.0, cents, 0.1);
}

TEST(FrequencyCalculatorTest, NoteNameC) {
  FrequencyCalculator calc;
  // MIDI 60 is C4
  EXPECT_EQ("C", calc.midi_to_note_name(60));
}

TEST(FrequencyCalculatorTest, NoteNameCSharp) {
  FrequencyCalculator calc;
  // MIDI 61 is C#
  EXPECT_EQ("C#", calc.midi_to_note_name(61));
}

TEST(FrequencyCalculatorTest, OctaveMiddleC) {
  FrequencyCalculator calc;
  // MIDI 60 is C4, so octave should be 4
  EXPECT_EQ(4, calc.midi_to_octave(60));
}

TEST(FrequencyCalculatorTest, OctaveC5) {
  FrequencyCalculator calc;
  // MIDI 72 is C5
  EXPECT_EQ(5, calc.midi_to_octave(72));
}

TEST(FrequencyCalculatorTest, ReferencePitchUpdate) {
  FrequencyCalculator calc;
  calc.set_reference_a4(442.0);
  EXPECT_NEAR(442.0, calc.get_reference_a4(), 0.001);
  // A4 should now be 442 Hz
  EXPECT_NEAR(442.0, calc.midi_to_frequency(69), kEpsilon);
}

TEST(FrequencyCalculatorTest, NonStandardReferencePitch415Hz) {
  // Baroque pitch
  FrequencyCalculator calc(415.0);
  EXPECT_NEAR(415.0, calc.midi_to_frequency(69), kEpsilon);
}

TEST(FrequencyCalculatorTest, BoundaryC1LowFrequency) {
  FrequencyCalculator calc;
  // C1 is MIDI 24, should be 32.70 Hz
  EXPECT_NEAR(32.70, calc.midi_to_frequency(24), kEpsilon);
}

TEST(FrequencyCalculatorTest, BoundaryC8HighFrequency) {
  FrequencyCalculator calc;
  // C8 is MIDI 108, should be 4186.01 Hz
  EXPECT_NEAR(4186.01, calc.midi_to_frequency(108), 1.0);
}

}  // namespace
}  // namespace simple_tuner
