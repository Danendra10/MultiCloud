#ifndef MULTICLOUD_TYPES_HPP_
#define MULTICLOUD_TYPES_HPP_

#pragma once

#include <memory>
#include <vector>

struct PointXYZ {
  float x, y, z;

  PointXYZ() : x(0), y(0), z(0) {}
  PointXYZ(float x, float y, float z) : x(x), y(y), z(z) {}
};

template<typename PointType>
class CloudSet {
  public:
    using Ptr = std::shared_ptr<CloudSet<PointType>>;

    CloudSet();
    void AddPoint(const PointType& point_in);
    size_t Size() const;
    void Clear();

  protected:
    std::vector<PointType> points;
};

#endif
