#ifndef MULTICLOUD_IO_HPP_
#define MULTICLOUD_IO_HPP_

#pragma once

#include <MultiCloud/types.hpp>
#include <memory>

template<typename PointType>
class MultiCloudIO : public CloudSet<PointType> {
  public:
    using Ptr = std::shared_ptr<MultiCloudIO<PointType>>;

    bool SaveToFile(const std::string& filename) const;
    bool LoadFromFile(const std::string& filename);
  private:
};

#endif
