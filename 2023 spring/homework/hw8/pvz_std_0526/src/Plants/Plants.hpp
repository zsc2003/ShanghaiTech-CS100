#ifndef PLANTS_HPP__
#define PLANTS_HPP__

#include "GameObject.hpp"

class Plant : public GameObject {
public:
  Plant(ImageID imgID, int x, int y, pGameWorld world, int hp);
  GameObject::Type GetType() const override { return GameObject::Type::Plant; }

  void OnClick() override;
};

class Sunflower : public Plant {
public:
  Sunflower(int x, int y, pGameWorld world);
  void Update() override;

private:
  int m_sunCoolDown;
};

class Peashooter : public Plant {
public:
  Peashooter(int x, int y, pGameWorld world);
  void Update() override;
private:
  int m_attackCoolDown;
};

class Wallnut : public Plant {
public:
  Wallnut(int x, int y, pGameWorld world);
  void Update() override;
};


class CherryBomb : public Plant {
public:
  CherryBomb(int x, int y, pGameWorld world);
  void Update() override;
private:
  int m_explodeCounter;
};

class Repeater : public Plant {
public:
  Repeater(int x, int y, pGameWorld world);
  void Update() override;
private:
  int m_attackCoolDown;
  int m_secondPeaCounter;
};

#endif // !PLANTS_HPP__
