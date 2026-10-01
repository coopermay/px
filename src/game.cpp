#include "game.h"

#include <cctype>
#include <iomanip>
#include <istream>
#include <iterator>
#include <ostream>
#include <utility>

namespace {

struct ThermometerLevel {
    double minDistance;
    const char* label;
};

// Checked in order: the first level whose minimum the distance reaches wins.
constexpr ThermometerLevel kThermometer[] = {
    {86, "absolutely freezing"},
    {75, "iceberg"},
    {60, "COLD"},
    {40, "chilly"},
    {33, "getting a bit chilly"},
    {22, "room temp"},
    {15, "getting warmer"},
    {10, "heating up"},
    {7, "HOT"},
    {3, "FLAMING HOT"},
    {0, "SCORCHING"},
};

// Below this distance the thermometer also shows the exact distance.
constexpr double kShowDistanceBelow = 3;

void printLocation(std::ostream& out, const Vec3& position) {
    out << "Location: " << position.x << ", " << position.y << ", " << position.z << "\n";
}

}  // namespace

std::string thermometerReading(double distance) {
    for (const ThermometerLevel& level : kThermometer) {
        if (distance >= level.minDistance) {
            return level.label;
        }
    }
    return kThermometer[std::size(kThermometer) - 1].label;
}

Game::Game(World world, Vec3 start)
    : world_(std::move(world)), player_(start), start_(start) {}

std::optional<Vec3> Game::directionFor(char key) {
    switch (std::tolower(static_cast<unsigned char>(key))) {
        case 'w': return Vec3{1, 0, 0};
        case 's': return Vec3{-1, 0, 0};
        case 'd': return Vec3{0, 0, 1};
        case 'a': return Vec3{0, 0, -1};
        case '-': return Vec3{0, 1, 0};
        case 'c': return Vec3{0, -1, 0};
        default: return std::nullopt;
    }
}

Outcome Game::handleKey(char key) {
    if (std::tolower(static_cast<unsigned char>(key)) == 'x') {
        return Outcome::Quit;
    }
    if (std::optional<Vec3> direction = directionFor(key)) {
        player_.move(*direction);
    }
    if (world_.isInKillZone(player_.position())) {
        return Outcome::Exploded;
    }
    if (player_.position() == world_.treasure()) {
        return Outcome::Won;
    }
    return Outcome::Playing;
}

Outcome Game::run(std::istream& in, std::ostream& out) {
    printLocation(out, player_.position());

    char key;
    while (in >> key) {
        Outcome outcome = handleKey(key);
        if (outcome == Outcome::Quit) {
            return outcome;
        }
        if (directionFor(key)) {
            printLocation(out, player_.position());
        }

        if (outcome == Outcome::Exploded) {
            out << "BOOM! You entered the kill zone. Game over.\n";
            return outcome;
        }
        if (outcome == Outcome::Won) {
            int moves = player_.moveCount();
            out << "Treasure found, you win!\n";
            out << "Moves: " << moves << " (shortest possible: " << shortestPath() << ")\n";
            out << "Efficiency: " << std::fixed << std::setprecision(1)
                << (100.0 * shortestPath() / moves) << "%\n";
            return outcome;
        }

        double distance = euclideanDistance(player_.position(), world_.treasure());
        out << "Thermometer: " << thermometerReading(distance) << "\n";
        if (distance < kShowDistanceBelow) {
            out << "Distance: " << distance << "\n";
        }
    }
    return Outcome::Quit;
}

int Game::shortestPath() const {
    return manhattanDistance(start_, world_.treasure());
}
