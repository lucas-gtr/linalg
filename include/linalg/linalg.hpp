/**
 * @file linalg.hpp
 * @brief Linear algebra utility functions for vectors and matrices.
 */
#ifndef LINALG_LINALG_HPP
#define LINALG_LINALG_HPP

#include <cmath>

#include "Mat3.hpp"
#include "Mat4.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

/**
 * @namespace linalg
 * @brief Namespace for linear algebra utility functions and classes.
 */
namespace linalg {

/**
 * @brief Converts a Vec4 to a Vec3
 * @param vec The Vec4 to convert.
 * @return A Vec3 with the x, y, and z components of the Vec4.
 */
template <typename T> inline Vec3<T> toVec3(const Vec4<T>& vec) { return {vec.x, vec.y, vec.z}; }

/**
 * @brief Converts a Vec3 to a Vec4 with w set to 1
 * @param vec The Vec3 to convert.
 * @return A Vec4 with the x, y, and z components of the Vec3 and w set to 1.
 */
template <typename T> inline Vec4<T> toVec4(const Vec3<T>& vec) { return {vec.x, vec.y, vec.z, static_cast<T>(1)}; }

/**
 * @brief Performs a dot product between two Vec2 vectors.
 * @param a The first Vec2 vector.
 * @param b The second Vec2 vector.
 * @return The dot product of the two Vec2 vectors.
 */
template <typename T> inline T dot(const Vec2<T>& a, const Vec2<T>& b) { return a.x * b.x + a.y * b.y; }

/**
 * @brief Performs a dot product between two Vec3 vectors.
 * @param a The first Vec3 vector.
 * @param b The second Vec3 vector.
 * @return The dot product of the two Vec3 vectors.
 */
template <typename T> inline T dot(const Vec3<T>& a, const Vec3<T>& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

/**
 * @brief Performs a dot product between two Vec4 vectors.
 * @param a The first Vec4 vector.
 * @param b The second Vec4 vector.
 * @return The dot product of the two Vec4 vectors.
 */
template <typename T> inline T dot(const Vec4<T>& a, const Vec4<T>& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

/**
 * @brief Returns the minimum value of two Vec2 vectors element-wise.
 * @param a The first Vec2 vector.
 * @param b The second Vec2 vector.
 * @return A Vec2 vector containing the minimum values of each component.
 */
template <typename T> inline Vec2<T> cwiseMin(const Vec2<T>& a, const Vec2<T>& b) {
  return {std::fmin(a.x, b.x), std::fmin(a.y, b.y)};
}

/**
 * @brief Returns the minimum value of two Vec3 vectors element-wise.
 * @param a The first Vec3 vector.
 * @param b The second Vec3 vector.
 * @return A Vec3 vector containing the minimum values of each component.
 */
template <typename T> inline Vec3<T> cwiseMin(const Vec3<T>& a, const Vec3<T>& b) {
  return {std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z)};
}

/**
 * @brief Returns the minimum value of two Vec4 vectors element-wise.
 * @param a The first Vec4 vector.
 * @param b The second Vec4 vector.
 * @return A Vec4 vector containing the minimum values of each component.
 */
template <typename T> inline Vec4<T> cwiseMin(const Vec4<T>& a, const Vec4<T>& b) {
  return {std::fmin(a.x, b.x), std::fmin(a.y, b.y), std::fmin(a.z, b.z), std::fmin(a.w, b.w)};
}

/**
 * @brief Returns the maximum value of two Vec2 vectors element-wise.
 * @param a The first Vec2 vector.
 * @param b The second Vec2 vector.
 * @return A Vec2 vector containing the maximum values of each component.
 */
template <typename T> inline Vec2<T> cwiseMax(const Vec2<T>& a, const Vec2<T>& b) {
  return {std::fmax(a.x, b.x), std::fmax(a.y, b.y)};
}

/**
 * @brief Returns the maximum value of two Vec3 vectors element-wise.
 * @param a The first Vec3 vector.
 * @param b The second Vec3 vector.
 * @return A Vec3 vector containing the maximum values of each component.
 */
template <typename T> inline Vec3<T> cwiseMax(const Vec3<T>& a, const Vec3<T>& b) {
  return {std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z)};
}

/**
 * @brief Returns the maximum value of two Vec4 vectors element-wise.
 * @param a The first Vec4 vector.
 * @param b The second Vec4 vector.
 * @return A Vec4 vector containing the maximum values of each component.
 */
template <typename T> inline Vec4<T> cwiseMax(const Vec4<T>& a, const Vec4<T>& b) {
  return {std::fmax(a.x, b.x), std::fmax(a.y, b.y), std::fmax(a.z, b.z), std::fmax(a.w, b.w)};
}

/**
 * @brief Clamps the elements of a Vec2 vector between two other Vec2 vectors.
 * @param a The Vec2 vector to clamp.
 * @param min The minimum Vec2 vector.
 * @param max The maximum Vec2 vector.
 * @return A Vec2 vector with each component clamped between the corresponding
 * components of min and max.
 */
template <typename T> inline Vec2<T> cwiseClamp(const Vec2<T>& a, const Vec2<T>& min, const Vec2<T>& max) {
  return {cwiseMin(cwiseMax(a, min), max)};
}

/**
 * @brief Clamps the elements of a Vec3 vector between two other Vec3 vectors.
 * @param a The Vec3 vector to clamp.
 * @param min The minimum Vec3 vector.
 * @param max The maximum Vec3 vector.
 * @return A Vec3 vector with each component clamped between the corresponding
 * components of min and
 */
template <typename T> inline Vec3<T> cwiseClamp(const Vec3<T>& a, const Vec3<T>& min, const Vec3<T>& max) {
  return {cwiseMin(cwiseMax(a, min), max)};
}

/**
 * @brief Clamps the elements of a Vec4 vector between two other Vec4 vectors.
 * @param a The Vec4 vector to clamp.
 * @param min The minimum Vec4 vector.
 * @param max The maximum Vec4 vector.
 * @return A Vec4 vector with each component clamped between the corresponding
 * components of min and max.
 */
template <typename T> inline Vec4<T> cwiseClamp(const Vec4<T>& a, const Vec4<T>& min, const Vec4<T>& max) {
  return {cwiseMin(cwiseMax(a, min), max)};
}

/**
 * @brief Returns the element-wise product of two Vec2 vectors.
 * @param a The first Vec2 vector.
 * @param b The second Vec2 vector.
 * @return A Vec2 vector containing the product of each component.
 */
template <typename T> inline Vec2<T> cwiseProduct(const Vec2<T>& a, const Vec2<T>& b) { return {a.x * b.x, a.y * b.y}; }

/**
 * @brief Returns the element-wise product of two Vec3 vectors.
 * @param a The first Vec3 vector.
 * @param b The second Vec3 vector.
 * @return A Vec3 vector containing the product of each component.
 */
template <typename T> inline Vec3<T> cwiseProduct(const Vec3<T>& a, const Vec3<T>& b) {
  return {a.x * b.x, a.y * b.y, a.z * b.z};
}

/**
 * @brief Returns the element-wise product of two Vec4 vectors.
 * @param a The first Vec4 vector.
 * @param b The second Vec4 vector.
 * @return A Vec4 vector containing the product of each component.
 */
template <typename T> inline Vec4<T> cwiseProduct(const Vec4<T>& a, const Vec4<T>& b) {
  return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

/**
 * @brief Returns the product of a Vec2 vector and a scalar.
 * @param scalar The scalar value to multiply with.
 * @param vec The Vec2 vector to multiply.
 * @return A Vec2 vector containing the product of each component with the
 * scalar.
 */
template <typename T> inline Vec2<T> operator*(T scalar, const Vec2<T>& vec) {
  return {vec.x * scalar, vec.y * scalar};
}

/**
 * @brief Returns the product of a Vec3 vector and a scalar.
 * @param scalar The scalar value to multiply with.
 * @param vec The Vec3 vector to multiply.
 * @return A Vec3 vector containing the product of each component with the
 * scalar.
 */
template <typename T> inline Vec3<T> operator*(T scalar, const Vec3<T>& vec) {
  return {vec.x * scalar, vec.y * scalar, vec.z * scalar};
}

/**
 * @brief Returns the product of a Vec4 vector and a scalar.
 * @param scalar The scalar value to multiply with.
 * @param vec The Vec4 vector to multiply.
 * @return A Vec4 vector containing the product of each component with the
 * scalar.
 */
template <typename T> inline Vec4<T> operator*(T scalar, const Vec4<T>& vec) {
  return {vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar};
}

/**
 * @brief Multiplies a Mat3 matrix vy a Vec3 vector.
 * @param mat The Mat3 matrix to multiply with.
 * @param vec The Vec3 vector to multiply.
 * @return A Vec3 vector resulting from the multiplication.
 */
template <typename T> inline Vec3<T> operator*(const Mat3<T>& mat, const Vec3<T>& vec) {
  return {mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z,
          mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z,
          mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z};
}

/**
 * @brief Multiplies a Mat4 matrix by a Vec4 vector.
 * @param mat The Mat4 matrix to multiply with.
 * @param vec The Vec4 vector to multiply.
 * @return A Vec4 vector resulting from the multiplication.
 */
template <typename T> inline Vec4<T> operator*(const Mat4<T>& mat, const Vec4<T>& vec) {
  return {mat.m[0][0] * vec.x + mat.m[0][1] * vec.y + mat.m[0][2] * vec.z + mat.m[0][3] * vec.w,
          mat.m[1][0] * vec.x + mat.m[1][1] * vec.y + mat.m[1][2] * vec.z + mat.m[1][3] * vec.w,
          mat.m[2][0] * vec.x + mat.m[2][1] * vec.y + mat.m[2][2] * vec.z + mat.m[2][3] * vec.w,
          mat.m[3][0] * vec.x + mat.m[3][1] * vec.y + mat.m[3][2] * vec.z + mat.m[3][3] * vec.w};
}

/**
 * @brief Returns a rotation matrix for the given angles around the x, y, and z
 * axes.
 * @param x_angle The angle in radians to rotate around the x-axis.
 * @param y_angle The angle in radians to rotate around the y-axis.
 * @param z_angle The angle in radians to rotate around the z-axis.
 * @return A Mat3 representing the combined rotation.
 */
template <typename T> inline Mat3<T> getRotationMatrix(T x_angle, T y_angle, T z_angle) {
  const T sin_x = std::sin(x_angle);
  const T cos_x = std::cos(x_angle);
  const T sin_y = std::sin(y_angle);
  const T cos_y = std::cos(y_angle);
  const T sin_z = std::sin(z_angle);
  const T cos_z = std::cos(z_angle);

  const Mat3<T> rx = Mat3<T>({{1, 0, 0}, {0, cos_x, -sin_x}, {0, sin_x, cos_x}});
  const Mat3<T> ry = Mat3<T>({{cos_y, 0, sin_y}, {0, 1, 0}, {-sin_y, 0, cos_y}});
  const Mat3<T> rz = Mat3<T>({{cos_z, -sin_z, 0}, {sin_z, cos_z, 0}, {0, 0, 1}});

  return rz * ry * rx;
}

} // namespace linalg

#endif // LINALG_LINALG_HPP
