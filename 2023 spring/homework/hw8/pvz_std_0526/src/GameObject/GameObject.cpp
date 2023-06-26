#include "GameObject.hpp"

#include "GameWorld.hpp"
#include "utils.hpp"

GameObject::GameObject(ImageID imageID, int x, int y, LayerID layer, int width, int height, std::shared_ptr<GameWorld> world, int hp, int attack, AnimID animID)
  : ObjectBase(imageID, x, y, layer, width, height, animID), m_world(world), m_hp(hp), m_maxHP(hp), m_attack(attack) {}

GameObject::~GameObject() {}

void GameObject::Update() {
  if (!IsAlive()) {
    return;
  }

  UpdateActions();

}

void GameObject::OnClick() {
  std::cout << "(" << GetX() << ", " << GetY() << ")" << std::endl;
  return;
}


std::shared_ptr<GameWorld> GameObject::GetWorld() const {
  return m_world;
}

bool GameObject::IsAlive() const {
  return m_hp > 0;
}

int GameObject::GetAttack() const {
  return m_attack;
}

int GameObject::GetHP() const {
  return m_hp;
}

void GameObject::SetHP(int hp) {
  m_hp = hp;
}

void GameObject::TakeDamage(int damage) {
  m_hp -= damage;
}

