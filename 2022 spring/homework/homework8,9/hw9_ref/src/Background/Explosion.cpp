#include "Explosion.h"

Explosion::Explosion(int x, int y, GameWorld* world)
  : Background(IMGID_EXPLOSION, x, y, 0, 3, 4.5, world, 20) {}

Explosion::~Explosion() {}

void Explosion::UpdateActions() {
  SetSize(GetSize() - 0.2);
  SetHP(GetHP() - 1);
}
