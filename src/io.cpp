#include "MultiCloud/types.hpp"
#include <MultiCloud/io.hpp>
#include <fstream>
#include <iostream>

template<typename PointType>
bool MultiCloudIO<PointType>::SaveToFile(const std::string& filename) const {
  std::ofstream file(filename);

  if(!file.is_open()) {
    std::cerr << "System failed to open file for: " << filename 
      << " Please check the permission" << std::endl;
    return false;
  }

  for(const PointXYZ& point : this->points) {
    file << point.x << " " << point.y << " " << point.z << "\n";
  }
  file.close();
  return true;
}

template<typename PointType>
bool MultiCloudIO<PointType>::LoadFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if(!file.is_open()) {
    std::cerr << "Failed to open file with name: " << filename 
      << " Please check if the file does exist" << std::endl;
    return false;
  }
  this->points.clear();
  float x, y, z;
  while(file >> x >> y >> z) {
    this->points.emplace_back(x, y, z);
  }
  file.close();
  return true;
}
