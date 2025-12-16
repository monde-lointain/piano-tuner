#include "simple_tuner/controllers/PitchDetectionController.h"

#include <algorithm>
#include <cstring>

#include "simple_tuner/algorithms/PitchDetector.h"

namespace simple_tuner {

PitchDetectionController::PitchDetectionController(std::size_t buffer_size,
                                                   double sample_rate)
    : detector_(std::make_unique<PitchDetector>(sample_rate, buffer_size)),
      accumulation_buffer_(buffer_size, 0.0f),
      detection_buffer_(buffer_size, 0.0f),
      write_index_(0),
      buffer_size_(buffer_size),
      hop_size_(buffer_size / 2),
      samples_since_detection_(0),
      latest_frequency_(0.0),
      latest_confidence_(0.0),
      has_valid_result_(false),
      confidence_threshold_(0.5) {}

PitchDetectionController::~PitchDetectionController() = default;

void PitchDetectionController::process_audio(const float* samples,
                                             std::size_t num_samples) noexcept {
  if (samples == nullptr || num_samples == 0) {
    return;
  }

  // Copy samples into circular buffer
  for (std::size_t i = 0; i < num_samples; ++i) {
    accumulation_buffer_[write_index_] = samples[i];
    write_index_ = (write_index_ + 1) % buffer_size_;
  }

  // Run detection every hop_size samples
  samples_since_detection_ += num_samples;

  if (samples_since_detection_ >= hop_size_) {
    samples_since_detection_ = 0;

    // Create linear buffer from circular buffer for detection
    for (std::size_t i = 0; i < buffer_size_; ++i) {
      detection_buffer_[i] =
          accumulation_buffer_[(write_index_ + i) % buffer_size_];
    }

    // Run pitch detection
    auto result = detector_->detect_pitch_detailed(detection_buffer_.data(),
                                                   buffer_size_);

    // Update atomic results if confidence meets threshold
    if (result.is_valid && result.confidence >= confidence_threshold_) {
      latest_frequency_.store(result.frequency, std::memory_order_release);
      latest_confidence_.store(result.confidence, std::memory_order_release);
      has_valid_result_.store(true, std::memory_order_release);
    } else {
      has_valid_result_.store(false, std::memory_order_release);
    }
  }
}

bool PitchDetectionController::get_latest_result(
    double& frequency, double& confidence) const noexcept {
  bool valid = has_valid_result_.load(std::memory_order_acquire);
  if (valid) {
    frequency = latest_frequency_.load(std::memory_order_acquire);
    confidence = latest_confidence_.load(std::memory_order_acquire);
  }
  return valid;
}

void PitchDetectionController::set_confidence_threshold(
    double threshold) noexcept {
  confidence_threshold_ = std::clamp(threshold, 0.0, 1.0);
}

double PitchDetectionController::get_confidence_threshold() const noexcept {
  return confidence_threshold_;
}

}  // namespace simple_tuner
