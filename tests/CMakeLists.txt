# GoogleTest dependency via FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()
include(GoogleTest)

# SimpleTuner Unit Tests
add_executable(simple_tuner_tests
  test_main.cpp
  test_frequency_calculator.cpp
  test_config_manager.cpp
  test_audio_callbacks.cpp
  test_pitch_detector.cpp
)

target_link_libraries(simple_tuner_tests
  PRIVATE
    simple_tuner_core
    GTest::gtest
    GTest::gtest_main
)

# Discover tests for CTest
gtest_discover_tests(simple_tuner_tests)

# Coverage targets (needs test executable)
enable_coverage_targets(simple_tuner_tests)
