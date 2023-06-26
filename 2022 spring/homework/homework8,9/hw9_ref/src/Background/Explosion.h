#ifndef EXPLOSION_H__
#define EXPLOSION_H__

#include "Background.h"

class Explosion : public Background {
public:
  Explosion(int x, int y, GameWorld* world);
  virtual ~Explosion();

  virtual void UpdateActions() override;

};

#endif // !EXPLOSION_H__
