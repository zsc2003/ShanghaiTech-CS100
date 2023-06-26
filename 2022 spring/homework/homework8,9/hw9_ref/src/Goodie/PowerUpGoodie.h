#ifndef POWERUPGOODIE_H__
#define POWERUPGOODIE_H__

#include "Goodie.h"

class PowerUpGoodie : public Goodie {
public:
  PowerUpGoodie(int x, int y, GameWorld* world);
  virtual ~PowerUpGoodie();

  virtual void OnDestroy() override;

};

#endif // !POWERUPGOODIE_H__
