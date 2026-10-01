#include <iostream>
#include <optional>
#include <random>
#include <stdexcept>
#include <string>

#include "game.h"
#include "replay.h"
#include "world.h"

namespace {

void printIntro(std::ostream& out) {
    out << " *** Welcome to Terminal Treasure Hunter *** \n"
        << "GOAL: Navigate to the treasure and avoid bombs\n"
        << "MOVEMENT:\n"
        << " 'W' increases x value\n"
        << " 'S' decreases x value\n"
        << " 'A' decreases z value\n"
        << " 'D' increases z value\n"
        << " '-' increases y value\n"
        << " 'C' decreases y value\n"
        << " 'X' quits\n"
        << "Enter your moves individually or combined!\n";
}

// Returns the seed from `--seed N`, a random seed if no arguments were given,
// or nothing if the arguments are invalid.
std::optional<unsigned> parseSeed(int argc, char* argv[]) {
    if (argc == 1) {
        return std::random_device{}();
    }
    if (argc == 3 && std::string(argv[1]) == "--seed") {
        try {
            return static_cast<unsigned>(std::stoul(argv[2]));
        } catch (const std::exception&) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

}  // namespace

int main(int argc, char* argv[]) {
    std::optional<unsigned> seed = parseSeed(argc, argv);
    if (!seed) {
        std::cerr << "usage: " << argv[0] << " [--seed N]\n";
        return 1;
    }

    printIntro(std::cout);
    std::cout << "Map seed: " << *seed << " (play this map again with --seed " << *seed << ")\nGO!\n";

    std::mt19937 rng(*seed);
    Vec3 start{0, 0, 0};
    Game game(World::generate(start, rng), start);
    game.run(std::cin, std::cout);

    saveReplay(game.world(), game.player().path());
    showReplay();
    return 0;
}
