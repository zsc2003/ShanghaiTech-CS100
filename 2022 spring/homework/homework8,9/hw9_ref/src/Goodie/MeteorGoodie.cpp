#include "MeteorGoodie.h"

#include "GameWorld.h"

MeteorGoodie::MeteorGoodie(int x, int y, GameWorld* world)
  : Goodie(IMGID_METEOR_GOODIE, x, y, world) {}

MeteorGoodie::~MeteorGoodie() {}

void MeteorGoodie::OnDestroy() {
  GetWorld()->GetDawnbreaker()->GainMeteor();
  GetWorld()->IncreaseScore(20);
}
