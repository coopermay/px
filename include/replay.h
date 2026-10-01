#pragma once

#include <vector>

#include "vec3.h"
#include "world.h"

// Writes treasure.txt, bombs.txt and path_data.txt for visual.py.
void saveReplay(const World& world, const std::vector<Vec3>& path);

// Opens the 3D replay of the last saved game.
void showReplay();
