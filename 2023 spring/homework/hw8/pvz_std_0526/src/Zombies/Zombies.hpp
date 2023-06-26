#ifndef ZOMBIES_HPP__
#define ZOMBIES_HPP__

#include "GameObject.hpp"

class Zombie : public GameObject {
public:
  Zombie(ImageID imgID, int x, int y, pGameWorld world, int hp, int speed);
  GameObject::Type GetType() const override { return GameObject::Type::Zombie; }
  
  void Update() override;
  virtual void Move();
  virtual void SpecialActions();
  //virtual void EatPlants(std::shared_ptr<GameObject> other) {}

  void OnCollision(std::shared_ptr<GameObject> other) override;

  //void OnClick() override {}

protected:
  int m_speed;
};

class RegularZombie : public Zombie {
public:
  RegularZombie(int x, int y, pGameWorld world);

private:

};

class BucketHeadZombie : public Zombie {
public:
  BucketHeadZombie(int x, int y, pGameWorld world);

  void SpecialActions() override;
};

class PoleVaultingZombie : public Zombie {
public:
  PoleVaultingZombie(int x, int y, pGameWorld world);

  void SpecialActions() override;

private:
  int m_jumpCountDown;
};
#endif // !ZOMBIES_HPP__
