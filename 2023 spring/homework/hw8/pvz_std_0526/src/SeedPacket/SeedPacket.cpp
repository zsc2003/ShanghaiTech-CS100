#include "SeedPacket.hpp"

#include "GameWorld.hpp"
#include "Spawn.hpp"
#include "Plants.hpp"
#include "Zombies/Zombies.hpp"
#include "utils.hpp"

SeedPacket::SeedPacket(ImageID imgID, int x, int y, pGameWorld world, int sunCost, int maxCoolDown)
  : GameObject(imgID, x, y, LAYER_UI, 50, 70, world, 1, 0), m_sunCost(sunCost), m_maxCoolDown(maxCoolDown), m_coolDownTime(0) {}

void SeedPacket::Update() {
  if (m_coolDownTime > 0) {
    m_coolDownTime--;
  }
}

void SeedPacket::OnClick() {
  if (!GetWorld()->IsHoldingShovel() && !GetWorld()->HasSpawn() && m_coolDownTime == 0 && GetWorld()->SpendSun(m_sunCost)) {
    CreateSpawn();
    GetWorld()->Instantiate(std::make_shared<SeedPacketCoolDown>(GetX(), GetY(), GetWorld(), m_maxCoolDown));
  }
}

SeedPacketCoolDown::SeedPacketCoolDown(int x, int y, pGameWorld world, int coolDown)
  : GameObject(IMGID_COOLDOWN_MASK, x, y, LAYER_COOLDOWN_MASK, 50, 70, world, 1, 0), m_coolDown(coolDown) {}

void SeedPacketCoolDown::Update() {
  if (--m_coolDown < 0) {
    TakeDamage(1);
  }
}

SunflowerSeed::SunflowerSeed(int x, int y, pGameWorld world)
  : SeedPacket(IMGID_SEED_SUNFLOWER, x, y, world, 50, 240) {}

void SunflowerSeed::CreateSpawn() {
  GetWorld()->SetSpawn(std::make_shared<Spawn<Sunflower>>(GetWorld()));
}

PeashooterSeed::PeashooterSeed(int x, int y, pGameWorld world)
  : SeedPacket(IMGID_SEED_PEASHOOTER, x, y, world, 100, 240) {}

void PeashooterSeed::CreateSpawn() {
  GetWorld()->SetSpawn(std::make_shared<Spawn<Peashooter>>(GetWorld()));
}

WallnutSeed::WallnutSeed(int x, int y, pGameWorld world)
  : SeedPacket(IMGID_SEED_WALLNUT, x, y, world, 50, 600) {}

void WallnutSeed::CreateSpawn() {
  GetWorld()->SetSpawn(std::make_shared<Spawn<Wallnut>>(GetWorld()));
}

CherryBombSeed::CherryBombSeed(int x, int y, pGameWorld world)
  : SeedPacket(IMGID_SEED_CHERRY_BOMB, x, y, world, 150, 1200) {}

void CherryBombSeed::CreateSpawn() {
  GetWorld()->SetSpawn(std::make_shared<Spawn<CherryBomb>>(GetWorld()));
}

RepeaterSeed::RepeaterSeed(int x, int y, pGameWorld world)
  : SeedPacket(IMGID_SEED_REPEATER, x, y, world, 200, 240) {}

void RepeaterSeed::CreateSpawn() {
  GetWorld()->SetSpawn(std::make_shared<Spawn<Repeater>>(GetWorld()));
}

ZombieSeed::ZombieSeed(int x, int y, pGameWorld world)
  : SeedPacket(IMGID_SEED_CHERRY_BOMB, x, y, world, 0, 0) {}

void ZombieSeed::CreateSpawn() {
  GetWorld()->SetSpawn(std::make_shared<Spawn<BucketHeadZombie>>(GetWorld()));
}