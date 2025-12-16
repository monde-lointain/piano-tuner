# SimpleTuner Core Library
add_library(simple_tuner_core STATIC
  # Shared algorithms (to be implemented)
  shared/algorithms/FrequencyCalculator.cpp
  shared/algorithms/PitchDetector.cpp
  shared/algorithms/ToneGenerator.cpp

  # Shared config
  shared/config/ConfigManager.cpp

  # Controllers
  controllers/PitchDetectionController.cpp

  # Desktop platform mocks
  platform/desktop/MockAudioInput.cpp
  platform/desktop/MockAudioOutput.cpp
  platform/desktop/MockConfigStorage.cpp
  platform/desktop/MockPermissions.cpp
)

target_include_directories(simple_tuner_core
  PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(simple_tuner_core
  PUBLIC
    cxx_std_17
)
