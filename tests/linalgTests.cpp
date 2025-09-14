#include <gtest/gtest.h>
#include "linalg/linalg.hpp"

using namespace linalg;

constexpr double EPS = 1e-9;

TEST(LinConversionTest, ToVec3d) {
    Vec4d v4 = {1.0, 2.0, 3.0, 4.0};
    Vec3d v3 = toVec3(v4);
    EXPECT_DOUBLE_EQ(v3.x, 1.0);
    EXPECT_DOUBLE_EQ(v3.y, 2.0);
    EXPECT_DOUBLE_EQ(v3.z, 3.0);
}

TEST(LinConversionTest, ToVec4d) {
    Vec3d v3 = {1.0, 2.0, 3.0};
    Vec4d v4 = toVec4(v3);
    EXPECT_DOUBLE_EQ(v4.x, 1.0);
    EXPECT_DOUBLE_EQ(v4.y, 2.0);
    EXPECT_DOUBLE_EQ(v4.z, 3.0);
    EXPECT_DOUBLE_EQ(v4.w, 1.0);
}

TEST(LinDotProductTest, Dot2D) {
    Vec2 a = {1.0, 2.0};
    Vec2 b = {3.0, 4.0};
    EXPECT_DOUBLE_EQ(dot(a, b), 11.0);
}

TEST(LinDotProductTest, Dot3D) {
    Vec3d a = {1.0, 2.0, 3.0};
    Vec3d b(4.0);
    EXPECT_DOUBLE_EQ(dot(a, b), 24.0);
}

TEST(LinDotProductTest, Dot4D) {
    Vec4d a = {1.0, 2.0, 3.0, 4.0};
    Vec4d b = {5.0, 6.0, 7.0, 8.0};
    EXPECT_DOUBLE_EQ(dot(a, b), 70.0);
}

TEST(LinComponentWiseTest, MinMaxProduct2D) {
    Vec2 a = {1.0, 5.0};
    Vec2 b = {3.0, 2.0};
    EXPECT_EQ(cwiseMin(a, b), Vec2(1.0, 2.0));
    EXPECT_EQ(cwiseMax(a, b), Vec2(3.0, 5.0));
    EXPECT_EQ(cwiseProduct(a, b), Vec2(3.0, 10.0));
}

TEST(LinComponentWiseTest, MinMaxProduct3D) {
    Vec3d a = {1.0, 5.0, -2.0};
    Vec3d b = {3.0, 2.0, 4.0};
    EXPECT_EQ(cwiseMin(a, b), Vec3d(1.0, 2.0, -2.0));
    EXPECT_EQ(cwiseMax(a, b), Vec3d(3.0, 5.0, 4.0));
    EXPECT_EQ(cwiseProduct(a, b), Vec3d(3.0, 10.0, -8.0));
}

TEST(LinComponentWiseTest, MinMaxProduct4D) {
    Vec4d a = {1.0, 5.0, -2.0, 3.0};
    Vec4d b = {3.0, 2.0, 4.0, 7.0};
    EXPECT_EQ(cwiseMin(a, b), Vec4d(1.0, 2.0, -2.0, 3.0));
    EXPECT_EQ(cwiseMax(a, b), Vec4d(3.0, 5.0, 4.0, 7.0));
    EXPECT_EQ(cwiseProduct(a, b), Vec4d(3.0, 10.0, -8.0, 21.0));
}

TEST(LinScalarTest, ScalarMultiplication) {
    Vec2 v2 = {2.0, -1.0};
    Vec3d v3 = {1.0, 0.0, -1.0};
    Vec4d v4 = {1.0, 2.0, 3.0, 4.0};
    EXPECT_EQ(2.0 * v2, Vec2(4.0, -2.0));
    EXPECT_EQ(3.0 * v3, Vec3d(3.0, 0.0, -3.0));
    EXPECT_EQ(0.5 * v4, Vec4d(0.5, 1.0, 1.5, 2.0));
}

