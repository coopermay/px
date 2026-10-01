#include "catch_amalgamated.hpp"

#include <sstream>
#include <string>

#include "config.h"
#include "game.h"

using Catch::Matchers::ContainsSubstring;

namespace {

const Vec3 kStart{0, 0, 0};

// Treasure two steps away along +x and no bombs.
Game simpleGame() {
    return Game(World({2, 0, 0}, {}), kStart);
}

}  // namespace

TEST_CASE("each movement key maps to one direction, in either case", "[game]") {
    CHECK(Game::directionFor('w') == Vec3{1, 0, 0});
    CHECK(Game::directionFor('S') == Vec3{-1, 0, 0});
    CHECK(Game::directionFor('d') == Vec3{0, 0, 1});
    CHECK(Game::directionFor('A') == Vec3{0, 0, -1});
    CHECK(Game::directionFor('-') == Vec3{0, 1, 0});
    CHECK(Game::directionFor('c') == Vec3{0, -1, 0});
    CHECK_FALSE(Game::directionFor('x').has_value());
    CHECK_FALSE(Game::directionFor('?').has_value());
}

TEST_CASE("reaching the treasure wins", "[game]") {
    Game game = simpleGame();
    CHECK(game.shortestPath() == 2);
    CHECK(game.handleKey('w') == Outcome::Playing);
    CHECK(game.handleKey('W') == Outcome::Won);
    CHECK(game.player().moveCount() == 2);
}

TEST_CASE("entering a kill zone explodes", "[game]") {
    Game game(World({10, 0, 0}, {{3, 0, 0}}), kStart);
    CHECK(game.handleKey('w') == Outcome::Playing);
    CHECK(game.handleKey('w') == Outcome::Exploded);
    CHECK(game.player().position() == Vec3{2, 0, 0});
}

TEST_CASE("x quits without moving", "[game]") {
    Game game = simpleGame();
    CHECK(game.handleKey('x') == Outcome::Quit);
    CHECK(game.handleKey('X') == Outcome::Quit);
    CHECK(game.player().moveCount() == 0);
}

TEST_CASE("unknown keys are ignored", "[game]") {
    Game game = simpleGame();
    CHECK(game.handleKey('?') == Outcome::Playing);
    CHECK(game.player().position() == kStart);
}

TEST_CASE("walls stop the player without ending the game", "[game]") {
    const Vec3 atWall{config::kWorldLimit, 0, 0};
    Game game(World({0, 0, 0}, {}), atWall);
    CHECK(game.handleKey('w') == Outcome::Playing);
    CHECK(game.player().position() == atWall);
    CHECK(game.player().moveCount() == 0);
}

TEST_CASE("thermometer readings change at each cutoff", "[game]") {
    CHECK(thermometerReading(150) == "absolutely freezing");
    CHECK(thermometerReading(86) == "absolutely freezing");
    CHECK(thermometerReading(85.9) == "iceberg");
    CHECK(thermometerReading(22) == "room temp");
    CHECK(thermometerReading(10) == "heating up");
    CHECK(thermometerReading(3) == "FLAMING HOT");
    CHECK(thermometerReading(2.9) == "SCORCHING");
    CHECK(thermometerReading(0) == "SCORCHING");
}

TEST_CASE("run plays a full game from an input stream", "[game][run]") {
    std::ostringstream out;

    SECTION("a perfect path scores 100%") {
        std::istringstream in("ww");
        Game game = simpleGame();
        CHECK(game.run(in, out) == Outcome::Won);
        CHECK_THAT(out.str(), ContainsSubstring("Treasure found, you win!"));
        CHECK_THAT(out.str(), ContainsSubstring("Moves: 2 (shortest possible: 2)"));
        CHECK_THAT(out.str(), ContainsSubstring("Efficiency: 100.0%"));
    }

    SECTION("a detour lowers efficiency") {
        std::istringstream in("d a w w");
        Game game = simpleGame();
        CHECK(game.run(in, out) == Outcome::Won);
        CHECK_THAT(out.str(), ContainsSubstring("Moves: 4 (shortest possible: 2)"));
        CHECK_THAT(out.str(), ContainsSubstring("Efficiency: 50.0%"));
    }

    SECTION("running out of input ends the game") {
        std::istringstream in("w");
        Game game = simpleGame();
        CHECK(game.run(in, out) == Outcome::Quit);
        CHECK_THAT(out.str(), ContainsSubstring("Location: 1, 0, 0"));
        CHECK_THAT(out.str(), ContainsSubstring("Thermometer: SCORCHING"));
    }

    SECTION("hitting a bomb prints game over") {
        std::istringstream in("www");
        Game game(World({10, 0, 0}, {{3, 0, 0}}), kStart);
        CHECK(game.run(in, out) == Outcome::Exploded);
        CHECK_THAT(out.str(), ContainsSubstring("BOOM!"));
    }
}
