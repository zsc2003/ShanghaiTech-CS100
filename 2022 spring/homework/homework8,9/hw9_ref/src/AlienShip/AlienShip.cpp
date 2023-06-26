#include "AlienShip.h"

AlienShip::AlienShip(int imageID, int x, int y,
  GameWorld* world, int hp, int collisionDamage, int attack, int speed)
  : GameObject(imageID, x, y, 180, 0, 1.0, world, hp, collisionDamage),
  m_attack(attack), m_speed(speed), m_energy(50), m_strategy(AlienShip::Strategy::NONE),
  m_strategyDuration(0) {}

AlienShip::~AlienShip() {}

bool AlienShip::IsEnemy() const {
  return true;
}

GameObject::Type AlienShip::GetType() const {
  return GameObject::Type::SPACESHIP;
}

int AlienShip::GetAttack() const {
  return m_attack;
}

int AlienShip::GetSpeed() const {
  return m_speed;
}

void AlienShip::SetSpeed(int speed) {
  m_speed = speed;
}

int AlienShip::GetEnergy() const {
  return m_energy;
}

void AlienShip::SetEnergy(int energy) {
  m_energy = energy;
}

void AlienShip::GenerateStrategy() {
  switch (randInt(1, 3)) {
  case 1:
    m_strategy = AlienShip::Strategy::DOWN;
    break;
  case 2:
    m_strategy = AlienShip::Strategy::LEFTDOWN;
    break;
  case 3:
    m_strategy = AlienShip::Strategy::RIGHTDOWN;
    break;
  default:
    break;
  }
}

void AlienShip::GenerateStrategyDuration() {
  m_strategyDuration = randInt(10, 50);
}

void AlienShip::SetStrategy(AlienShip::Strategy strategy) {
  m_strategy = strategy;
}

void AlienShip::SetStrategyDuration(int duration) {
  m_strategyDuration = duration;
}

void AlienShip::Move() {
  switch (m_strategy) {
  case AlienShip::Strategy::NONE:
    break;
  case AlienShip::Strategy::DOWN:
    MoveTo(GetX(), GetY() - m_speed);
    break;
  case AlienShip::Strategy::LEFTDOWN:
    MoveTo(GetX() - m_speed, GetY() - m_speed);
    break;
  case AlienShip::Strategy::RIGHTDOWN:
    MoveTo(GetX() + m_speed, GetY() - m_speed);
    break;
  default:
    break;
  }
  m_strategyDuration--;
}

void AlienShip::UpdateActions() {
  ReactToPlayer();

  if (GetX() < 0) {
    m_strategy = AlienShip::Strategy::RIGHTDOWN;
    GenerateStrategyDuration();
  }
  if (GetX() >= WINDOW_WIDTH) {
    m_strategy = AlienShip::Strategy::LEFTDOWN;
    GenerateStrategyDuration();
  }
  if (m_strategyDuration <= 0) {
    GenerateStrategy();
    GenerateStrategyDuration();
  }

  Move();

}
