#ifndef GAMEWORLD_H__
#define GAMEWORLD_H__

#include <list>
#include <memory>

#include "WorldBase.h"
#include "GameObject/GameObject.h"
#include "Dawnbreaker/Dawnbreaker.h"
#include "utils.h"

class Dawnbreaker;

class GameWorld : public WorldBase {
public:
  GameWorld();
  virtual ~GameWorld();

  virtual void Init() override;

  virtual LevelStatus Update() override;

  virtual void CleanUp() override;

  virtual bool IsGameOver() const override;

  void Instantiate(GameObject* newGameObject);
  void CheckCollisions(GameObject* thisObject);
  void RecordAnEnemyDestroyed();

  Dawnbreaker* GetDawnbreaker() const;

private:  
  // The most tricky function: collision check.
  bool CanCollide(GameObject* thisObject, GameObject* thatObject);

  inline bool CollisionHappens(GameObject* thisObject, GameObject* thatObject);
  inline int MaxEnemiesOnScreen() const;
  inline int EnemiesRequiredForLevel() const;
  void AddRandomEnemy();


  Dawnbreaker* m_dawnbreaker;
  std::list<GameObject*> m_gameObjects;

  int m_lives;
  int m_enemiesOnScreen;
  int m_enemiesDestroyed;

};

#endif // !GAMEWORLD_H__
