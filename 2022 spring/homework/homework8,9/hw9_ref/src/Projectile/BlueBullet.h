#ifndef BLUEBULLET_H__
#define BLUEBULLET_H__

#include "Projectile.h"

class BlueBullet : public Projectile {
public:
  BlueBullet(int x, int y, double size, GameWorld* world, int collisionDamage);
  virtual ~BlueBullet();

  virtual void UpdateActions() override;

  virtual bool IsEnemy() const override;

};

#endif // !BLUEBULLET_H__
