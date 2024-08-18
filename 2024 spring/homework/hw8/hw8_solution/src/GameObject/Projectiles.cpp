#include "pvz/GameObject/Projectiles.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

void RedPea::Update() {
  auto targetZombie = GetWorld()->GetLeftmostZombie();
  if (targetZombie != nullptr) {
    auto xdiff = targetZombie->GetX() - GetX();
    auto ydiff = targetZombie->GetY() - GetY();
    auto diffNorm = std::sqrt(xdiff * xdiff + ydiff * ydiff);

    auto inertiaRatioX = 0.85;
    auto inertiaRatioY = 0.85;
    auto rawVelocityX = inertiaRatioX * (m_velocityX / 8.0) + (1.0 - inertiaRatioX) * (xdiff / diffNorm);
    auto rawVelocityY = inertiaRatioY * (m_velocityY / 8.0) + (1.0 - inertiaRatioY) * (ydiff / diffNorm);
    auto velocityNorm = std::sqrt(rawVelocityX * rawVelocityX + rawVelocityY * rawVelocityY);

    m_velocityX = rawVelocityX / velocityNorm * 8;
    m_velocityY = rawVelocityY / velocityNorm * 8;
  }

  MoveTo(GetX() + m_velocityX, GetY() + m_velocityY);
  if (GetX() >= WINDOW_WIDTH || GetX() < 0 || GetY() >= WINDOW_HEIGHT || GetY() < 0)
    SetDead();
}

void RedPea::Hit(GameObject &other) {
  if (!other.IsZombie())
    return;
  other.DecreaseHP(GetAttack());
  SetDead();
  if (randInt(1, 30) == 1)
    GetWorld()->AddObject<Explosion>(GetX(), GetY(), GetWorld());
}