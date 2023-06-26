#ifndef ALPHATRON_H__
#define ALPHATRON_H__

#include "AlienShip.h"

class Alphatron : public AlienShip {
public:
  Alphatron(int x, int y, int hp, GameWorld* world, int attack, int speed);
  virtual ~Alphatron();

  virtual void ReactToPlayer() override;

  virtual void OnDestroy() override;
};

#endif // !ALPHATRON_H__
