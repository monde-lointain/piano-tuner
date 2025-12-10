# SimpleTuner Unit Tests
add_executable(simple_tuner_tests
  unit/test_main.cpp
  unit/test_frequency_calculator.cpp
  unit/test_config_manager.cpp
)

target_link_libraries(simple_tuner_tests
  PRIVATE
    simple_tuner_core
    GTest::gtest
    GTest::gtest_main
)

# Discover tests for CTest
gtest_discover_tests(simple_tuner_tests)
