#include "GameObjects.h"

#include <memory>

#include "GameWorld.h"
#include "utils.h"

GameObject::GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world, int hp, int collisionDamage)
  : ObjectBase(imageID, x, y, direction, layer, size), m_world(world), m_hp(hp), m_collisionDmg(collisionDamage) {}

GameObject::~GameObject() {}

void GameObject::Update() {
  if (!IsAlive()) {
    return;
  }
  if (IsOffBoundary()) {
    SetHP(0);
    return;
  }

  UpdateActions();

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
}

inline bool GameObject::IsOffBoundary() const {
  return GetY() < 0 || GetY() >= WINDOW_HEIGHT;
}

BackGround::BackGround(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world)
  : GameObject(imageID, x, y, direction, layer, size, world, 1, 0) {}

BackGround::~BackGround() {}

Star::Star(int x, int y, double size, GameWorld* world)
  : BackGround(IMGID_STAR, x, y, 0, 4, size, world) {}

Star::~Star() {}

void Star::UpdateActions() {
  MoveTo(GetX(), GetY() - 1);
}

Dawnbreaker::Dawnbreaker(int x, int y, GameWorld* world)
  : GameObject(IMGID_DAWNBREAKER, x, y, 0, 0, 1.0, world, MAX_HP, MAX_HP_LIMIT), m_energy(MAX_ENERGY) {}

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
      GetWorld()->Instantiate(new BlueBullet(GetX(), GetY() + 50, BASE_ATTACK, GetWorld(), BASE_BULLET_SIZE));
    }
  }

  if (m_energy < MAX_ENERGY) {
    m_energy++;
  }
  
}


Projectile::Projectile(int imageID, int x, int y, int direction, double size, GameWorld* world, int hp, int collisionDamage)
  : GameObject(imageID, x, y, direction, 1, size, world, hp, collisionDamage) {}

Projectile::~Projectile() {}


BlueBullet::BlueBullet(int x, int y, double size, GameWorld* world, int collisionDamage)
  : Projectile(IMGID_BLUE_BULLET, x, y, 0, size, world, 1, collisionDamage) {}

BlueBullet::~BlueBullet() {}

void BlueBullet::UpdateActions() {
  MoveTo(GetX(), GetY() + 6);
}

