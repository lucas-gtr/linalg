/**
 * @file Example.hpp
 * @brief Header file for the Example class.
 */
#ifndef MODULEEXAMPLE_EXAMPLE_HPP
#define MODULEEXAMPLE_EXAMPLE_HPP

/**
 * @class Example
 * @brief A simple example class that provides an add function.
 *
 * This class demonstrates a basic structure with a single method to add two integers.
 */
class Example {
public:
  /**
   * @brief Adds two integers.
   * @param a The first integer to add.
   * @param b The second integer to add.
   * @return The sum of the two integers.
   */
  static int add(int a, int b);
};

#endif // MODULEEXAMPLE_EXAMPLE_HPP