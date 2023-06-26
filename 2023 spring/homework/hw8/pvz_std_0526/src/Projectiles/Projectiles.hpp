#ifndef PROJECTILES_HPP__
#define PROJECTILES_HPP__

#include "GameObject.hpp"

class Projectile : public GameObject {
public:
  Projectile(ImageID imgID, int x, int y, int width, int height, pGameWorld world, int hp, int collisionDmg);
  GameObject::Type GetType() const override { return GameObject::Type::Projectile; }
};

class Pea : public Projectile {
public:
  Pea(int x, int y, pGameWorld world);
  void Update() override;
  void OnCollision(std::shared_ptr<GameObject> other) override;

private:
};

class Explosion : public Projectile {
public:
  Explosion(int x, int y, pGameWorld world);
  void Update() override;
  void OnCollision(std::shared_ptr<GameObject> other) override;
private:
  int m_lifetime;
};


#endif // !PROJECTILES_HPP__
