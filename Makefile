.PHONY: all configure build run \
        run-tests coverage \
        format lint format-and-lint \
        generate-doc clean help

MAKEFLAGS += --no-print-directory

# ------------------ Configurable Variables ------------------

BUILD_DIR ?= build

INCLUDE_DIR := include

TEST_EXECUTABLE_NAME ?= linalg_UnitTests

# External tools (check availability at runtime)
CMAKE := $(shell command -v cmake 2>/dev/null)
CLANG_FORMAT := $(shell command -v clang-format 2>/dev/null)
CLANG_TIDY := $(shell command -v clang-tidy 2>/dev/null)
GCOVR := $(shell command -v gcovr 2>/dev/null)

# Internal variables
CMAKE_FLAGS ?= -DLINALG_ENABLE_UNIT_TESTS=ON

FIX ?= OFF

# ------------------ Helper Functions ------------------

define check_tool
	@if [ -z "$($1)" ]; then echo "Error: $2 is not installed or not in PATH."; exit 1; fi
endef

# ------------------ Main Targets ------------------

all: build

configure:
	$(call check_tool,CMAKE,CMake)
	@echo "Configuring build..."
	@cmake -S . -B $(BUILD_DIR) $(CMAKE_FLAGS)

build:
	@echo "Building project..."
	@cmake --build $(BUILD_DIR) --parallel

run-tests: build
	@echo "Running test executable $(TEST_EXECUTABLE_NAME)..."
	@./$(BUILD_DIR)/tests/$(TEST_EXECUTABLE_NAME)

coverage: run-tests
	$(call check_tool,GCOVR,gcovr)
	@echo "Generating coverage reports..."
	@mkdir -p tests/coverage_report
	@gcovr -f $(INCLUDE_DIR) --exclude-throw-branches --json-summary -o tests/coverage_report/coverage_report.json
	@gcovr -f $(INCLUDE_DIR) --exclude-throw-branches --html-details -o tests/coverage_report/coverage_report.html

# ------------------ Code Quality ------------------

format:
	$(call check_tool,CLANG_FORMAT,clang-format)
	@echo "Running clang-format..."
	@cmake -S . -B $(BUILD_DIR) -DFILES_TO_CHECK="$(FILES)" -DLINALG_ENABLE_CLANG_FORMAT=ON -DLINALG_ENABLE_CLANG_TIDY=OFF
	@cmake --build $(BUILD_DIR) --target run-clang-format-linalg

lint:
	$(call check_tool,CLANG_TIDY,clang-tidy)
	@echo "Running clang-tidy (FIX=$(FIX))..."
	@cmake -S . -B $(BUILD_DIR) -DFILES_TO_CHECK="$(FILES)" -DLINALG_ENABLE_CLANG_FORMAT=OFF -DLINALG_ENABLE_CLANG_TIDY=ON -DLINALG_ENABLE_FIX_CLANG_TIDY=$(FIX)
	@cmake --build $(BUILD_DIR) --target run-clang-tidy-linalg

format-and-lint: format lint
	@echo "Formatting and linting completed."

# ------------------ Documentation ------------------

documentation:
	@echo "Generating documentation with Doxygen..."
	@cmake -S . -B $(BUILD_DIR) -DLINALG_ENABLE_DOXYGEN=ON
	@cmake --build $(BUILD_DIR) --target generate-doc-linalg

# ------------------ Cleanup ------------------

clean:
	@echo "Cleaning all build and coverage artifacts..."
	@rm -rf build* tests/coverage_report

# ------------------ Help ------------------

help:
	@echo "Available make targets:"
	@echo "  all (default)          - Build the project in Release mode"
	@echo "  configure              - Configure the project"
	@echo "  build                  - Build the project"
	@echo "  run                    - Run the executable"
	@echo "  configure-debug        - Configure the project in Debug mode"
	@echo "  build-debug            - Build the project in Debug mode"
	@echo "  run-debug              - Run the executable in Debug mode"
	@echo "  configure-tests        - Configure the project for tests"
	@echo "  build-tests            - Build the project for tests"
	@echo "  run-tests              - Run the tests"
	@echo "  coverage               - Generate coverage reports"
	@echo "  format                 - Format all source files (use FILES=\"file1.cpp file2.cpp\" to specify files)"
	@echo "  format-diff            - Format changed source files"
	@echo "  lint                   - Lint all source files (use FILES=\"file1.cpp file2.cpp\" to specify files)"
	@echo "  lint-diff              - Lint changed source files"
	@echo "  format-and-lint        - Format and lint all source files"
	@echo "  format-and-lint-diff   - Format and lint changed source files"
	@echo "  documentation          - Generate documentation with Doxygen"
	@echo "  clean                  - Clean all build and coverage artifacts"

