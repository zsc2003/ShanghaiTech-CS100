#ifndef METEORGOODIE_H__
#define METEORGOODIE_H__

#include "Goodie.h"

class MeteorGoodie : public Goodie {
public:
  MeteorGoodie(int x, int y, GameWorld* world);
  virtual ~MeteorGoodie();

  virtual void OnDestroy() override;

};

#endif // !METEORGOODIE_H__
