#pragma once

#include <iosfwd>
#include <optional>
#include <string>

#include "player.h"
#include "vec3.h"
#include "world.h"

enum class Outcome { Playing, Won, Exploded, Quit };

// The thermometer message for a straight-line distance to the treasure.
std::string thermometerReading(double distance);

class Game {
public:
    Game(World world, Vec3 start);

    // The direction a movement key moves the player, or nothing for other keys.
    // Keys are case-insensitive.
    static std::optional<Vec3> directionFor(char key);

    // Applies one key press and reports the state of the game afterward.
    Outcome handleKey(char key);

    // Reads key presses from `in` and writes the game's text to `out` until
    // the game ends or input runs out.
    Outcome run(std::istream& in, std::ostream& out);

    // The fewest moves needed to reach the treasure.
    int shortestPath() const;

    const World& world() const { return world_; }
    const Player& player() const { return player_; }

private:
    World world_;
    Player player_;
    Vec3 start_;
};
