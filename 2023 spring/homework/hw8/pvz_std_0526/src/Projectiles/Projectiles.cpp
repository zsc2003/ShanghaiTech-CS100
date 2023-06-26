#include "Projectiles.hpp"
#include "UI.hpp"

#include "GameWorld.hpp"

Projectile::Projectile(ImageID imgID, int x, int y, int width, int height, pGameWorld world, int hp, int collisionDmg)
  : GameObject(imgID, x, y, LAYER_PROJECTILES, width, height, world, hp, collisionDmg, ANIMID_NO_ANIMATION) {}


Pea::Pea(int x, int y, pGameWorld world) : Projectile(IMGID_PEA, x, y, 30, 30, world, 1, 20) {}

void Pea::Update() {
  MoveTo(GetX() + 8, GetY());
  if (GetX() >= WINDOW_WIDTH) {
    TakeDamage(1);
  }
}

void Pea::OnCollision(std::shared_ptr<GameObject> other) {
  if (other->GetType() != GameObject::Type::Zombie) {
    return;
  }
  other->TakeDamage(GetAttack());
  TakeDamage(1);
}

Explosion::Explosion(int x, int y, pGameWorld world) : Projectile(IMGID_EXPLOSION, x, y, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, world, 1, 1800), m_lifetime(3) {}

void Explosion::Update() {
  if (--m_lifetime < 0) {
    TakeDamage(1);
  }
}

void Explosion::OnCollision(std::shared_ptr<GameObject> other) {
  if (other->GetType() != GameObject::Type::Zombie) {
    return;
  }
  other->TakeDamage(GetAttack());
}


