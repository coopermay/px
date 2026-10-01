#include "catch_amalgamated.hpp"

#include <cstdlib>
#include <random>

#include "config.h"
#include "world.h"

TEST_CASE("inBounds accepts the edge and rejects one past it", "[world]") {
    const int edge = config::kWorldLimit;
    CHECK(World::inBounds({0, 0, 0}));
    CHECK(World::inBounds({edge, -edge, edge}));
    CHECK_FALSE(World::inBounds({edge + 1, 0, 0}));
    CHECK_FALSE(World::inBounds({0, -edge - 1, 0}));
    CHECK_FALSE(World::inBounds({0, 0, edge + 1}));
}

TEST_CASE("the kill zone is the 3x3x3 cube around each bomb", "[world]") {
    World world({20, 0, 0}, {{5, 5, 5}});
    CHECK(world.isInKillZone({5, 5, 5}));
    CHECK(world.isInKillZone({6, 6, 6}));
    CHECK(world.isInKillZone({4, 5, 6}));
    CHECK_FALSE(world.isInKillZone({7, 5, 5}));
    CHECK_FALSE(world.isInKillZone({5, 3, 5}));
    CHECK_FALSE(World({20, 0, 0}, {}).isInKillZone({0, 0, 0}));
}

TEST_CASE("generated worlds follow the placement rules", "[world]") {
    const Vec3 start{0, 0, 0};
    auto withinSpawn = [](const Vec3& p) {
        return std::abs(p.x) <= config::kSpawnLimit && std::abs(p.y) <= config::kSpawnLimit &&
               std::abs(p.z) <= config::kSpawnLimit;
    };

    for (unsigned seed = 0; seed < 500; ++seed) {
        INFO("seed " << seed);
        std::mt19937 rng(seed);
        World world = World::generate(start, rng);

        REQUIRE(withinSpawn(world.treasure()));
        REQUIRE(manhattanDistance(start, world.treasure()) >= config::kMinTreasureDistance);
        int bombCount = static_cast<int>(world.bombs().size());
        REQUIRE(bombCount >= config::kMinBombs);
        REQUIRE(bombCount <= config::kMaxBombs);
        for (const Vec3& bomb : world.bombs()) {
            REQUIRE(withinSpawn(bomb));
            REQUIRE(chebyshevDistance(bomb, start) >= config::kBombClearance);
            REQUIRE(chebyshevDistance(bomb, world.treasure()) >= config::kBombClearance);
        }
        REQUIRE_FALSE(world.isInKillZone(start));
        REQUIRE_FALSE(world.isInKillZone(world.treasure()));
    }
}

TEST_CASE("the same seed always generates the same world", "[world]") {
    std::mt19937 rngA(1234);
    std::mt19937 rngB(1234);
    World a = World::generate({0, 0, 0}, rngA);
    World b = World::generate({0, 0, 0}, rngB);
    CHECK(a.treasure() == b.treasure());
    CHECK(a.bombs() == b.bombs());

    std::mt19937 rngC(5678);
    World c = World::generate({0, 0, 0}, rngC);
    CHECK((a.treasure() != c.treasure() || a.bombs() != c.bombs()));
}
