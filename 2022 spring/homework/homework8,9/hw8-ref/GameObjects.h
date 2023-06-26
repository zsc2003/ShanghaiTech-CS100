#ifndef GAMEOBJECTS_H__
#define GAMEOBJECTS_H__

#include <memory>
#include "ObjectBase.h"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;

class GameObject : public ObjectBase {
public:
  GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world, int hp, int collisionDamage);
  virtual ~GameObject();

  virtual void Update();

  virtual void UpdateActions() = 0;

  GameWorld* GetWorld() const;
  bool IsAlive() const;
  int GetCollisionDamage() const;

  int GetHP() const;
  void SetHP(int hp);

  // Have a think: Now that we have SetHP, Why do we need this function?
  // Hint: An enemy destroyed is different from an enemy floating out of screen.
  void TakeDamage(int damage);


protected:
  inline bool IsOffBoundary() const;

  // A handy definition of a large number, 
  // since for simplicity I don't want to use INT_MAX or std::numeric_limits.
  inline static const int MAX_HP_LIMIT = 9999999;

private:
  GameWorld* m_world;
  int m_hp;
  int m_collisionDmg;

};

class BackGround : public GameObject {
public:
  BackGround(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world);
  virtual ~BackGround();

  virtual void UpdateActions() = 0;
};

class Star : public BackGround {
public:
  Star(int x, int y, double size, GameWorld* world);
  virtual ~Star();

  virtual void UpdateActions() override;
};

class Dawnbreaker : public GameObject {
public:
  Dawnbreaker(int x, int y, GameWorld* world);
  virtual ~Dawnbreaker();

  virtual void UpdateActions() override;

private:
  int m_energy;

  inline static const int BASE_ATTACK = 5;
  inline static const int MAX_HP = 100;
  inline static const int MAX_ENERGY = 10;
  inline static const double BASE_BULLET_SIZE = 0.5;
};

class Projectile : public GameObject {
public:
  Projectile(int imageID, int x, int y, int direction, double size, GameWorld* world, int hp, int collisionDamage);
  virtual ~Projectile();

  virtual void UpdateActions() = 0;
};

class BlueBullet : public Projectile {
public:
  BlueBullet(int x, int y, double size, GameWorld* world, int collisionDamage);
  virtual ~BlueBullet();

  virtual void UpdateActions() override;
};

#endif // !GAMEOBJECTS_H__