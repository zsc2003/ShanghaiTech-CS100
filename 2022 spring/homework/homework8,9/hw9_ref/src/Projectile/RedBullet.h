#ifndef REDBULLET_H__
#define REDBULLET_H__

#include "Projectile.h"

class RedBullet : public Projectile {
public:
  RedBullet(int x, int y, int direction, double size, GameWorld* world, int collisionDamage);
  virtual ~RedBullet();

  virtual void UpdateActions() override;

  virtual bool IsEnemy() const override;
};


#endif // !REDBULLET_H__
