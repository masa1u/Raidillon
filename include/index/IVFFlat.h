#ifndef IVFFLAT_H
#define IVFFLAT_H

#include "index.h"
#include <vector>
#include <utility> // for std::pair
#include <unordered_map>

namespace Raidillon
{
class IVFFlatIndex : public Index
{
public:
    using Index::Index; // 親クラスのコンストラクタを使用

    void buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data, int numClusters=0) override;
    std::vector<std::pair<int, float>> search(const std::vector<float>& query, int top_k, int nprobe=0) const override;

private:
    int numClusters_; // クラスタの数
    std::vector<std::vector<float>> centroids_; // クラスタの中心
    std::unordered_map<int, std::vector<std::pair<int, std::vector<float>>>> clusters_; // クラスタごとのデータ

    int findNearestCluster(const std::vector<float>& point) const;
    void kMeansClustering(const std::vector<std::pair<int, std::vector<float>>>& data);
};
} // namespace Raidillon

#endif // IVFFLAT_H