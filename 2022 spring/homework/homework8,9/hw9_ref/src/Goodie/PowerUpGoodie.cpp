#include "PowerUpGoodie.h"

#include "GameWorld.h"

PowerUpGoodie::PowerUpGoodie(int x, int y, GameWorld* world)
  : Goodie(IMGID_POWERUP_GOODIE, x, y, world) {}

PowerUpGoodie::~PowerUpGoodie() {}

void PowerUpGoodie::OnDestroy() {
  GetWorld()->GetDawnbreaker()->PowerUp();
  GetWorld()->IncreaseScore(20);
}
