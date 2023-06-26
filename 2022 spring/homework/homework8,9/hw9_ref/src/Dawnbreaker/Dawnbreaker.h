#ifndef DAWNBREAKER_H__
#define DAWNBREAKER_H__

#include "GameObject.h"

class Dawnbreaker : public GameObject {
public:
  Dawnbreaker(int x, int y, GameWorld* world);
  virtual ~Dawnbreaker();

  virtual void UpdateActions() override;

  virtual bool IsEnemy() const override;

  virtual GameObject::Type GetType() const override;

  int GetMeteors() const;
  void GainMeteor();
  void PowerUp();

private:
  int m_energy;
  int m_meteors;
  int m_powerUpLevel;

  inline static const int BASE_ATTACK = 5;
  inline static const int MAX_HP = 100;
  inline static const int MAX_ENERGY = 10;
  inline static const double BASE_BULLET_SIZE = 0.5;
};

#endif // !DAWNBREAKER_H__
