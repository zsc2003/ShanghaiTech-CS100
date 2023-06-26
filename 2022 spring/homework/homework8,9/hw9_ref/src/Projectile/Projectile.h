#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include "GameObject.h"

class Projectile : public GameObject {
public:
  Projectile(int imageID, int x, int y, int direction, double size, GameWorld* world, int hp, int collisionDamage);
  virtual ~Projectile();

  virtual void UpdateActions() = 0;

  virtual GameObject::Type GetType() const override;

};


#endif // !PROJECTILE_H__
