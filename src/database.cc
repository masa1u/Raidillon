#include "database.h"

namespace Raidillon
{
Database::Database(const std::string& name) : name_(name)
{
    // Constructor
}

Database::~Database()
{
    // Destructor
}

// コレクションを追加する関数
// コレクションを追加する関数
Collection* Database::createCollection(const std::string& collectionName)
{
    auto newCollection = std::make_unique<Collection>(collectionName);
    Collection* collectionPtr = newCollection.get();
    collections_.push_back(std::move(newCollection));
    return collectionPtr;
}
} // namespace Raidillon