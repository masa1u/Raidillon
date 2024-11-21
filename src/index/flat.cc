#include "index/flat.h"
#include <limits>
#include <queue>
#include <algorithm>
#include <utility> // for std::pair

namespace Raidillon
{
void FlatIndex::buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data)
{
    indexedData_ = data;
}

std::vector<int> FlatIndex::search(const std::vector<float>& query, int top_k) const
{
    using DistancePair = std::pair<float, int>;
    std::priority_queue<DistancePair, std::vector<DistancePair>, std::greater<DistancePair>> pq;

    for (const auto& [id, vec] : indexedData_) {
        float distance = distance_->compute(vec, query);
        pq.emplace(distance, id);
        if (pq.size() > top_k) {
            pq.pop();
        }
    }

    std::vector<int> result;
    while (!pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;
}
} // namespace Raidillon
