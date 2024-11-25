#ifndef FLAT_H
#define FLAT_H

#include "index.h"
#include <vector>
#include <utility> // for std::pair

namespace Raidillon
{
class FlatIndex : public Index
{
public:
    using Index::Index; // 親クラスのコンストラクタを使用

    void buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data, int numClusters=0) override;
    std::vector<std::pair<int, float>>  search(const std::vector<float>& query, int top_k, int nprobe=0) const override;

private:
    std::vector<std::pair<int, std::vector<float>>> indexedData_;
};
} // namespace Raidillon

#endif // FLAT_H