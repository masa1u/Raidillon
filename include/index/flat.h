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

    void buildIndex(const std::vector<std::pair<int, std::vector<float>>>& data) override;
    std::vector<int> search(const std::vector<float>& query, int top_k) const override;

private:
    std::vector<std::pair<int, std::vector<float>>> indexedData_;
};
} // namespace Raidillon

#endif // FLAT_H