#include "catch_amalgamated.hpp"

#include "vec3.h"

using Catch::Approx;

TEST_CASE("Vec3 equality and addition", "[vec3]") {
    Vec3 a{1, 2, 3};
    CHECK(a == Vec3{1, 2, 3});
    CHECK(a != Vec3{1, 2, 4});
    CHECK(a + Vec3{-1, 0, 2} == Vec3{0, 2, 5});
}

TEST_CASE("euclideanDistance is straight-line distance", "[vec3]") {
    CHECK(euclideanDistance({0, 0, 0}, {3, 4, 0}) == Approx(5.0));
    CHECK(euclideanDistance({1, 1, 1}, {1, 1, 1}) == Approx(0.0));
    CHECK(euclideanDistance({-1, -2, -2}, {0, 0, 0}) == Approx(3.0));
}

TEST_CASE("manhattanDistance counts single-axis steps", "[vec3]") {
    CHECK(manhattanDistance({0, 0, 0}, {1, -2, 3}) == 6);
    CHECK(manhattanDistance({5, 5, 5}, {5, 5, 5}) == 0);
    CHECK(manhattanDistance({-3, 0, 0}, {3, 0, 0}) == 6);
}

TEST_CASE("chebyshevDistance is the largest single-axis gap", "[vec3]") {
    CHECK(chebyshevDistance({0, 0, 0}, {1, -2, 3}) == 3);
    CHECK(chebyshevDistance({0, 0, 0}, {1, 1, 1}) == 1);
    CHECK(chebyshevDistance({4, 4, 4}, {4, 4, 4}) == 0);
}

TEST_CASE("distances are symmetric", "[vec3]") {
    Vec3 a{3, -7, 12};
    Vec3 b{-4, 2, 0};
    CHECK(euclideanDistance(a, b) == Approx(euclideanDistance(b, a)));
    CHECK(manhattanDistance(a, b) == manhattanDistance(b, a));
    CHECK(chebyshevDistance(a, b) == chebyshevDistance(b, a));
}
