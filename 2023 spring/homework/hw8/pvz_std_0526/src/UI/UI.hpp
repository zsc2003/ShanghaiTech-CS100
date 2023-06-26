#ifndef UI_HPP__
#define UI_HPP__

#include "GameObject.hpp"

class Background : public GameObject {
public:
  Background(pGameWorld world);
  GameObject::Type GetType() const override { return GameObject::Type::UI; }
  void Update() override {}
  void OnClick() override {}
};

class LawnGrid : public GameObject {
public: 
  LawnGrid(int x, int y, pGameWorld world);
  GameObject::Type GetType() const override { return GameObject::Type::UI; }
  void Update() override {}
  void OnClick() override;
};

class Sun : public GameObject {
public:
  enum class Source {
    Sky, Sunflower
  };
  Sun(int x, int y, pGameWorld world, Source source);

  GameObject::Type GetType() const override { return GameObject::Type::UI; }
  void Update() override;
  void OnClick() override;

private:
  Source m_source;
  int m_ySpeed;
  int m_dropTimer;
  int m_dieTimer;
};

class Shovel : public GameObject {
public:
  Shovel(pGameWorld world);
  GameObject::Type GetType() const override { return GameObject::Type::UI; }
  void Update() override {}
  void OnClick() override;

};


#endif // !PLANT_H__
