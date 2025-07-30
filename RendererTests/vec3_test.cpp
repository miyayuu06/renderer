#include "pch.h"
#include "..\src\vec3.cpp"

using namespace Renderer;

TEST(Vec3Test, DefaultConstructor) {
    Vec3 v;
    EXPECT_DOUBLE_EQ(v[0], 0.0);
    EXPECT_DOUBLE_EQ(v[1], 0.0);
    EXPECT_DOUBLE_EQ(v[2], 0.0);
}

TEST(Vec3Test, ValueConstructor) {
    Vec3 v(1.5, -2.5, 3.0);
    EXPECT_DOUBLE_EQ(v[0], 1.5);
    EXPECT_DOUBLE_EQ(v[1], -2.5);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(Vec3Test, Length) {
    Vec3 v(3, 4, 0);
    EXPECT_DOUBLE_EQ(v.length(), 5.0);
}

TEST(Vec3Test, Addition) {
    Vec3 v1(1, 2, 3);
    Vec3 v2(4, 5, 6);
    Vec3 sum = v1 + v2;
    EXPECT_DOUBLE_EQ(sum[0], 5);
    EXPECT_DOUBLE_EQ(sum[1], 7);
    EXPECT_DOUBLE_EQ(sum[2], 9);
}

TEST(Vec3Test, DotProduct) {
    Vec3 v1(1, 3, -5);
    Vec3 v2(4, -2, -1);
    double dot = v1.dot(v2);
    EXPECT_DOUBLE_EQ(dot, 3);
}

TEST(Vec3Test, CrossProduct) {
    Vec3 v1(1, 0, 0);
    Vec3 v2(0, 1, 0);
    Vec3 cross = v1.cross(v2);
    EXPECT_DOUBLE_EQ(cross[0], 0);
    EXPECT_DOUBLE_EQ(cross[1], 0);
    EXPECT_DOUBLE_EQ(cross[2], 1);
}

TEST(Vec3Test, Normalize) {
    Vec3 v(3, 0, 4);
    Vec3 norm = v.norm();
    EXPECT_NEAR(norm.length(), 1.0, 1e-6);
    EXPECT_NEAR(norm[0], 0.6, 1e-6);
    EXPECT_NEAR(norm[1], 0.0, 1e-6);
    EXPECT_NEAR(norm[2], 0.8, 1e-6);
}
