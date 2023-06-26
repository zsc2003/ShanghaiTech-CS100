#include "Meteor.h"


Meteor::Meteor(int x, int y, GameWorld* world)
  : Projectile(IMGID_METEOR, x, y, 0, 2.0, world, MAX_HP_LIMIT, 100) {}

Meteor::~Meteor() {}

bool Meteor::IsEnemy() const {
  return false;
}

void Meteor::UpdateActions() {
  MoveTo(GetX(), GetY() + 2);
  SetDirection(GetDirection() + 5);
}
