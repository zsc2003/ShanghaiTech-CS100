#include "UI.hpp"

#include "GameWorld.hpp"

Background::Background(pGameWorld world) : GameObject(IMGID_BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, LAYER_BACKGROUND, WINDOW_WIDTH, WINDOW_HEIGHT, world, 1, 0) {
  
}

LawnGrid::LawnGrid(int x, int y, pGameWorld world) : GameObject(IMGID_NONE, x, y, LAYER_UI, 60, 80, world, 1, 0) {
  
}

void LawnGrid::OnClick() {
  if (GetWorld()->HasSpawn()) {
    GetWorld()->GetSpawn()->MoveTo(GetX(), GetY());
    GetWorld()->GetSpawn()->TakeDamage(1);
  }
}

Sun::Sun(int x, int y, pGameWorld world, Source source) : GameObject(IMGID_SUN, x, y, LAYER_SUN, 80, 80, world, 1, 0, ANIMID_IDLE_ANIM),
  m_source(source),
  m_ySpeed(source == Sun::Source::Sky ? -2 : 4),
  m_dropTimer(source == Sun::Source::Sky ? randInt(63, 263) : 12),
  m_dieTimer(400) {}

void Sun::Update() {
  if (--m_dropTimer > 0) {
    switch (m_source) {
    case Sun::Source::Sky:
      MoveTo(GetX(), GetY() + m_ySpeed);
      break;
    case Sun::Source::Sunflower:
      MoveTo(GetX() - 1, GetY() + m_ySpeed);
      m_ySpeed--;
      break;
    default:
      break;
    }
  }
  else {
    if (--m_dieTimer <= 0) {
      TakeDamage(1);
    }
  }
}

void Sun::OnClick() {
  GetWorld()->SpendSun(-25);
  TakeDamage(1);
}

Shovel::Shovel(pGameWorld world)
  : GameObject(IMGID_SHOVEL, 600, WINDOW_HEIGHT - 40, LAYER_UI, 50, 50, world, 1, 0) {}

void Shovel::OnClick() {
  if (GetWorld()->HasSpawn()) {
    return;
  }
  else {
    GetWorld()->SetShovel(!GetWorld()->IsHoldingShovel());
  }
}

