#include "index/IVFFlat.h"
#include "utils/distance.h"
#include <limits>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <random>

namespace Raidillon
{
void IVFFlatIndex::buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data, int numClusters)
{
    dimension_ = data.front().second.size();
    numClusters_ = numClusters;

    // K-meansクラスタリングを実行してクラスタの中心を計算
    kMeansClustering(data);

    // 各データポイントを最も近いクラスタに割り当てる
    for (const auto& [id, point] : data) {
        int clusterId = findNearestCluster(point);
        clusters_[clusterId].emplace_back(id, point);
    }
}

std::vector<int> IVFFlatIndex::search(const std::vector<float>& query, int top_k, int nprobe) const
{
    // クエリポイントに最も近いクラスタを見つける
    std::vector<int> nearestClusters;
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>> pq;

    for (size_t i = 0; i < centroids_.size(); ++i) {
        float distance = distance_->compute(centroids_[i], query);
        pq.emplace(distance, i);
        if (pq.size() > nprobe) {
            pq.pop();
        }
    }

    while (!pq.empty()) {
        nearestClusters.push_back(pq.top().second);
        pq.pop();
    }

    // 選ばれたクラスタ内で検索を行う
    using DistancePair = std::pair<float, int>;
    std::priority_queue<DistancePair, std::vector<DistancePair>, std::greater<DistancePair>> resultPq;

    for (int clusterId : nearestClusters) {
        for (const auto& [id, point] : clusters_.at(clusterId)) {
            float distance = distance_->compute(point, query);
            resultPq.emplace(distance, id);
            if (resultPq.size() > top_k) {
                resultPq.pop();
            }
        }
    }

    std::vector<int> result;
    while (!resultPq.empty()) {
        result.push_back(resultPq.top().second);
        resultPq.pop();
    }

    std::reverse(result.begin(), result.end());
    return result;
}

int IVFFlatIndex::findNearestCluster(const std::vector<float>& point) const
{
    int nearestCluster = -1;
    float minDistance = std::numeric_limits<float>::max();

    for (size_t i = 0; i < centroids_.size(); ++i) {
        float distance = distance_->compute(centroids_[i], point);
        if (distance < minDistance) {
            minDistance = distance;
            nearestCluster = static_cast<int>(i);
        }
    }

    return nearestCluster;
}

void IVFFlatIndex::kMeansClustering(const std::vector<std::pair<int, std::vector<float>>>& data)
{
    // 初期クラスタの中心をランダムに選択
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, data.size() - 1);

    centroids_.resize(numClusters_);
    for (int i = 0; i < numClusters_; ++i) {
        centroids_[i] = data[dis(gen)].second;
    }

    // K-meansアルゴリズムを実行
    bool changed;
    do {
        changed = false;
        std::vector<std::vector<std::vector<float>>> newClusters(numClusters_);

        // 各ポイントを最も近いクラスタに割り当てる
        for (const auto& [id, point] : data) {
            int clusterId = findNearestCluster(point);
            newClusters[clusterId].push_back(point);
        }

        // 新しいクラスタの中心を計算
        for (int i = 0; i < numClusters_; ++i) {
            if (newClusters[i].empty()) continue;

            std::vector<float> newCentroid(dimension_, 0.0f);
            for (const auto& point : newClusters[i]) {
                for (size_t j = 0; j < dimension_; ++j) {
                    newCentroid[j] += point[j];
                }
            }
            for (size_t j = 0; j < newCentroid.size(); ++j) {
                newCentroid[j] /= newClusters[i].size();
            }

            if (distance_->compute(newCentroid, centroids_[i]) > 1e-4) {
                centroids_[i] = newCentroid;
                changed = true;
            }
        }
    } while (changed);
}
} // namespace Raidillon