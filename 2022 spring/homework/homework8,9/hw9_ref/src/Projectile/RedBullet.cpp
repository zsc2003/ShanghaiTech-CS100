#include "RedBullet.h"


RedBullet::RedBullet(int x, int y, int direction, double size, GameWorld* world, int collisionDamage)
  : Projectile(IMGID_RED_BULLET, x, y, direction, size, world, 1, collisionDamage) {}

RedBullet::~RedBullet() {}

bool RedBullet::IsEnemy() const {
  return true;
}

void RedBullet::UpdateActions() {
  MoveTo(GetX(), GetY() - 6);

  if (GetDirection() == 162) {
    MoveTo(GetX() + 2, GetY());
  }

  if (GetDirection() == 198) {
    MoveTo(GetX() - 2, GetY());
  }
}

