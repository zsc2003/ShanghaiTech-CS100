#ifndef GOODIE_H__
#define GOODIE_H__

#include "GameObject.h"

class Goodie : public GameObject {
public:
  Goodie(int imageID, int x, int y, GameWorld* world);
  virtual ~Goodie();

  virtual void UpdateActions() override;

  virtual bool IsEnemy() const override;

  virtual GameObject::Type GetType() const override;

  virtual void OnDestroy() override = 0;

private:

};


#endif // !GOODIE_H__
