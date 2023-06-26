#include "Alphatron.h"

#include "GameWorld.h"
#include "RedBullet.h"
#include "Explosion.h"

Alphatron::Alphatron(int x, int y, int hp, GameWorld* world, int attack, int speed)
  : AlienShip(IMGID_ALPHATRON, x, y, world, hp, 20, attack, speed) {}

Alphatron::~Alphatron() {}

void Alphatron::ReactToPlayer() {
  int xDiff = GetWorld()->GetDawnbreaker()->GetX() - GetX();
  if (std::abs(xDiff) <= 10 && GetEnergy() >= 50 && randInt(1, 4) <= 1) {
    SetEnergy(GetEnergy() - 50);
    GetWorld()->Instantiate(new RedBullet(GetX(), GetY() - 50, 180, 0.5, GetWorld(), GetAttack()));
  }
  if (GetEnergy() < 50) {
    SetEnergy(GetEnergy() + 2);
  }

}

void Alphatron::OnDestroy() {
  GetWorld()->Instantiate(new Explosion(GetX(), GetY(), GetWorld()));
  GetWorld()->RecordAnEnemyDestroyed();
  GetWorld()->IncreaseScore(50);
}

