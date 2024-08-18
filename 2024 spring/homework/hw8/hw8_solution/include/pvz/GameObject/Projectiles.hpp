#ifndef PROJECTILES_HPP
#define PROJECTILES_HPP

#include "pvz/GameObject/GameObject.hpp"

class Projectile : public GameObject {
public:
  Projectile(ImageID imageID, int x, int y, int width, int height, GameWorld *world, int attack)
      : GameObject{imageID, x, y, LayerID::PROJECTILES, width, height, AnimID::NO_ANIMATION, world}, m_attack{attack} {}

  void OnClick() final {}

  int GetAttack() const { return m_attack; }

  bool IsProjectile() const final { return true; }

private:
  int m_attack;
};

class Pea : public Projectile {
public:
  Pea(int x, int y, GameWorld *world) : Projectile{ImageID::PEA, x, y, 28, 28, world, 20} {}

  void Update() override {
    MoveTo(GetX() + 8, GetY());
    if (GetX() >= WINDOW_WIDTH)
      SetDead();
  }

  void Hit(GameObject &other) override {
    if (!other.IsZombie())
      return;
    other.DecreaseHP(GetAttack());
    SetDead();
  }
};

class Explosion : public Projectile {
public:
  Explosion(int x, int y, GameWorld *world)
      : Projectile{ImageID::EXPLOSION, x, y, 3 * LAWN_GRID_WIDTH, 3 * LAWN_GRID_HEIGHT, world, 1800} {}

  void Update() override {
    if (--m_timer < 0)
      SetDead();
  }

  void Hit(GameObject &other) override {
    if (!other.IsZombie())
      return;
    other.DecreaseHP(GetAttack());
  }

private:
  int m_timer{3};
};

class RedPea : public Projectile {
public:
  RedPea(int x, int y, GameWorld *world) : Projectile{ImageID::RED_PEA, x, y, 28, 28, world, 20} {}

  void Update() override;

  void Hit(GameObject &other) override;

private:
  int m_velocityX{8};
  int m_velocityY{8};
};

#endif // PROJECTILES_HPP