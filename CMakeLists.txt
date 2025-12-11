cmake_minimum_required(VERSION 3.20)
project(SimpleTuner VERSION 1.0.0 LANGUAGES CXX)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Build options
option(BUILD_TESTING "Build unit tests" ON)

# Sanitizers and coverage (must be before add_subdirectory)
include(cmake/sanitizers.cmake)
include(cmake/coverage.cmake)

# Add subdirectories
add_subdirectory(src)

# Conditionally build tests
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

# Formatting
include(cmake/clang-format.cmake)

# Static analysis
include(cmake/clang-tidy.cmake)
include(cmake/cppcheck.cmake)

# Metrics
include(cmake/complexity.cmake)
include(cmake/sloccount.cmake)

# Documentation
include(cmake/doxygen.cmake)
