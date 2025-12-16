#include <gtest/gtest.h>

#include <cmath>
#include <vector>

#include "simple_tuner/algorithms/PitchDetector.h"

namespace simple_tuner {
namespace {

// Test fixture for pitch detector tests
class PitchDetectorTest : public ::testing::Test {
 protected:
  static constexpr double kSampleRate = 44100.0;
  static constexpr std::size_t kBufferSize = 4096;
  static constexpr double kCentTolerance = 1.0;  // ±1 cent accuracy

  void SetUp() override {
    detector_ = std::make_unique<PitchDetector>(kSampleRate, kBufferSize);
  }

  // Generate pure sine wave at given frequency
  std::vector<float> generate_sine(double frequency, std::size_t num_samples,
                                   double amplitude = 1.0) {
    std::vector<float> samples(num_samples);
    constexpr double pi = 3.14159265358979323846;
    const double angular_freq = 2.0 * pi * frequency / kSampleRate;
    for (std::size_t i = 0; i < num_samples; ++i) {
      samples[i] = static_cast<float>(
          amplitude * std::sin(angular_freq * static_cast<double>(i)));
    }
    return samples;
  }

  // Generate sine wave with harmonics
  std::vector<float> generate_sine_with_harmonics(
      double fundamental, std::size_t num_samples,
      double harmonic_amplitude = 0.5) {
    std::vector<float> samples(num_samples);
    constexpr double pi = 3.14159265358979323846;
    const double angular_freq = 2.0 * pi * fundamental / kSampleRate;
    const double angular_freq_2 = 2.0 * angular_freq;  // 2nd harmonic

    for (std::size_t i = 0; i < num_samples; ++i) {
      const double t = static_cast<double>(i);
      samples[i] =
          static_cast<float>(std::sin(angular_freq * t) +
                             harmonic_amplitude * std::sin(angular_freq_2 * t));
    }
    return samples;
  }

  // Calculate cents difference between two frequencies
  double calculate_cents(double freq1, double freq2) {
    return 1200.0 * std::log2(freq1 / freq2);
  }

  // Check if frequency detection is within tolerance
  bool is_frequency_accurate(double detected, double expected,
                             double cent_tolerance) {
    double cents_diff = std::abs(calculate_cents(detected, expected));
    return cents_diff <= cent_tolerance;
  }

