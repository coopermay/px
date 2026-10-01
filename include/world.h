#pragma once

#include <random>
#include <vector>

#include "vec3.h"

// The fixed contents of one game: where the treasure and bombs are.
class World {
public:
    World(Vec3 treasure, std::vector<Vec3> bombs);

    // Builds a random, always-winnable world for a player starting at `start`.
    static World generate(Vec3 start, std::mt19937& rng);

    // Whether a position is inside the playable area.
    static bool inBounds(const Vec3& position);

    bool isInKillZone(const Vec3& position) const;

    const Vec3& treasure() const { return treasure_; }
    const std::vector<Vec3>& bombs() const { return bombs_; }

private:
    Vec3 treasure_;
    std::vector<Vec3> bombs_;
};
