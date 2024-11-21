#ifndef DISTANCE_H
#define DISTANCE_H

#include <vector>
#include <cmath>
#include <limits>
#include <iostream>

namespace Raidillon
{
class Distance
{
public:
    virtual ~Distance() = default;

    // 純粋仮想関数として距離計算を行う関数
    virtual float compute(const std::vector<float>& a, const std::vector<float>& b) const = 0;
};

class EuclideanDistance : public Distance
{
public:
    float compute(const std::vector<float>& a, const std::vector<float>& b) const override
    {
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
};

class CosineSimilarity : public Distance
{
public:
    float compute(const std::vector<float>& a, const std::vector<float>& b) const override
    {
        if (a.size() != b.size()) {
            std::cerr << "Error: Vectors must be of the same dimension." << std::endl;
            return std::numeric_limits<float>::max();
        }

        float dotProduct = 0.0f;
        float normA = 0.0f;
        float normB = 0.0f;
        for (size_t i = 0; i < a.size(); ++i) {
            dotProduct += a[i] * b[i];
            normA += a[i] * a[i];
            normB += b[i] * b[i];
        }
        return dotProduct / (std::sqrt(normA) * std::sqrt(normB));
    }
};
} // namespace Raidillon

#endif // DISTANCE_H