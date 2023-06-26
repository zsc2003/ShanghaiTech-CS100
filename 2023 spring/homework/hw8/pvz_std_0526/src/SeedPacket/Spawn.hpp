#ifndef SPAWN_HPP__
#define SPAWN_HPP__

#include "GameObject.hpp"
#include "Plants.hpp"
#include "GameWorld.hpp"

#include <memory>

template <typename PlantType>
class Spawn : public GameObject {
public:
  Spawn(pGameWorld world)
    : GameObject(IMGID_NONE, 0, 0, MAX_LAYERS - 1, 0, 0, world, 1, 0) {}

  virtual ~Spawn() {
    GetWorld()->Instantiate(std::make_shared<PlantType>(GetX(), GetY(), GetWorld()));
  }
private:

};

#endif // !SPAWN_HPP__
