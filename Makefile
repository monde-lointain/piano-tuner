.DEFAULT_GOAL := help
.PHONY: help configure configure-release configure-debug configure-coverage \
        configure-sanitize configure-no-tests build rebuild clean test coverage \
        coverage-html format format-check tidy cppcheck complexity analyze docs \
        sloccount all

# Build directory
BUILD_DIR := build

# Default build type
BUILD_TYPE ?= Debug

# Sanitizer options (empty by default)
SANITIZER ?=

# Build tests (default: ON)
BUILD_TESTS ?= ON

# CMake generator (default: Unix Makefiles)
CMAKE_GENERATOR ?= "Unix Makefiles"

# Number of parallel jobs
JOBS ?= $(shell nproc 2>/dev/null || echo 4)

#######################
# Configuration Targets
#######################

configure: ## Configure Debug build with all analysis enabled
	@echo "Configuring Debug build with analysis..."
	cmake -S . -B $(BUILD_DIR) \
		-G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DBUILD_TESTING=$(BUILD_TESTS)

configure-release: ## Configure Release build
	@echo "Configuring Release build..."
	cmake -S . -B $(BUILD_DIR) \
		-G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Release \
		-DBUILD_TESTING=$(BUILD_TESTS)

configure-debug: ## Configure Debug build (no analysis)
	@echo "Configuring Debug build..."
	cmake -S . -B $(BUILD_DIR) \
		-G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DBUILD_TESTING=$(BUILD_TESTS)

configure-coverage: ## Configure Debug build with coverage analysis
	@echo "Configuring Debug build with coverage..."
	cmake -S . -B $(BUILD_DIR) \
		-G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DENABLE_COVERAGE_ANALYSIS=ON \
		-DBUILD_TESTING=ON

configure-sanitize: ## Configure Debug build with sanitizers (set SANITIZER=address,undefined)
	@echo "Configuring Debug build with sanitizers ($(SANITIZER))..."
	cmake -S . -B $(BUILD_DIR) \
		-G $(CMAKE_GENERATOR) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DUSE_SANITIZER=$(SANITIZER) \
		-DBUILD_TESTING=$(BUILD_TESTS)

configure-no-tests: ## Configure build without tests (set BUILD_TYPE for Debug/Release)
	@echo "Configuring $(BUILD_TYPE) build without tests..."
	$(MAKE) BUILD_TESTS=OFF configure-$(shell echo $(BUILD_TYPE) | tr A-Z a-z)

#################
# Build Targets
#################

## Build the project (requires prior configure)
build: | configure
	cmake --build $(BUILD_DIR) -j $(JOBS)

rebuild: clean configure build ## Clean, configure, and build from scratch

clean: ## Remove build directory
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)

##################
# Testing Targets
##################

## Run tests
test: | configure build
	ctest --test-dir $(BUILD_DIR)/tests --output-on-failure

## Generate coverage reports (requires configure-coverage)
coverage: | configure-coverage build
	cmake --build $(BUILD_DIR)/tests --target coverage

####################
# Analysis Targets
####################

format: ## Format code in-place
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR); \
	fi
	cmake --build $(BUILD_DIR) --target format

format-check: ## Check code formatting (dry-run)
	@echo "Checking code formatting..."
	find include src tests -name '*.cpp' -o -name '*.h' | \
		xargs clang-format --dry-run --Werror

tidy: | configure
	cmake --build $(BUILD_DIR) --target tidy

cppcheck: ## Run cppcheck
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR); \
	fi
	cmake --build $(BUILD_DIR) --target cppcheck

complexity: ## Run complexity analysis
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR); \
	fi
	cmake --build $(BUILD_DIR) --target complexity

analyze: tidy cppcheck complexity ## Run all static analysis

##################
# Utility Targets
##################

docs: ## Generate documentation
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR); \
	fi
	cmake --build $(BUILD_DIR) --target docs

sloccount: ## Generate code metrics
	@if [ ! -d "$(BUILD_DIR)" ]; then \
		cmake -S . -B $(BUILD_DIR) -G $(CMAKE_GENERATOR); \
	fi
	cmake --build $(BUILD_DIR) --target sloccount

all: configure build test ## Configure, build, and test

help: ## Display this help message
	@echo "Usage: make [target]"
	@echo ""
	@echo "Available targets:"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | \
		awk 'BEGIN {FS = ":.*?## "}; {printf "  %-20s %s\n", $$1, $$2}'
	@echo ""
	@echo "Variables:"
	@echo "  BUILD_DIR    Build directory (default: build)"
	@echo "  BUILD_TYPE   Build type (default: Debug)"
	@echo "  BUILD_TESTS  Build unit tests (default: ON)"
	@echo "  SANITIZER    Sanitizer(s) to use (e.g., address,undefined)"
	@echo "  JOBS         Parallel jobs (default: nproc)"
	@echo ""
	@echo "Examples:"
	@echo "  make all                         # Quick start: configure + build + test"
	@echo "  make BUILD_TESTS=OFF configure build  # Build without tests"
	@echo "  make configure-no-tests build    # Build without tests"
	@echo "  make configure-coverage build test coverage  # Coverage workflow"
	@echo "  make SANITIZER=address configure-sanitize build test  # Sanitizer build"
	@echo "  make analyze                     # Run all static analysis"
