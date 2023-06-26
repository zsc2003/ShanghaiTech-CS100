#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>
#include <memory>

#include "WorldBase.h"
#include "GameObjects.h"
#include "utils.h"

class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  void Instantiate(GameObject* newGameObject);

  Dawnbreaker* GetDawnbreaker() const;

private:
  Dawnbreaker* m_dawnbreaker;
  std::list<GameObject*> m_gameObjects;

  int m_lives;
};

#endif // !GAMEWORLD_H__
