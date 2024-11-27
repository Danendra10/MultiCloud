#include <MultiCloud/types.hpp>
#include <gtest/gtest.h>

// Default Constructor Test
TEST(TypesTest, DefaultConstructor) {
  PointXYZ point;
  EXPECT_FLOAT_EQ(point.x, .0f);
  EXPECT_FLOAT_EQ(point.y, .0f);
  EXPECT_FLOAT_EQ(point.z, .0f);
}

// Test Parameterized Constructor
TEST(TypesTest, ParameterizedConstructor) {
  PointXYZ point(1.0, 2.0, 3.0);
  EXPECT_FLOAT_EQ(point.x, 1.0);
  EXPECT_FLOAT_EQ(point.y, 2.0);
  EXPECT_FLOAT_EQ(point.z, 3.0);
}

// Test Equality Operator
TEST(TypesTest, EqualityOperator) {
  PointXYZ p1(1.0, 2.0, 3.0);
  PointXYZ p2(1.0, 2.0, 3.0);
  PointXYZ p3(4.0, 5.0, 6.0);
  EXPECT_TRUE(p1 == p2);
  EXPECT_FALSE(p1 == p3);
}

// Test Output Operator
TEST(TypesTest, OutputOperator) {
  PointXYZ point(1.0, 2.0, 3.0);
  std::ostringstream oss;
  oss << point;
  EXPECT_EQ(oss.str(), "(1, 2, 3)\n");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
