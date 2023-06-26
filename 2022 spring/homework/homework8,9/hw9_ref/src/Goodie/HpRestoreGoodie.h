#ifndef HPRESTOREGOODIE_H__
#define HPRESTOREGOODIE_H__

#include "Goodie.h"

class HpRestoreGoodie : public Goodie {
public:
  HpRestoreGoodie(int x, int y, GameWorld* world);
  virtual ~HpRestoreGoodie();

  virtual void OnDestroy() override;

};

#endif // !HPRESTOREGOODIE_H__
