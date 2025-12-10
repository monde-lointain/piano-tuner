#ifndef SIMPLE_TUNER_ALGORITHMS_FREQUENCY_CALCULATOR_H_
#define SIMPLE_TUNER_ALGORITHMS_FREQUENCY_CALCULATOR_H_

#include <string>

namespace simple_tuner {

class FrequencyCalculator {
 public:
  FrequencyCalculator();
  explicit FrequencyCalculator(double reference_a4_hz);
  ~FrequencyCalculator() = default;

  // Equal temperament frequency conversions
  double midi_to_frequency(int midi_note) const noexcept;
  int frequency_to_midi(double frequency) const noexcept;

  // Tuning calculations
  double calculate_cents(double frequency, int target_midi) const noexcept;

  // Note naming
  std::string midi_to_note_name(int midi_note) const noexcept;
  int midi_to_octave(int midi_note) const noexcept;

  // Reference pitch
  void set_reference_a4(double frequency) noexcept;
  double get_reference_a4() const noexcept;

 private:
  double reference_a4_;
};

}  // namespace simple_tuner

#endif  // SIMPLE_TUNER_ALGORITHMS_FREQUENCY_CALCULATOR_H_
