#pragma once
#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include <string>
#include <utility> // for std::pair
#include <memory> // for std::unique_ptr
#include "index.h"

namespace Raidillon
{
class Collection
{
public:
    Collection(const std::string& name);
    ~Collection();

    void insert(const std::vector<float>& data);

    // インデックスの種類と距離関数を指定してインデックスを作成する関数
    Index* buildIndex(const std::string& indexType, const std::string& distanceType);
    Index* buildIndex(const std::string& indexType, const std::string& distanceType, int numClusters);

    const std::string& getName() const;
    int getId() const;
    const std::vector<std::pair<int, std::vector<float>>>& getData() const;

private:
    std::string name_;
    int id_;
    std::vector<std::pair<int, std::vector<float>>> data_;
    std::unique_ptr<Index> index_; // インデックスを保持するユニークポインタ

    static int nextId_; // 次のIDを生成するための静的変数
    static int nextDataId_; // 次のデータIDを生成するための静的変数
};
} // namespace Raidillon

#endif // COLLECTION_H