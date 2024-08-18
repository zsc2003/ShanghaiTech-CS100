#ifndef GAMEOBJECT_HPP__
#define GAMEOBJECT_HPP__

#include <limits>
#include <memory>

#include "pvz/Framework/ObjectBase.hpp"

// Declares the class name GameWorld so that its pointers can be used.
class GameWorld;

class GameObject : public ObjectBase {
public:
  GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, AnimID animID, GameWorld *world,
             int hp = std::numeric_limits<int>::max())
      : ObjectBase{imageID, x, y, layer, width, height, animID}, m_world{world}, m_hp{hp} {}

  bool IsDead() const { return m_hp <= 0; }

  void SetDead() { m_hp = 0; }

  void Update() override {}

  void OnClick() override {}

  void DecreaseHP(int dec) { m_hp -= dec; }

  int GetHP() const { return m_hp; }

  void SetHP(int hp) { m_hp = hp; }

  auto GetWorld() const { return m_world; }

  virtual bool IsZombie() const { return false; }

  virtual bool IsPlant() const { return false; }

  virtual bool IsProjectile() const { return false; }

  virtual void Hit(GameObject &other) {}

private:
  GameWorld *m_world;
  int m_hp;
};

#endif // !GAMEOBJECT_HPP__
