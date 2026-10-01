#include "catch_amalgamated.hpp"

#include "config.h"
#include "player.h"

TEST_CASE("a new player is at the start with no moves", "[player]") {
    Player player({0, 0, 0});
    CHECK(player.position() == Vec3{0, 0, 0});
    CHECK(player.path().size() == 1);
    CHECK(player.moveCount() == 0);
}

TEST_CASE("moving updates the position and path", "[player]") {
    Player player({0, 0, 0});
    CHECK(player.move({1, 0, 0}));
    CHECK(player.move({0, -1, 0}));

    CHECK(player.position() == Vec3{1, -1, 0});
    CHECK(player.moveCount() == 2);
    REQUIRE(player.path().size() == 3);
    CHECK(player.path()[1] == Vec3{1, 0, 0});
    CHECK(player.path()[2] == Vec3{1, -1, 0});
}

TEST_CASE("the player cannot move through any wall", "[player]") {
    const int edge = config::kWorldLimit;
    Vec3 direction = GENERATE(values<Vec3>({{1, 0, 0}, {-1, 0, 0}, {0, 1, 0},
                                             {0, -1, 0}, {0, 0, 1}, {0, 0, -1}}));
    Vec3 atWall{direction.x * edge, direction.y * edge, direction.z * edge};

    Player player(atWall);
    CHECK_FALSE(player.move(direction));
    CHECK(player.position() == atWall);
    CHECK(player.moveCount() == 0);
}
