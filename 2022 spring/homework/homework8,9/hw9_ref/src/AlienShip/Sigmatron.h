#ifndef SIGMATRON_H__
#define SIGMATRON_H__

#include "AlienShip.h"

class Sigmatron : public AlienShip {
public:
  Sigmatron(int x, int y, int hp, GameWorld* world, int attack, int speed);
  virtual ~Sigmatron();

  virtual void ReactToPlayer() override;

  virtual void OnDestroy() override;
};

#endif // !SIGMATRON_H__

