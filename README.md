# Raidillon

Raidillon is a C++ library designed for building and searching indices using customizable distance metrics. It supports various indexing methods such as Flat and IVF-Flat, and allows for efficient similarity search in high-dimensional spaces.

## Build Instructions

To build the project, follow these steps:
```
mkdir build
cd build
cmake ..
make
```

## Usage

### C++ Example
To use the `Flat.cc` sample code, follow these steps:
```
cd build
./exmaples/cpp/Flat
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

    for (int i = 0; i < 100; ++i) {
        std::vector<float> data = {static_cast<float>(dis(gen)), static_cast<float>(dis(gen)), static_cast<float>(dis(gen))};
        collection->insert(data);
    }

    // インデックスを作成
    Raidillon::Index* index = collection->buildIndex("flat", "euclidean");

    // 検索クエリ
    std::vector<float> query = {1.0, 2.0, 3.0};
    int top_k = 5;
    std::vector<int> nearestIds = index->search(query, top_k);

    // 検索結果を表示
    std::cout << "Top " << top_k << " nearest IDs: ";
    for (int id : nearestIds) {
        std::cout << id << " ";
    }
    std::cout << std::endl;

    return 0;
}
```

### Python Example
To use the library in Python, follow these steps:

1. Add the pybind11 submodule:
```
git submodule add https://github.com/pybind/pybind11.git bindings/python/pybind11
git submodule update --init
```

2. Install setuptools if you haven't already:
```
pip install setuptools
```

3. Build the project:
```
mkdir build
cd build
cmake ..
make
```

4. Install the Python bindings:
```
cd ../bindings/python
python setup.py install
```

5. Create a Python script (e.g., test_raidillon.py) with the following content:
```
import raidillon_bindings as rb
import random

# データベースを作成
db = rb.Database("MyDatabase")

# コレクションを作成
collection = db.createCollection("MyCollection")

# ランダムなデータを生成してコレクションにインサート
for i in range(100):
    data = [random.uniform(0.0, 10.0) for _ in range(3)]
    collection.insert_with_id(i, data)

# インデックスを作成
index = collection.buildIndex("flat", "euclidean")

# 検索クエリ
query = [1.0, 2.0, 3.0]
top_k = 5
nearest_results = index.search(query, top_k)

# 検索結果を表示
print(f"Top {top_k} nearest IDs and distances: {nearest_results}")
```

6. Run the Python script:
```
python test_raidillon.py
```