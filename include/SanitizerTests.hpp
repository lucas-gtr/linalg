/**
 * @file SanitizerTests.hpp
 * @brief Header file for sanitizer tests.
 */
#ifndef SANITIZERTESTS_HPP
#define SANITIZERTESTS_HPP

void testAddressSanitizer();
void testUndefinedBehaviorSanitizer();
void testLeakSanitizer();
void testSignedIntegerOverflow();
void testFloatDivideByZero();

#endif // SANITIZERTESTS_HPP