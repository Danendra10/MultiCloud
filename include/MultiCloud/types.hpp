#ifndef MULTICLOUD_TYPES_HPP_
#define MULTICLOUD_TYPES_HPP_

#pragma once

#include <cstddef>
#include <ostream>
#include <memory>
#include <vector>
#include <math.h>

struct PointXYZ {
  float x, y, z;

  PointXYZ() : x(0), y(0), z(0) {}
  PointXYZ(float x, float y, float z) : x(x), y(y), z(z) {}
  
  // Utilities Functions 
  float EuclideanDist(const PointXYZ& other);
  PointXYZ DistToPoint(const PointXYZ& other);
  // Operators
  friend std::ostream &operator<<(std::ostream &os, const PointXYZ &other);
  bool operator==(const PointXYZ& other) const;
};

struct PointNormal {
  float nx, ny, nz;

  PointNormal() : nx(0), ny(0), nz(0) {}
  PointNormal(float nx, float ny, float nz) : nx(nx), ny(ny), nz(nz) {}
};

struct TextureCoord {
  float u, v;

  TextureCoord(): u(0), v(0) {}
  TextureCoord(float u, float v): u(u), v(v) {}
};

struct MeshFace {
  int vert_1, vert_2, vert_3;

  MeshFace() : vert_1(0), vert_2(0), vert_3(0){}
  MeshFace(int vert_in_1, int vert_in_2, int vert_in_3): vert_1(vert_in_1), vert_2(vert_in_2), vert_3(vert_in_3) {}
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

template<typename VertType>
class MultiMesh {
  public:
    using Ptr = std::shared_ptr<MultiMesh<VertType>>;
    
    MultiMesh() = default;
    
    // Accessors
    size_t VertexCnt() const;
    size_t FaceCnt() const;
    size_t NormalCnt() const;
    size_t TextCoordCnt() const;
  protected:
    std::vector<VertType> vertices;
    std::vector<MeshFace> faces;
    std::vector<PointNormal> normals;
    std::vector<TextureCoord> texture_coords;
  private:
};

#endif