  std::unique_ptr<PitchDetector> detector_;
};

// Algorithm Tests

TEST_F(PitchDetectorTest, NSDFZeroLagMaximum) {
  // NSDF at lag=0 should be 1.0 (perfect correlation)
  auto samples = generate_sine(440.0, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());
  // We can't directly access NSDF, but detection should succeed
  EXPECT_TRUE(result.is_valid);
  EXPECT_GT(result.confidence, 0.0);
}

TEST_F(PitchDetectorTest, PeakDetectionAccuracy) {
  // Peak detection should find correct period for known frequency
  constexpr double test_freq = 440.0;
  auto samples = generate_sine(test_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(
      is_frequency_accurate(result.frequency, test_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, ParabolicInterpolationPrecision) {
  // Sub-sample accuracy through parabolic interpolation
  constexpr double test_freq = 261.63;  // C4
  auto samples = generate_sine(test_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  // Should achieve ±1 cent accuracy
  EXPECT_TRUE(
      is_frequency_accurate(result.frequency, test_freq, kCentTolerance));
}

// Frequency Detection Tests

TEST_F(PitchDetectorTest, DetectC1LowBoundary) {
  // C1 (32.70 Hz) - lowest note in detection range
  // Requires 4096 buffer for ~3 fundamental cycles at 44.1kHz
  constexpr double c1_freq = 32.70;
  auto samples = generate_sine(c1_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, c1_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectC2) {
  constexpr double c2_freq = 65.41;
  auto samples = generate_sine(c2_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, c2_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectA2) {
  constexpr double a2_freq = 110.0;
  auto samples = generate_sine(a2_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, a2_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectE2) {
  constexpr double e2_freq = 82.41;
  auto samples = generate_sine(e2_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, e2_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectG3) {
  constexpr double g3_freq = 196.00;
  auto samples = generate_sine(g3_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, g3_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectD4) {
  constexpr double d4_freq = 293.66;
  auto samples = generate_sine(d4_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, d4_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectA4ReferenceNote) {
  constexpr double a4_freq = 440.0;
  auto samples = generate_sine(a4_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, a4_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectB5) {
  constexpr double b5_freq = 987.77;
  auto samples = generate_sine(b5_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, b5_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectFSharp6) {
  constexpr double fsharp6_freq = 1479.98;
  auto samples = generate_sine(fsharp6_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(
      is_frequency_accurate(result.frequency, fsharp6_freq, kCentTolerance));
}

TEST_F(PitchDetectorTest, DetectC8HighBoundary) {
  constexpr double c8_freq = 4186.01;
  auto samples = generate_sine(c8_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_TRUE(is_frequency_accurate(result.frequency, c8_freq, kCentTolerance));
}

// Robustness Tests

TEST_F(PitchDetectorTest, HarmonicRejection) {
  // Generate fundamental with strong 2nd harmonic
  constexpr double fundamental = 220.0;
  auto samples = generate_sine_with_harmonics(fundamental, kBufferSize, 0.8);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  // Should detect fundamental, not octave (2nd harmonic)
  EXPECT_TRUE(is_frequency_accurate(result.frequency, fundamental,
                                    5.0));  // Slightly relaxed tolerance
}

TEST_F(PitchDetectorTest, LowSignalRejection) {
  // Signal below -60dBFS threshold should be rejected
  constexpr double test_freq = 440.0;
  constexpr double low_amplitude = 0.0003;  // Approximately -70dBFS
  auto samples = generate_sine(test_freq, kBufferSize, low_amplitude);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_FALSE(result.is_valid);
  EXPECT_EQ(result.frequency, 0.0);
}

TEST_F(PitchDetectorTest, ConfidenceScoring) {
  // Clean sine wave should have high confidence
  constexpr double test_freq = 440.0;
  auto samples = generate_sine(test_freq, kBufferSize);
  auto result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result.is_valid);
  EXPECT_GT(result.confidence, 0.8);
}

TEST_F(PitchDetectorTest, NullPointerHandling) {
  // Null pointer should return invalid result
  auto result = detector_->detect_pitch_detailed(nullptr, kBufferSize);

  EXPECT_FALSE(result.is_valid);
  EXPECT_EQ(result.frequency, 0.0);
  EXPECT_EQ(result.confidence, 0.0);

  // Test simple API as well
  double freq = detector_->detect_pitch(nullptr, kBufferSize);
  EXPECT_EQ(freq, 0.0);
}

TEST_F(PitchDetectorTest, ZeroSamplesHandling) {
  // Zero samples should return invalid result
  std::vector<float> samples(kBufferSize);
  auto result = detector_->detect_pitch_detailed(samples.data(), 0);

  EXPECT_FALSE(result.is_valid);
  EXPECT_EQ(result.frequency, 0.0);
  EXPECT_EQ(result.confidence, 0.0);
}

TEST_F(PitchDetectorTest, SilenceHandling) {
  // Silence (all zeros) should be rejected
  std::vector<float> silence(kBufferSize, 0.0f);
  auto result =
      detector_->detect_pitch_detailed(silence.data(), silence.size());

  EXPECT_FALSE(result.is_valid);
  EXPECT_EQ(result.frequency, 0.0);
}

TEST_F(PitchDetectorTest, RepeatedDetectionStability) {
  // Repeated detections should give stable results
  constexpr double test_freq = 440.0;
  auto samples = generate_sine(test_freq, kBufferSize);

  auto result1 =
      detector_->detect_pitch_detailed(samples.data(), samples.size());
  auto result2 =
      detector_->detect_pitch_detailed(samples.data(), samples.size());
  auto result3 =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_TRUE(result1.is_valid);
  EXPECT_TRUE(result2.is_valid);
  EXPECT_TRUE(result3.is_valid);

  // Results should be identical (deterministic algorithm)
  EXPECT_EQ(result1.frequency, result2.frequency);
  EXPECT_EQ(result2.frequency, result3.frequency);
  EXPECT_EQ(result1.confidence, result2.confidence);
  EXPECT_EQ(result2.confidence, result3.confidence);
}

// Configuration Tests

TEST_F(PitchDetectorTest, ConfigurationThreshold) {
  constexpr double test_freq = 440.0;
  constexpr double amplitude = 0.015;  // ~-36dBFS

  // Default threshold (-40dBFS) should accept this signal
  auto samples = generate_sine(test_freq, kBufferSize, amplitude);
  auto result1 =
      detector_->detect_pitch_detailed(samples.data(), samples.size());
  EXPECT_TRUE(result1.is_valid);

  // Stricter threshold (-30dBFS) should reject it
  detector_->set_threshold_db(-30.0);
  auto result2 =
      detector_->detect_pitch_detailed(samples.data(), samples.size());
  EXPECT_FALSE(result2.is_valid);
}

TEST_F(PitchDetectorTest, ConfigurationFrequencyRange) {
  // Test that frequency range configuration works
  EXPECT_DOUBLE_EQ(detector_->get_min_frequency(), 32.7);
  EXPECT_DOUBLE_EQ(detector_->get_max_frequency(), 4186.0);

  detector_->set_min_frequency(100.0);
  detector_->set_max_frequency(1000.0);

  EXPECT_DOUBLE_EQ(detector_->get_min_frequency(), 100.0);
  EXPECT_DOUBLE_EQ(detector_->get_max_frequency(), 1000.0);
}

TEST_F(PitchDetectorTest, SimpleAPIEquivalence) {
  // Simple API should return same frequency as detailed API
  constexpr double test_freq = 440.0;
  auto samples = generate_sine(test_freq, kBufferSize);

  double simple_result =
      detector_->detect_pitch(samples.data(), samples.size());
  auto detailed_result =
      detector_->detect_pitch_detailed(samples.data(), samples.size());

  EXPECT_EQ(simple_result, detailed_result.frequency);
}

}  // namespace
}  // namespace simple_tuner
