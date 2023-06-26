#ifndef METEOR_H__
#define METEOR_H__

#include "Projectile.h"

class Meteor : public Projectile {
public:
  Meteor(int x, int y, GameWorld* world);
  virtual ~Meteor();

  virtual void UpdateActions() override;

  virtual bool IsEnemy() const override;
};



#endif // !METEOR_H__
