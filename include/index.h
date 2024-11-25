#pragma once

#ifndef INDEX_H
#define INDEX_H

#include <vector>
#include <utility> // for std::pair
#include <string>
#include <memory> // for std::unique_ptr
#include "utils/distance.h"

namespace Raidillon
{
class Index
{
public:
    Index(std::unique_ptr<Distance> distance) : distance_(std::move(distance)) {}
    virtual ~Index() = default;

    // 純粋仮想関数としてインデックスを作成する関数
    virtual void buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data, int numClusters=0) = 0;

    // 純粋仮想関数としてインデックスに基づいて検索を行う関数
    virtual std::vector<std::pair<int, float>> search(const std::vector<float>& query, int top_k, int nprobe=0) const = 0;
protected:
    int dimension_;
    std::unique_ptr<Distance> distance_;
};
} // namespace Raidillon

#endif // INDEX_H