#include "pvz/GameObject/Environment.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

void PlantingSpot::OnClick() {
  if (GetWorld()->HasSelectedSeed())
    GetWorld()->ReleaseSelectedSeed(GetX(), GetY());
}

void Sun::Update() {
  --m_dropTime;
  if (m_dropTime >= 0) {
    if (m_isFromSky)
      MoveTo(GetX(), GetY() + m_velocityY);
    else {
      MoveTo(GetX() - 1, GetY() + m_velocityY);
      --m_velocityY;
    }
  } else
    DecreaseHP(1);
}

void Sun::OnClick() {
  SetDead();
  GetWorld()->IncreaseSunlight(25);
}