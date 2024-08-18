#include "pvz/GameObject/Plants.hpp"
#include "pvz/GameObject/Environment.hpp"
#include "pvz/GameObject/Projectiles.hpp"

void Sunflower::Update() {
  if (--m_sunTimer == 0) {
    GetWorld()->AddObject(Sun::CreateFromSunflower(*this, GetWorld()));
    m_sunTimer = PRODUCE_COOLDOWN;
  }
}

void Peashooter::Update() {
  if (m_peaTimer > 0)
    --m_peaTimer;
  if (m_peaTimer == 0 && GetWorld()->HasZombieOnRightOf(*this)) {
    GetWorld()->AddObject<Pea>(GetX() + 30, GetY() + 20, GetWorld());
    m_peaTimer = ATTACK_COOLDOWN;
  }
}

void Wallnut::OnClick() {
  Plant::OnClick();
  if (!IsCracked())
    return;
  if (GetWorld()->HasSelectedSeed() && GetWorld()->SelectedIsWallnut()) {
    SetHP(HP_MAX);
    ChangeImage(ImageID::WALLNUT);
    GetWorld()->ResetSelectedSeed();
  }
}

void CherryBomb::Update() {
  if (--m_explodeTimer == 0) {
    GetWorld()->AddObject<Explosion>(GetX(), GetY(), GetWorld());
    SetDead();
  }
}

void Repeater::Update() {
  if (--m_secondPeaTimer == 0) {
    if (m_isRed) {
      GetWorld()->AddObject<RedPea>(GetX() + 30, GetY() + 20, GetWorld());
      ChangeImage(ImageID::REPEATER);
      m_isRed = false;
    } else
      GetWorld()->AddObject<Pea>(GetX() + 30, GetY() + 20, GetWorld());
  }
  if (m_attackTimer > 0)
    --m_attackTimer;
  else {
    bool isFacingZombie = GetWorld()->HasZombieOnRightOf(*this);
    bool turnRed = randInt(1, isFacingZombie ? 10 : 100) == 1;
    bool shouldAttack = turnRed ? GetWorld()->GetLeftmostZombie() != nullptr : isFacingZombie;
    if (!shouldAttack)
      return;
    if (turnRed) {
      GetWorld()->AddObject<RedPea>(GetX() + 30, GetY() + 20, GetWorld());
      ChangeImage(ImageID::RED_REPEATER);
      m_isRed = true;
    } else
      GetWorld()->AddObject<Pea>(GetX() + 30, GetY() + 20, GetWorld());
    m_attackTimer = ATTACK_COOLDOWN;
    m_secondPeaTimer = SECOND_PEA_COOLDOWN;
  }
}
