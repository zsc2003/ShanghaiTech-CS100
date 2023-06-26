#ifndef STAR_H__
#define STAR_H__

#include "Background.h"

class Star : public Background {
public:
  Star(int x, int y, double size, GameWorld* world);
  virtual ~Star();

  virtual void UpdateActions() override;
};


#endif // !STAR_H__
