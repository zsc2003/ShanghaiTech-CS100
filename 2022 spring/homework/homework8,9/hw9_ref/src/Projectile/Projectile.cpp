#include "Projectile.h"

Projectile::Projectile(int imageID, int x, int y, int direction, double size, GameWorld* world, int hp, int collisionDamage)
  : GameObject(imageID, x, y, direction, 1, size, world, hp, collisionDamage) {}

Projectile::~Projectile() {}

GameObject::Type Projectile::GetType() const {
  return GameObject::Type::PROJECTILE;
}
