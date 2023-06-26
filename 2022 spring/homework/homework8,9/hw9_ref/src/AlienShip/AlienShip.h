#ifndef ALIENSHIP_H__
#define ALIENSHIP_H__

#include "GameObject.h"

class AlienShip : public GameObject {
public:
  AlienShip(int imageID, int x, int y, GameWorld* world, int hp, int collisionDamage, int attack, int speed);
  virtual ~AlienShip();

  virtual void UpdateActions();

  virtual bool IsEnemy() const override;

  virtual GameObject::Type GetType() const override;

  int GetSpeed() const;
  void SetSpeed(int speed);
  int GetAttack() const;
  int GetEnergy() const;
  void SetEnergy(int energy);

  virtual void Move();
  virtual void ReactToPlayer() = 0;

protected:
  enum class Strategy {
    NONE, DOWN, LEFTDOWN, RIGHTDOWN
  };

  void GenerateStrategy();
  void GenerateStrategyDuration();
  void SetStrategy(AlienShip::Strategy strategy);
  void SetStrategyDuration(int duration);

private:
  int m_attack;
  int m_speed;
  int m_energy;
  Strategy m_strategy;
  int m_strategyDuration;
};

#endif // !ALIENSHIP_H__
