#include "simple_tuner/platform/mobile/AudioManager.h"

namespace simple_tuner {

AudioManager& AudioManager::get_instance() noexcept {
  static AudioManager instance;
  return instance;
}

bool AudioManager::initialize() noexcept {
  try {
    device_manager_ = std::make_unique<juce::AudioDeviceManager>();

    // Initialize with 1 input channel, 2 output channels
    juce::String error = device_manager_->initialiseWithDefaultDevices(1, 2);

    if (error.isNotEmpty()) {
      DBG("AudioManager initialization failed: " << error);
      return false;
    }

    // Configure for low latency
    juce::AudioDeviceManager::AudioDeviceSetup setup;
    device_manager_->getAudioDeviceSetup(setup);
    setup.inputChannels.setRange(0, 1, true);   // Mono input
    setup.outputChannels.setRange(0, 2, true);  // Stereo output

    // Phase 5: Platform-specific low latency buffer configuration
#if JUCE_IOS
    // iOS: Request 128 samples for minimal latency
    // AVAudioSession will be configured by JUCE with preferred buffer size
    setup.bufferSize = 128;
#elif JUCE_ANDROID
    // Android: Try for smallest available buffer (typically 192-256)
    setup.bufferSize = 128;
#else
    // Desktop/other: Use 256 as reasonable low latency default
    setup.bufferSize = 256;
#endif

    setup.sampleRate = 0;  // Auto-detect (44.1/48kHz)

    error = device_manager_->setAudioDeviceSetup(setup, true);
    if (error.isNotEmpty()) {
      DBG("AudioManager setup failed: " << error);
      return false;
    }

    device_manager_->addAudioCallback(this);
    return true;
  } catch (...) {
    DBG("Exception in AudioManager::initialize()");
    return false;
  }
}

bool AudioManager::start() noexcept {
  try {
    if (device_manager_ == nullptr) {
      return false;
    }
    return true;
  } catch (...) {
    DBG("Exception in AudioManager::start()");
    return false;
  }
}

void AudioManager::stop() noexcept {
  try {
    if (device_manager_ != nullptr) {
      device_manager_->removeAudioCallback(this);
    }
  } catch (...) {
    DBG("Exception in AudioManager::stop()");
  }
}

void AudioManager::set_input_handler(
    std::function<void(const float*, int)> handler) noexcept {
  try {
    input_handler_ = std::move(handler);
  } catch (...) {
    DBG("Exception in AudioManager::set_input_handler()");
  }
}

void AudioManager::set_output_handler(
    std::function<void(float*, int)> handler) noexcept {
  try {
    output_handler_ = std::move(handler);
  } catch (...) {
    DBG("Exception in AudioManager::set_output_handler()");
  }
}

double AudioManager::get_sample_rate() const noexcept {
  return sample_rate_.load();
}

int AudioManager::get_buffer_size() const noexcept {
  return buffer_size_.load();
}

bool AudioManager::is_initialized() const noexcept {
  try {
    return device_manager_ != nullptr &&
           device_manager_->getCurrentAudioDevice() != nullptr;
  } catch (...) {
    return false;
  }
}

int AudioManager::get_input_channels() const noexcept {
  try {
    auto* device = device_manager_->getCurrentAudioDevice();
    return device ? device->getActiveInputChannels().countNumberOfSetBits() : 0;
  } catch (...) {
    return 0;
  }
}

int AudioManager::get_output_channels() const noexcept {
  try {
    auto* device = device_manager_->getCurrentAudioDevice();
    return device ? device->getActiveOutputChannels().countNumberOfSetBits()
                  : 0;
  } catch (...) {
    return 0;
  }
}

void AudioManager::audioDeviceIOCallbackWithContext(
    const float* const* input_channel_data, int num_input_channels,
    float* const* output_channel_data, int num_output_channels, int num_samples,
    const juce::AudioIODeviceCallbackContext& context) {
  (void)context;

  try {
    // Handle input - Placeholder for pitch detection
    if (input_handler_ && num_input_channels > 0 &&
        input_channel_data != nullptr) {
      // TODO(Week 3): Process input through pitch detector
      input_handler_(input_channel_data[0], num_samples);
    }

    // Handle output - Placeholder for tone generation
    if (output_handler_ && num_output_channels > 0 &&
        output_channel_data != nullptr) {
      // TODO(Week 3): Generate reference tone for tuner mode
      output_handler_(output_channel_data[0], num_samples);
      // Copy to second channel if stereo
      if (num_output_channels > 1) {
        std::memcpy(output_channel_data[1], output_channel_data[0],
                    static_cast<size_t>(num_samples) * sizeof(float));
      }
    } else {
      // Clear output buffers if no handler
      for (int ch = 0; ch < num_output_channels; ++ch) {
        if (output_channel_data[ch] != nullptr) {
          std::memset(output_channel_data[ch], 0,
                      static_cast<size_t>(num_samples) * sizeof(float));
        }
      }
    }
  } catch (...) {
    // Suppress exceptions in audio callback
    for (int ch = 0; ch < num_output_channels; ++ch) {
      if (output_channel_data != nullptr &&
          output_channel_data[ch] != nullptr) {
        std::memset(output_channel_data[ch], 0,
                    static_cast<size_t>(num_samples) * sizeof(float));
      }
    }
  }
}

void AudioManager::audioDeviceAboutToStart(juce::AudioIODevice* device) {
  try {
    if (device != nullptr) {
      sample_rate_.store(device->getCurrentSampleRate());
      buffer_size_.store(device->getCurrentBufferSizeSamples());
    }
  } catch (...) {
    DBG("Exception in AudioManager::audioDeviceAboutToStart()");
  }
}

void AudioManager::audioDeviceStopped() {
  try {
    // Cleanup if needed
  } catch (...) {
    DBG("Exception in AudioManager::audioDeviceStopped()");
  }
}

}  // namespace simple_tuner
