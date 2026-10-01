#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ostream>

// A point (or direction) on the game grid. y is the vertical axis.
struct Vec3 {
    int x = 0;
    int y = 0;
    int z = 0;
};

inline bool operator==(const Vec3& a, const Vec3& b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

inline bool operator!=(const Vec3& a, const Vec3& b) {
    return !(a == b);
}

inline Vec3 operator+(const Vec3& a, const Vec3& b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

// Straight-line distance, used for the thermometer.
inline double euclideanDistance(const Vec3& a, const Vec3& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Fewest moves between two points, since each move changes one axis by 1.
inline int manhattanDistance(const Vec3& a, const Vec3& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
}

// Largest distance along any single axis. Points within Chebyshev distance r
// of a center form a (2r+1)x(2r+1)x(2r+1) cube around it.
inline int chebyshevDistance(const Vec3& a, const Vec3& b) {
    return std::max({std::abs(a.x - b.x), std::abs(a.y - b.y), std::abs(a.z - b.z)});
}
