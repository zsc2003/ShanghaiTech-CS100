#include "BlueBullet.h"

BlueBullet::BlueBullet(int x, int y, double size, GameWorld* world, int collisionDamage)
  : Projectile(IMGID_BLUE_BULLET, x, y, 0, size, world, 1, collisionDamage) {}

BlueBullet::~BlueBullet() {}

bool BlueBullet::IsEnemy() const {
  return false;
}

void BlueBullet::UpdateActions() {
  MoveTo(GetX(), GetY() + 6);
}
