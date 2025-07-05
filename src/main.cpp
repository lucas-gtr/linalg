#include <chrono>
#include <iostream>

#include "ModuleExample/Example.hpp"
#include "SanitizerTests.hpp"

void testOptimization() {
  constexpr size_t iterations = 1'000'000'000;

  auto start = std::chrono::high_resolution_clock::now();

  long long sum = 0;
  for(size_t i = 0; i < iterations; ++i) {
    sum += i;
  }

  auto end = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed = end - start;

  std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";
}

int main(int argc, char* argv[]) {
  // testAddressSanitizer();
  // testUndefinedBehaviorSanitizer();
  // testLeakSanitizer();
  // testSignedIntegerOverflow();
  // testFloatDivideByZero();
  // testOptimization();

  Example calculator;

  int a = 5;
  int b = 10;

  int result = calculator.add(a, b);

  std::cout << "Result of addition: " << result << std::endl;

  return 0;
}