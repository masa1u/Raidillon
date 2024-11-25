#include "collection.h"
#include "index/flat.h"
#include "index/IVFFlat.h"
#include "utils/distance.h"

namespace Raidillon
{
int Collection::nextId_ = 0;
int Collection::nextDataId_ = 0;

Collection::Collection(const std::string& name)
    : name_(name), id_(nextId_++)
{
    // Constructor
}

Collection::~Collection()
{
    // Destructor
}

void Collection::insert(const std::vector<float>& data)
{
    data_.emplace_back(nextDataId_++, data);
}

Index* Collection::buildIndex(const std::string& indexType, const std::string& distanceType)
{
    std::unique_ptr<Distance> distance;

    if (distanceType == "euclidean") {
        distance = std::make_unique<EuclideanDistance>();
    } else if (distanceType == "cosine") {
        distance = std::make_unique<CosineSimilarity>();
    } else {
        std::cerr << "Error: Unknown distance type '" << distanceType << "'." << std::endl;
        return nullptr;
    } 

    if (indexType == "flat") {
        index_ = std::make_unique<FlatIndex>(std::move(distance));
    } else if(indexType == "IVFFlat") {
        std::cerr << "Error: IVFFlat index needs the number of clusters." << std::endl;
        return nullptr;
    }else {
        std::cerr << "Error: Unknown index type '" << indexType << "'." << std::endl;
        return nullptr;
    }

    if (index_) {
        index_->buildIndex(data_);
    }

    return index_.get();
}

Index* Collection::buildIndex(const std::string& indexType, const std::string& distanceType, int numClusters)
{
    std::unique_ptr<Distance> distance;

    if (distanceType == "euclidean") {
        distance = std::make_unique<EuclideanDistance>();
    } else if (distanceType == "cosine") {
        distance = std::make_unique<CosineSimilarity>();
    } else {
        std::cerr << "Error: Unknown distance type '" << distanceType << "'." << std::endl;
        return nullptr;
    } 

    if (indexType == "flat") {
        std::cerr << "Error: Flat index does not need the number of clusters." << std::endl;
        return nullptr;
    } else if(indexType == "IVFFlat") {
        index_ = std::make_unique<IVFFlatIndex>(std::move(distance));
    }else {
        std::cerr << "Error: Unknown index type '" << indexType << "'." << std::endl;
        return nullptr;
    }

    if (index_) {
        index_->buildIndex(data_, numClusters);
    }

    return index_.get();
}

const std::string& Collection::getName() const
{
    return name_;
}

int Collection::getId() const
{
    return id_;
}

const std::vector<std::pair<int, std::vector<float>>>& Collection::getData() const
{
    return data_;
}
} // namespace Raidillon