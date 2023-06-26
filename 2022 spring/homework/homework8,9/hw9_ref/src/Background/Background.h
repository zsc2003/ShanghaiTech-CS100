#ifndef BACKGROUND_H__
#define BACKGROUND_H__

#include "GameObject.h"

class Background : public GameObject {
public:
  Background(int imageID, int x, int y, int direction, int layer, double size, GameWorld* world, int hp);
  virtual ~Background();

  virtual void UpdateActions() = 0;

  virtual bool IsEnemy() const override;

  virtual GameObject::Type GetType() const override;
};


#endif // !BACKGROUND_H__
