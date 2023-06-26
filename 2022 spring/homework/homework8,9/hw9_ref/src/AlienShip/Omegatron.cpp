#include "Omegatron.h"

#include "GameWorld.h"
#include "RedBullet.h"
#include "Explosion.h"
#include "PowerUpGoodie.h"
#include "MeteorGoodie.h"

Omegatron::Omegatron(int x, int y, int hp, GameWorld* world, int attack, int speed)
  : AlienShip(IMGID_OMEGATRON, x, y, world, hp, 20, attack, speed) {}

Omegatron::~Omegatron() {}

void Omegatron::ReactToPlayer() {
  if (GetEnergy() >= 50) {
    SetEnergy(GetEnergy() - 50);
    GetWorld()->Instantiate(new RedBullet(GetX(), GetY() - 50, 162, 0.5, GetWorld(), GetAttack()));
    GetWorld()->Instantiate(new RedBullet(GetX(), GetY() - 50, 198, 0.5, GetWorld(), GetAttack()));
  }
  if (GetEnergy() < 50) {
    SetEnergy(GetEnergy() + 1);
  }
}

void Omegatron::OnDestroy() {
  GetWorld()->Instantiate(new Explosion(GetX(), GetY(), GetWorld()));
  if (randInt(1, 5) <= 2) {
    if (randInt(1, 5) <= 4) {
      GetWorld()->Instantiate(new PowerUpGoodie(GetX(), GetY(), GetWorld()));
    }
    else {
      GetWorld()->Instantiate(new MeteorGoodie(GetX(), GetY(), GetWorld()));
    }
  }
  GetWorld()->RecordAnEnemyDestroyed();
  GetWorld()->IncreaseScore(200);
}

