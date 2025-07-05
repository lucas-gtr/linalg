#include <cstdint>

// NOLINTBEGIN(clang-diagnostic-integer-overflow, clang-analyzer-cplusplus.NewDeleteLeaks,
// cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers, cppcoreguidelines-owning-memory,
// clang-diagnostic-division-by-zero, clang-analyzer-core.DivideZero)

void testAddressSanitizer() {
  int* array = new int[5];
  array[5]   = 42; // Buffer overflow (out-of-bounds write)
  delete[] array;
}

void testUndefinedBehaviorSanitizer() {
  int const x = 1;
  int const y = 0;
  int const z = x / y; // undefined behavior (division by zero)
  (void)z;
}

void testLeakSanitizer() {
  int* leak = new int[10]; // Memory leak
  (void)leak;
}

void testSignedIntegerOverflow() {
  int const max      = INT32_MAX;
  int const overflow = max + 1; // Overflow signed integer
  (void)overflow;
}

void testFloatDivideByZero() {
  float const a = 1.0F;
  float const b = 0.0F;
  float const c = a / b; // Float divide by zero
  (void)c;
}

// NOLINTEND(clang-diagnostic-integer-overflow, clang-analyzer-cplusplus.NewDeleteLeaks,
// cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers, cppcoreguidelines-owning-memory,
// clang-diagnostic-division-by-zero, clang-analyzer-core.DivideZero)