#include "Star.h"

Star::Star(int x, int y, double size, GameWorld* world)
  : Background(IMGID_STAR, x, y, 0, 4, size, world, 1) {}

Star::~Star() {}

void Star::UpdateActions() {
  MoveTo(GetX(), GetY() - 1);
}

