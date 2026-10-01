#include "replay.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

namespace {

void writePoints(const std::string& filename, const std::vector<Vec3>& points) {
    std::ofstream file(filename);
    for (const Vec3& p : points) {
        file << p.x << " " << p.y << " " << p.z << "\n";
    }
}

}  // namespace

void saveReplay(const World& world, const std::vector<Vec3>& path) {
    writePoints("treasure.txt", {world.treasure()});
    writePoints("bombs.txt", world.bombs());
    writePoints("path_data.txt", path);
}

void showReplay() {
#ifdef _WIN32
    const char* command = "python visual.py";
#else
    const char* command = "python3 visual.py";
#endif
    if (std::system(command) != 0) {
        std::cerr << "Couldn't open the replay. Make sure Python 3 and matplotlib are installed\n"
                  << "(pip3 install -r requirements.txt) and run the game from the project folder.\n";
    }
}
