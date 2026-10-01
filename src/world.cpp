#include "world.h"

#include <algorithm>
#include <cstdlib>
#include <utility>

#include "config.h"

World::World(Vec3 treasure, std::vector<Vec3> bombs)
    : treasure_(treasure), bombs_(std::move(bombs)) {}

World World::generate(Vec3 start, std::mt19937& rng) {
    std::uniform_int_distribution<int> coordinate(-config::kSpawnLimit, config::kSpawnLimit);
    auto randomPoint = [&] { return Vec3{coordinate(rng), coordinate(rng), coordinate(rng)}; };

    // Place the treasure first, far enough away that the game isn't trivial.
    Vec3 treasure;
    do {
        treasure = randomPoint();
    } while (manhattanDistance(start, treasure) < config::kMinTreasureDistance);

    std::uniform_int_distribution<int> bombCount(config::kMinBombs, config::kMaxBombs);
    int numBombs = bombCount(rng);
    std::vector<Vec3> bombs;
    while (static_cast<int>(bombs.size()) < numBombs) {
        Vec3 bomb = randomPoint();
        if (chebyshevDistance(bomb, start) >= config::kBombClearance &&
            chebyshevDistance(bomb, treasure) >= config::kBombClearance) {
            bombs.push_back(bomb);
        }
    }

    return World(treasure, std::move(bombs));
}

bool World::inBounds(const Vec3& position) {
    return std::abs(position.x) <= config::kWorldLimit &&
           std::abs(position.y) <= config::kWorldLimit &&
           std::abs(position.z) <= config::kWorldLimit;
}

bool World::isInKillZone(const Vec3& position) const {
    return std::any_of(bombs_.begin(), bombs_.end(), [&](const Vec3& bomb) {
        return chebyshevDistance(position, bomb) <= config::kKillRadius;
    });
}
