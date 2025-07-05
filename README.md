# 🧱 C++ Project Template

A modern, professional-grade C++ project template designed to streamline the development of robust, maintainable, and scalable software. This template integrates industry most common practices across build systems, testing, code quality, documentation, and automation — all preconfigured to support a clean and efficient development workflow, ready to use.

## 🚀 Features

- ✅ Modern **C++20** standard
- 🧪 **Unit testing** with `GoogleTest`, included as a Git submodule
- 🛡️ Built-in **Sanitizers** (AddressSanitizer, UndefinedBehaviorSanitizer, etc.) for early bug detection
- 📈 **Code coverage** analysis with report generation
- 🧹 **Static analysis** with `clang-tidy`
- 🎨 Consistent **code formatting** with `clang-format`
- 📄 Support for **automatic documentation generation** using `Doxygen`
- ⚙️ Clean and modular `Makefile` for build orchestration
- 🧠 Preconfigured **compiler warnings**, **Link-Time Optimization** (LTO), and optional **CI**-ready settings

## 🛠️ Clone & Setup

Clone the repository along with its dependencies (e.g. GoogleTest) :

```
git clone --recurse-submodules https://github.com/lucas-gtr/projecttemplate.git
```

## ▶️ Build & Run

The Makefile provides multiple build modes to suit various development and debugging scenarios :

- **Production build** (with optimizations, LTO and without sanitizers):

```
make run
```

- **Debug build** (with sanitizers and without LTO and optimizations for easier debugging):

```
make run-debug
```

These commands configure, build, and execute the main target.

## 🧪 Running Unit Tests

Unit tests are implemented using the `GoogleTest` framework and integrated into the build system.

To compile and run the test suite :

```
make run-tests
```

## 📈 Code Coverage

The project supports coverage tracking to assess test completeness and identify untested code paths.

To generate a coverage report :

```
make coverage
```

The resulting HTML report will be generated in : `tests/coverage_report/`

## 🧼 Formatting & Lintting

Ensure code quality and consistency with preconfigured static analysis and formatting tools:

- Format all source files using `clang-format`:

```
make format
```

- Lint all source files using `clang-tidy` :

```
make lint
```

- Run both:

```
make format-and-lint
```

Restrict formatting/linting to modified files compared to `origin/main` :

```
make format-diff
make lint-diff
make format-and-lint-diff
```

### Custom Options
- Specify a list of files to check :
```
make lint FILES="src/main.cpp include/MyHeader.hpp"
```

- Automatically apply clang-tidy suggested fixes :

```
make lint FIX=ON
```

## 📚 Documentation

Documentation is generated via `Doxygen`, configured in `docs/Doxygen.in`

To generate the HTML documentation :

```
make documentation
```

The output will be located in : `docs/html/`

