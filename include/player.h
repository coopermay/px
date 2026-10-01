#pragma once

#include <vector>

#include "vec3.h"

// The player's current position and every position they have visited.
class Player {
public:
    explicit Player(Vec3 start);

    // Moves one step in `direction`. Returns false (and stays put) if the step
    // would leave the world.
    bool move(const Vec3& direction);

    const Vec3& position() const { return position_; }
    const std::vector<Vec3>& path() const { return path_; }
    int moveCount() const { return static_cast<int>(path_.size()) - 1; }

private:
    Vec3 position_;
    std::vector<Vec3> path_;
};
