#include "Dawnbreaker.h"

#include "GameWorld.h"
#include "BlueBullet.h"
#include "Meteor.h"

Dawnbreaker::Dawnbreaker(int x, int y, GameWorld* world)
  : GameObject(IMGID_DAWNBREAKER, x, y, 0, 0, 1.0, world, MAX_HP, MAX_HP_LIMIT), m_energy(MAX_ENERGY), m_meteors(0), m_powerUpLevel(0) {}

Dawnbreaker::~Dawnbreaker() {}

void Dawnbreaker::UpdateActions() {

  if (GetWorld()->GetKey(KeyCode::LEFT)) {
    MoveTo((GetX() - 4 >= 0) ? GetX() - 4 : GetX(), GetY());
  }
  if (GetWorld()->GetKey(KeyCode::RIGHT)) {
    MoveTo((GetX() + 4 < WINDOW_WIDTH) ? GetX() + 4 : GetX(), GetY());
  }
  if (GetWorld()->GetKey(KeyCode::UP)) {
    MoveTo(GetX(), (GetY() + 4 < WINDOW_HEIGHT) ? GetY() + 4 : GetY());
  }
  if (GetWorld()->GetKey(KeyCode::DOWN)) {
    MoveTo(GetX(), (GetY() - 4 >= 50) ? GetY() - 4 : GetY());
  }
  if (GetWorld()->GetKey(KeyCode::FIRE1)) {
    if (m_energy >= 10) {
      m_energy -= 10;
      GetWorld()->Instantiate(new BlueBullet(GetX(), GetY() + 50, BASE_BULLET_SIZE + 0.1 * m_powerUpLevel, GetWorld(), BASE_ATTACK + 3 * m_powerUpLevel));
    }
  }

  if (GetWorld()->GetKeyDown(KeyCode::FIRE2)) {
    if (m_meteors > 0) {
      m_meteors--;
      GetWorld()->Instantiate(new Meteor(GetX(), GetY() + 100, GetWorld()));
    }
  }

  if (m_energy < MAX_ENERGY) {
    m_energy++;
  }

}

bool Dawnbreaker::IsEnemy() const {
  return false;
}

GameObject::Type Dawnbreaker::GetType() const {
  return GameObject::Type::SPACESHIP;
}

void Dawnbreaker::GainMeteor() {
  m_meteors++;
}

int Dawnbreaker::GetMeteors() const {
  return m_meteors;
}

void Dawnbreaker::PowerUp() {
  m_powerUpLevel++;
}
