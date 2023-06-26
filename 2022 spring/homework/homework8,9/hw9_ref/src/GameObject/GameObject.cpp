#include "GameObject.h"

#include "GameWorld.h"
#include "utils.h"

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world, int hp, int collisionDamage)
  : ObjectBase(imageID, x, y, direction, layer, size), m_world(world), m_hp(hp), m_maxHP(hp), m_collisionDmg(collisionDamage) {}

GameObject::~GameObject() {}

void GameObject::Update() {
  if (!IsAlive()) {
    return;
  }

  if (IsOffBoundary()) {
    SetHP(0);
    return;
  }

  GetWorld()->CheckCollisions(this);
  if (!IsAlive()) {
    return;
  }

  UpdateActions();

  GetWorld()->CheckCollisions(this);
  if (!IsAlive()) {
    return;
  }

}

GameWorld* GameObject::GetWorld() const {
  return m_world;
}

bool GameObject::IsAlive() const {
  return m_hp > 0;
}

int GameObject::GetCollisionDamage() const {
  return m_collisionDmg;
}

int GameObject::GetHP() const {
  return m_hp;
}

void GameObject::SetHP(int hp) {
  m_hp = hp;
}

// Have a think: Now that we have SetHP, Why do we need this function?
// Hint: An enemy destroyed is different from an enemy floating out of screen.
// Hint2: You may want to add something else to this function. What could that be?
void GameObject::TakeDamage(int damage) {
  m_hp -= damage;
  if (m_hp <= 0) {
    OnDestroy();
  }
}

void GameObject::RestoreHP(int hp) {
  m_hp = m_hp + hp >= m_maxHP ? m_maxHP : m_hp + hp;
}

void GameObject::OnDestroy() {}

inline bool GameObject::IsOffBoundary() const {
  return GetY() < 0 || GetY() >= WINDOW_HEIGHT;
}

