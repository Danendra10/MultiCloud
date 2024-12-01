#include <gtest/gtest.h>
#include <MultiCloud/point_visualizer.hpp>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  Visualizer visualizer;
  visualizer.Spin(1);
  return RUN_ALL_TESTS();
}
