#include "Sigmatron.h"

#include "GameWorld.h"
#include "Explosion.h"
#include "HpRestoreGoodie.h"

Sigmatron::Sigmatron(int x, int y, int hp, GameWorld* world, int attack, int speed)
  : AlienShip(IMGID_SIGMATRON, x, y, world, hp, 20, attack, speed) {}

Sigmatron::~Sigmatron() {}

void Sigmatron::ReactToPlayer() {
  int xDiff = GetWorld()->GetDawnbreaker()->GetX() - GetX();
  if (std::abs(xDiff) <= 10) {
    SetStrategy(AlienShip::Strategy::DOWN);
    SetStrategyDuration(WINDOW_HEIGHT);
    SetSpeed(10);
  }
}

void Sigmatron::OnDestroy() {
  GetWorld()->Instantiate(new Explosion(GetX(), GetY(), GetWorld()));
  if (randInt(1, 5) <= 1) {
    GetWorld()->Instantiate(new HpRestoreGoodie(GetX(), GetY(), GetWorld()));
  }
  GetWorld()->RecordAnEnemyDestroyed();
  GetWorld()->IncreaseScore(100);
}

