#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <list>
#include <memory>

#include "WorldBase.hpp"
#include "GameObject.hpp"
#include "utils.hpp"


class GameWorld : public WorldBase, public std::enable_shared_from_this<GameWorld> {
public:
  GameWorld();
  virtual ~GameWorld();

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override;

  void Instantiate(std::shared_ptr<GameObject> newGameObject);
  
  bool SpendSun(int value);

  bool ShouldAttack(std::shared_ptr<GameObject> plant) const;
  
  void CheckCollisions();
  bool IsCollidingWithPlant(std::shared_ptr<GameObject> zombie);
  void RecordAnEnemyDestroyed();

  bool HasSpawn() const;
  bool IsHoldingShovel() const;
  void SetShovel(bool value);
  const std::shared_ptr<GameObject> GetSpawn() const;
  void SetSpawn(std::shared_ptr<GameObject> spawnObj);

private: 
  bool CanCollide(std::shared_ptr<GameObject> thisObject, std::shared_ptr<GameObject> thatObject);
  inline bool CollisionHappens(std::shared_ptr<GameObject> thisObject, std::shared_ptr<GameObject> thatObject);
  inline int MaxEnemiesOnScreen() const;
  inline int EnemiesRequiredForLevel() const;
  int NextWaveTime() const;
  void AddZombieWave();
  void AddRandomZombie();

  std::list<std::shared_ptr<GameObject>> m_gameObjects;

  int m_dropSunTimer;
  int m_waveTimer;

  std::shared_ptr<GameObject> m_spawn;
  bool m_holdingShovel;
};

#endif // !GAMEWORLD_HPP__
