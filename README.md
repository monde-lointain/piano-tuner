# SimpleTuner

A cross-platform chromatic instrument tuner built with C++ and JUCE framework for iOS and Android.

## Prerequisites

- CMake 3.20 or higher
- C++17 compatible compiler:
  - GCC 7+ (Linux)
- clang-format (for code formatting)

## Build Instructions

### Configure

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

### Build

```bash
cmake --build build --config Release
```

### Test

```bash
ctest --test-dir build --output-on-failure --build-config Release
```

Or run the test executable directly:

```bash
./build/tests/simple_tuner_tests
```

## Development Workflow

### Code Formatting

Format all C++ files:

```bash
find include src tests -name '*.cpp' -o -name '*.h' | xargs clang-format -i
```

Check formatting without modifying files:

```bash
find include src tests -name '*.cpp' -o -name '*.h' | xargs clang-format --dry-run --Werror
```

### Running CI Locally

The CI pipeline runs on Ubuntu. Test locally before pushing:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build --output-on-failure --build-config Release
```

## Project Structure

```
simple-tuner/
├── include/simple_tuner/       # Public headers
│   ├── interfaces/             # Platform abstraction interfaces
│   ├── algorithms/             # Algorithm headers (FrequencyCalculator, PitchDetector, ToneGenerator)
│   ├── config/                 # ConfigManager
│   └── platform/desktop/       # Desktop mock implementations
├── src/
│   ├── shared/                 # Platform-independent implementations
│   │   ├── algorithms/         # FrequencyCalculator, PitchDetector, ToneGenerator
│   │   └── config/             # ConfigManager
│   └── platform/desktop/       # Mock audio/config/permissions for testing
├── tests/unit/                 # Unit tests (GoogleTest)
├── .github/workflows/          # CI/CD (GitHub Actions)
└── docs/requirements/          # Requirements documentation
```

## Architecture

SimpleTuner uses a platform abstraction layer to enable desktop testing without mobile devices:

- **Interfaces** (`IAudioInput`, `IAudioOutput`, `IConfigStorage`, `IPermissions`): Pure abstract base classes defining platform contracts
- **Shared Library** (`simple_tuner_core`): Platform-independent algorithms (FrequencyCalculator, pitch detection, tone generation)
- **Mock Implementations**: Desktop testing doubles (sine wave generators, in-memory storage)
- **Unit Tests**: 22+ tests validating core functionality with >80% coverage target

Week 1 establishes this testing infrastructure. Subsequent phases integrate JUCE framework for mobile deployment.

## Testing Strategy

Desktop tests gate all mobile builds in CI/CD:

1. **Desktop Tests** (current): Mock implementations, unit tests, multi-platform CI
2. **Mobile Integration** (Week 2+): JUCE platform implementations for iOS/Android

See `docs/requirements/TEST_PLAN.md` for full strategy.

## Requirements

See `docs/requirements/` for comprehensive specifications:
- **SOFTWARE_REQUIREMENTS_SPECIFICATION.md**: Functional/non-functional requirements
- **USE_CASE_DOCUMENTATION.md**: User scenarios and business rules
- **VISION_AND_SCOPE_DOCUMENT.md**: Project scope and objectives
- **TEST_PLAN.md**: Testing strategy and acceptance criteria
- **IMPLEMENTATION_PLAN.md**: 12-week phased roadmap

## License

TBD
