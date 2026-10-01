#include "player.h"

#include "world.h"

Player::Player(Vec3 start) : position_(start), path_{start} {}

bool Player::move(const Vec3& direction) {
    Vec3 next = position_ + direction;
    if (!World::inBounds(next)) {
        return false;
    }
    position_ = next;
    path_.push_back(next);
    return true;
}
