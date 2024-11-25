#include "index/Flat.h"
#include <limits>
#include <queue>
#include <algorithm>
#include <utility> // for std::pair

namespace Raidillon
{
void FlatIndex::buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data, int numClusters)
{
    dimension_ = data.front().second.size();
    indexedData_ = data;
}

std::vector<std::pair<int, float>> FlatIndex::search(const std::vector<float>& query, int top_k, int nprobe) const
{
    using DistancePair = std::pair<float, int>;
    std::priority_queue<DistancePair, std::vector<DistancePair>, std::less<DistancePair>> pq;

    for (const auto& [id, vec] : indexedData_) {
        float distance = distance_->compute(vec, query);
        pq.emplace(distance, id);
        if (pq.size() > top_k) {
            pq.pop();
        }
    }

    std::vector<std::pair<int, float>> result;
    while (!pq.empty()) {
        result.emplace_back(pq.top().second, pq.top().first);
        pq.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;
}
} // namespace Raidillon
