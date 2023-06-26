#ifndef OMEGATRON_H__
#define OMEGATRON_H__

#include "AlienShip.h"

class Omegatron : public AlienShip {
public:
  Omegatron(int x, int y, int hp, GameWorld* world, int attack, int speed);
  virtual ~Omegatron();

  virtual void ReactToPlayer() override;

  virtual void OnDestroy() override;
};

#endif // !OMEGATRON_H__
