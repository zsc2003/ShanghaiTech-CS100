#include "Plants.hpp"
#include "UI.hpp"

#include "GameWorld.hpp"
#include "Projectiles.hpp"

Plant::Plant(ImageID imgID, int x, int y, pGameWorld world, int hp) : GameObject(imgID, x, y, LAYER_PLANTS, 60, 80, world, hp, 1, ANIMID_IDLE_ANIM) {}

void Plant::OnClick() {
  if (GetWorld()->IsHoldingShovel()) {
    TakeDamage(4000);
    GetWorld()->SetShovel(false);
  }
}

Sunflower::Sunflower(int x, int y, pGameWorld world) : Plant(IMGID_SUNFLOWER, x, y, world, 300), m_sunCoolDown(randInt(30, 600)) {}

void Sunflower::Update() {
  if (--m_sunCoolDown <= 0) {
    GetWorld()->Instantiate(std::make_shared<Sun>(GetX(), GetY(), GetWorld(), Sun::Source::Sunflower));
    m_sunCoolDown = 600;
  }
}

Peashooter::Peashooter(int x, int y, pGameWorld world) : Plant(IMGID_PEASHOOTER, x, y, world, 300), m_attackCoolDown(0) {}

void Peashooter::Update() {
  if (m_attackCoolDown > 0) {
    --m_attackCoolDown;
  }
  else {
    if (GetWorld()->ShouldAttack(shared_from_this())) {
      GetWorld()->Instantiate(std::make_shared<Pea>(GetX() + 30, GetY() + 20, GetWorld()));
      m_attackCoolDown = 30;
    }
  }
}

Wallnut::Wallnut(int x, int y, pGameWorld world) : Plant(IMGID_WALLNUT, x, y, world, 4000) {}

void Wallnut::Update() {
  if (GetHP() <= 4000 / 3) {
    ChangeImage(IMGID_WALLNUT_CRACKED);
  }
}

CherryBomb::CherryBomb(int x, int y, pGameWorld world) : Plant(IMGID_CHERRY_BOMB, x, y, world, 300), m_explodeCounter(14) {}

void CherryBomb::Update() {
  if (--m_explodeCounter <= 0) {
    GetWorld()->Instantiate(std::make_shared<Explosion>(GetX(), GetY(), GetWorld()));
    TakeDamage(300);
  }
}

Repeater::Repeater(int x, int y, pGameWorld world) : Plant(IMGID_REPEATER, x, y, world, 300), m_attackCoolDown(0), m_secondPeaCounter(0) {}

void Repeater::Update() {
  if (--m_secondPeaCounter == 0) {
      GetWorld()->Instantiate(std::make_shared<Pea>(GetX() + 30, GetY() + 20, GetWorld()));
  }

  if (m_attackCoolDown > 0) {
    --m_attackCoolDown;
  }
  else {
    if (GetWorld()->ShouldAttack(shared_from_this())) {
      GetWorld()->Instantiate(std::make_shared<Pea>(GetX() + 30, GetY() + 20, GetWorld()));
      m_attackCoolDown = 30;
      m_secondPeaCounter = 5;
    }
  }
}