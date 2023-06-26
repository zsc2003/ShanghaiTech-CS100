#include "Goodie.h"

Goodie::Goodie(int imageID, int x, int y, GameWorld* world)
  : GameObject(imageID, x, y, 0, 2, 0.5, world, 1, 0) {
}

Goodie::~Goodie() {}

bool Goodie::IsEnemy() const {
  return false;
}

void Goodie::UpdateActions() {
  MoveTo(GetX(), GetY() - 2);
}

GameObject::Type Goodie::GetType() const {
  return GameObject::Type::GOODIE;
}

