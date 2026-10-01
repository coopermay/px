#pragma once

namespace config {

// The player can move anywhere with every coordinate in [-kWorldLimit, kWorldLimit].
inline constexpr int kWorldLimit = 29;

// The treasure and bombs spawn with every coordinate in [-kSpawnLimit, kSpawnLimit].
inline constexpr int kSpawnLimit = 25;

inline constexpr int kMinBombs = 10;
inline constexpr int kMaxBombs = 40;

// The treasure is always at least this many moves from the start.
inline constexpr int kMinTreasureDistance = 10;

// Entering any cell within this Chebyshev distance of a bomb sets it off (a 3x3x3 cube).
inline constexpr int kKillRadius = 1;

// Bombs spawn at least this far (Chebyshev) from the start and the treasure, so the
// first move and the final approach to the treasure are always safe.
inline constexpr int kBombClearance = 3;

}  // namespace config
