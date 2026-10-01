#include "replay.h"

#include <cstdlib>
#include <fstream>
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
    std::system("python visual.py");
#else
    std::system("python3 visual.py");
#endif
}
