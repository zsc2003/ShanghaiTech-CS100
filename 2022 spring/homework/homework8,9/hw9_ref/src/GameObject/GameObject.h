#ifndef GAMEOBJECT_H__
#define GAMEOBJECT_H__

#include <memory>
#include "ObjectBase.h"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;

class GameObject : public ObjectBase {
public:
  enum class Type {
    SPACESHIP, PROJECTILE, GOODIE, BACKGROUND
  };

  GameObject(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world, int hp, int collisionDamage);
  virtual ~GameObject();

  virtual void Update();

  virtual void UpdateActions() = 0;

  GameWorld* GetWorld() const;
  bool IsAlive() const;
  int GetCollisionDamage() const;

  int GetHP() const;
  void SetHP(int hp);
  void RestoreHP(int hp);

  // Have a think: Now that we have SetHP, Why do we need this function?
  // Hint: An enemy destroyed is different from an enemy floating out of screen.
  void TakeDamage(int damage);

  virtual bool IsEnemy() const = 0;

  virtual GameObject::Type GetType() const = 0;

  virtual void OnDestroy();

protected:
  inline bool IsOffBoundary() const;

  // A handy definition of a large number, 
  // since for simplicity I don't want to use INT_MAX or std::numeric_limits.
  inline static const int MAX_HP_LIMIT = 9999999;

private:
  GameWorld* m_world;
  int m_hp;
  int m_maxHP;
  int m_collisionDmg;

};


#endif // !GAMEOBJECT_H__
