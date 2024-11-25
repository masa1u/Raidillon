# Raidillon

Raidillon is a C++ library for building and searching indices using customizable distance metrics.

## Build Instructions

To build the project, follow these steps:
```
mkdir build
cd build
cmake ..
make
```

## Usage

To use the `flat.cc` sample code, follow these steps:
```
cd build
./exmaples/cpp/flat
```

```flat.cc
#include "database.h"
#include "collection.h"
#include "index.h"
#include <iostream>
#include <vector>
#include <random>

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
    }

    // インデックスを作成
    Raidillon::Index* index = collection->buildIndex("flat", "euclidean");

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
```
