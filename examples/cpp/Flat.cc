#include "database.h"
#include "collection.h"
#include "index.h"
#include <iostream>
#include <vector>
#include <random>
#include <cmath>

// ユークリッド距離を計算する関数
float computeEuclideanDistance(const std::vector<float>& a, const std::vector<float>& b) {
    if (a.size() != b.size()) {
        std::cerr << "Error: Vectors must be of the same dimension." << std::endl;
        return std::numeric_limits<float>::max();
    }

    float sum = 0.0f;
    for (size_t i = 0; i < a.size(); ++i) {
        float diff = a[i] - b[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

int main() {
    // データベースを作成
    Raidillon::Database db("MyDatabase");

    // コレクションを作成
    Raidillon::Collection* collection = db.createCollection("MyCollection");

    // ランダムなデータを生成してコレクションにインサート
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 10.0);

    // 検索クエリ
    std::vector<float> query = {1.0, 2.0, 3.0};

    for (int i = 0; i < 100; ++i) {
        std::vector<float> data = {static_cast<float>(dis(gen)), static_cast<float>(dis(gen)), static_cast<float>(dis(gen))};
        collection->insert(i, data);

        // 距離を計算してプリント
        // float distance = computeEuclideanDistance(data, query);
        // std::cout << "Inserted vector ID: " << i << ", Distance to query: " << distance << std::endl;
    }

    // インデックスを作成
    Raidillon::Index* index = collection->buildIndex("flat", "euclidean");

    // 検索クエリ
    int top_k = 5;
    std::vector<std::pair<int, float>> nearestResults = index->search(query, top_k);

    // 検索結果を表示
    std::cout << "Top " << top_k << " nearest IDs and distances: ";
    for (const auto& [id, distance] : nearestResults) {
        std::cout << "(" << id << ", " << distance << ") ";
    }
    std::cout << std::endl;

    return 0;
}