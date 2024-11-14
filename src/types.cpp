#include <MultiCloud/types.hpp>

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
