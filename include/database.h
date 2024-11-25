#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <memory> 

#include "collection.h"

namespace Raidillon
{
class Database
{
public:
    Database(const std::string& name);
    ~Database();

    // コレクションを追加する関数
    Collection* createCollection(const std::string& collectionName);

private:
    std::string name_;
    std::vector<std::unique_ptr<Collection>> collections_;
};
} // namespace Raidillon

#endif // DATABASE_H