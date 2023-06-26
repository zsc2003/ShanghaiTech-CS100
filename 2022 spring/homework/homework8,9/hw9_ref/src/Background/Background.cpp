#include "Background.h"

Background::Background(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world, int hp)
  : GameObject(imageID, x, y, direction, layer, size, world, hp, 0) {}

Background::~Background() {}

bool Background::IsEnemy() const {
  return false;
}

GameObject::Type Background::GetType() const {
  return GameObject::Type::BACKGROUND;
}

