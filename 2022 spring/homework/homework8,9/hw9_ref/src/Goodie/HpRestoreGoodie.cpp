#include "HpRestoreGoodie.h"

#include "GameWorld.h"

HpRestoreGoodie::HpRestoreGoodie(int x, int y, GameWorld* world)
  : Goodie(IMGID_HP_RESTORE_GOODIE, x, y, world) {}

HpRestoreGoodie::~HpRestoreGoodie() {}

void HpRestoreGoodie::OnDestroy() {
  GetWorld()->GetDawnbreaker()->RestoreHP(50);
  GetWorld()->IncreaseScore(20);
}
