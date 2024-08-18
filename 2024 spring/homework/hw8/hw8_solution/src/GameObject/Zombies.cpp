#include "pvz/GameObject/Zombies.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

void Zombie::Hit(GameObject &other) {
  if (!other.IsPlant())
    return;

  if (!IsWalking() && !IsEating())
    return;
  else if (IsWalking())
    PlayAnimation(AnimID::EAT);

  other.DecreaseHP(3);
}

void PoleVaultingZombie::Update() {
  if (IsRunning()) {
    MoveTo(GetX() - 40, GetY());
    if (GetWorld()->CollidesWithAnyPlant(*this)) {
      PlayAnimation(AnimID::JUMP);
      SetVelocity(0);
      m_jumpTimer = 42;
    }
    MoveTo(GetX() + 40, GetY());
  } else if (m_jumpTimer > 0) {
    if (--m_jumpTimer <= 0) {
      MoveTo(GetX() - 150, GetY());
      PlayAnimation(AnimID::WALK);
      SetVelocity(1);
    }
  }
  DefaultUpdate();
}