TEST(LinalgTest, ReflectVec3) {
    Vec3d incident = {1.0, -1.0, 0.0};
    Vec3d normal = {0.0, 1.0, 0.0};
    Vec3d reflected = incident - 2 * dot(incident, normal) * normal;
    EXPECT_EQ(reflected, Vec3d(1.0, 1.0, 0.0));

    incident = {0.0, -1.0, -1.0};
    normal = {0.0, 0.0, 1.0};
    reflected = incident - 2 * dot(incident, normal) * normal;
    EXPECT_EQ(reflected, Vec3d(0.0, -1.0, 1.0));
}

TEST(RefractTest, NormalIncidenceAirToGlass) {
  Vec3<double> I(0, 0, -1);
  Vec3<double> N(0, 0, 1);
  double eta = 1.0 / 1.5;
  Vec3<double> T = refract(I, N, eta);
  EXPECT_NEAR(T.x, 0.0, EPS);
  EXPECT_NEAR(T.y, 0.0, EPS);
  EXPECT_NEAR(T.z, -1.0, EPS);
}

TEST(RefractTest, NormalIncidenceGlassToAir) {
  Vec3<double> I(0, 0, -1);
  Vec3<double> N(0, 0, 1);
  double eta = 1.5 / 1.0;
  Vec3<double> T = refract(I, N, eta);
  EXPECT_NEAR(T.x, 0.0, EPS);
  EXPECT_NEAR(T.y, 0.0, EPS);
  EXPECT_NEAR(T.z, -1.0, EPS);
}

TEST(RefractTest, ObliqueIncidenceAirToGlass) {
  Vec3<double> I(0, std::sin(M_PI/6), -std::cos(M_PI/6));
  I = I.normalized();
  Vec3<double> N(0, 0, 1);
  double eta = 1.0 / 1.5;
  Vec3<double> T = refract(I, N, eta);
  EXPECT_LT(T.z, 0.0);
}

TEST(RefractTest, ObliqueIncidenceGlassToAirNoTIR) {
  Vec3<double> I(0, std::sin(M_PI/6), -std::cos(M_PI/6));
  I = I.normalized();
  Vec3<double> N(0, 0, 1);
  double eta = 1.5 / 1.0;
  Vec3<double> T = refract(I, N, eta);
  EXPECT_LT(T.z, 0.0);
}

TEST(RefractTest, TotalInternalReflection) {
  Vec3<double> I(0, std::sin(M_PI/3), -std::cos(M_PI/3));
  I = I.normalized();
  Vec3<double> N(0, 0, 1);
  double eta = 1.5 / 1.0;
  Vec3<double> T = refract(I, N, eta);
  Vec3<double> R = reflect(I, N);
  EXPECT_NEAR(T.x, R.x, EPS);
  EXPECT_NEAR(T.y, R.y, EPS);
  EXPECT_NEAR(T.z, R.z, EPS);
}

TEST(RefractTest, EtaEqualOne) {
  Vec3<double> I(0, 0, -1);
  Vec3<double> N(0, 0, 1);
  double eta = 1.0;
  Vec3<double> T = refract(I, N, eta);
  EXPECT_NEAR(T.x, I.x, EPS);
  EXPECT_NEAR(T.y, I.y, EPS);
  EXPECT_NEAR(T.z, I.z, EPS);
}

TEST(LinMatrixTest, Mat3dVec3dMultiplication) {
    Mat3d m({{1, 2, 3}, {0, 1, 4}, {5, 6, 0}});
    Vec3d v = {1, 2, 3};
    Vec3d result = m * v;
    EXPECT_EQ(result, Vec3d(14.0, 14.0, 17.0));
}

TEST(LinMatrixTest, Mat4dVec4dMultiplication) {
    Mat4d m({{1, 2, 3, 4},
            {5, 6, 7, 8},
            {9, 10, 11, 12},
            {13, 14, 15, 16}});
    Vec4d v = {1, 2, 3, 4};
    Vec4d result = m * v;
    EXPECT_EQ(result, Vec4d(30, 70, 110, 150));
}

TEST(LinRotationTest, RotationMatrixOrthogonality) {
    Mat3d rot = getRotationMatrix(0.1, 0.2, 0.3);
    Mat3d transposed = rot.transposed();
    Mat3d identity = rot * transposed;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            EXPECT_NEAR(identity.m[i][j], i == j ? 1.0 : 0.0, EPS);
}
