#include <MultiCloud/types.hpp>

std::ostream &operator<<(std::ostream &os, const PointXYZ &other) {
  os << "(" << other.x << ", " << other.y << ", " << other.z << ")" << std::endl;
  return os;
}

bool PointXYZ::operator==(const PointXYZ& other) const {
  return x == other.x &&
    y == other.y &&
    z == other.z;
}

template<typename PointType>
CloudSet<PointType>::CloudSet() = default;

template<typename PointType>
void CloudSet<PointType>::AddPoint(const PointType& point_in) {
  points.push_back(point_in);
}

template<typename PointType>
size_t CloudSet<PointType>::Size() const {
  return points.size();
}

template<typename PointType>
void CloudSet<PointType>::Clear() {
  points.clear();
}
