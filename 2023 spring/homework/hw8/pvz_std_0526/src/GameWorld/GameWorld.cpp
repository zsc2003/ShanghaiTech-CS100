#include "GameWorld.hpp"

#include <sstream>

#include "GameObject.hpp"
#include "Plants.hpp"
#include "UI.hpp"
#include "Zombies.hpp"
#include "SeedPacket.hpp"
#include "Spawn.hpp"

GameWorld::GameWorld() : m_gameObjects(), m_dropSunTimer(180), m_waveTimer(1200), m_spawn(nullptr), m_holdingShovel(false) {

}

GameWorld::~GameWorld() {}

void GameWorld::Init() {
  SetWave(0);
  SetSun(50);
  m_spawn = nullptr;
  m_dropSunTimer = 180;
  m_waveTimer = 1200;
  Instantiate(std::make_shared<Background>(shared_from_this()));
  for (int r = 0; r < GAME_ROWS; r++) {
    for (int c = 0; c < GAME_COLS; c++) {
      Instantiate(std::make_shared<LawnGrid>(FIRST_COL_CENTER + c * LAWN_GRID_WIDTH, FIRST_ROW_CENTER + r * LAWN_GRID_HEIGHT, shared_from_this()));
    }
  }
  Instantiate(std::make_shared<SunflowerSeed>(130, WINDOW_HEIGHT - 44, shared_from_this()));
  Instantiate(std::make_shared<PeashooterSeed>(130 + 60, WINDOW_HEIGHT - 44, shared_from_this()));
  Instantiate(std::make_shared<WallnutSeed>(130 + 120, WINDOW_HEIGHT - 44, shared_from_this()));
  Instantiate(std::make_shared<CherryBombSeed>(130 + 180, WINDOW_HEIGHT - 44, shared_from_this()));
  Instantiate(std::make_shared<RepeaterSeed>(130 + 240, WINDOW_HEIGHT - 44, shared_from_this()));
  //Instantiate(std::make_shared<ZombieSeed>(130 + 300, WINDOW_HEIGHT - 44, shared_from_this()));

  Instantiate(std::make_shared<Shovel>(shared_from_this()));
}

LevelStatus GameWorld::Update() {

  if (--m_dropSunTimer <= 0) {
    Instantiate(std::make_shared<Sun>(randInt(75, WINDOW_WIDTH - 75), WINDOW_HEIGHT, shared_from_this(), Sun::Source::Sky));
    m_dropSunTimer = 300;
  }

  if (--m_waveTimer <= 0) {
    SetWave(GetWave()+1);
    m_waveTimer = NextWaveTime();
    AddZombieWave();
  }

  for (const auto& gameObject : m_gameObjects) {
    if (gameObject->IsAlive()) {
      gameObject->Update();
    }
  }

  CheckCollisions();

  if (m_spawn && !m_spawn->IsAlive()) {
    m_spawn = nullptr;
  }

  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    if (!(*iter)->IsAlive()) {
      iter = m_gameObjects.erase(iter);
    }
    else {
      ++iter;
    }
  }

  for (const auto& object : m_gameObjects) {
    if (object->GetType() == GameObject::Type::Zombie) {
      if (object->GetX() < 0) {
        return LevelStatus::LOSING;
      }
      if (object->GetCurrentAnimation() == ANIMID_EAT_ANIM && !IsCollidingWithPlant(object)) {
        object->PlayAnimation(ANIMID_WALK_ANIM);
      }
    } 
  }


  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  m_gameObjects.clear();
  m_spawn = nullptr;
  m_holdingShovel = false;
}

void GameWorld::Instantiate(std::shared_ptr<GameObject> newGameObject) {
  m_gameObjects.push_back(newGameObject);
}

bool GameWorld::HasSpawn() const {
  return m_spawn != nullptr;
}

bool GameWorld::IsHoldingShovel() const {
  return m_holdingShovel;
}

void GameWorld::SetShovel(bool value) {
  m_holdingShovel = value;
}

const std::shared_ptr<GameObject> GameWorld::GetSpawn() const {
  return m_spawn;
}

void GameWorld::SetSpawn(std::shared_ptr<GameObject> spawnObj) {
  Instantiate(spawnObj);
  m_spawn = spawnObj;
}


bool GameWorld::SpendSun(int value) {
  if (GetSun() >= value) {
    SetSun(GetSun() - value);
    return true;
  }
  else {
    return false;
  }
}

bool GameWorld::ShouldAttack(std::shared_ptr<GameObject> plant) const {
  if (plant->GetType() != GameObject::Type::Plant) {
    return false;
  }
  for (const auto& object : m_gameObjects) {
    if (object->GetType() == GameObject::Type::Zombie && std::abs(object->GetY() - plant->GetY()) <= 1 && object->GetX() > plant->GetX()) {
      return true;
    }
  }
  return false;
}

void GameWorld::CheckCollisions() {
  for (const auto& thisObject : m_gameObjects) {
    // Only alive objects can collide.
    if (!thisObject->IsAlive()) {
      continue;
    }
    for (const auto& thatObject : m_gameObjects) {
      // The same object! Move on.
      if (thatObject == thisObject) {
        continue;
      }

      // Cannot collide with dead objects!
      if (!thatObject->IsAlive()) {
        continue;
      }

      // On collision
      if (CanCollide(thisObject, thatObject) && CollisionHappens(thisObject, thatObject)) {
        thisObject->OnCollision(thatObject);
        thatObject->OnCollision(thisObject);
      }

      // If this object dies, it cannot collide any more.
      if (!thisObject->IsAlive()) {
        break;
      }
    }
  }
}

bool GameWorld::IsCollidingWithPlant(std::shared_ptr<GameObject> zombie) {
  for (const auto& object : m_gameObjects) {
    if (object->GetType() == GameObject::Type::Plant && CollisionHappens(zombie, object)) {
      return true;
    }
  }
  return false;
}

bool GameWorld::CanCollide(std::shared_ptr<GameObject> thisObject, std::shared_ptr<GameObject> thatObject) {
  // At least one object should be a zombie.
  if (thisObject->GetType() != GameObject::Type::Zombie && thatObject->GetType() != GameObject::Type::Zombie) {
    return false;
  }

  // Zombies should not collide.
  if (thisObject->GetType() == GameObject::Type::Zombie && thatObject->GetType() == GameObject::Type::Zombie) {
    return false;
  }

  // Only one zombie: the other object should be either a plant or a projectile.
  if (thisObject->GetType() == GameObject::Type::Plant || thatObject->GetType() == GameObject::Type::Plant) {
    return true;
  }
  if (thisObject->GetType() == GameObject::Type::Projectile || thatObject->GetType() == GameObject::Type::Projectile) {
    return true;
  }
  return false;
}

inline bool GameWorld::CollisionHappens(std::shared_ptr<GameObject> thisObject, std::shared_ptr<GameObject> thatObject) {
  return (std::abs(thatObject->GetX() - thisObject->GetX()) < ((thisObject->GetWidth() + thatObject->GetWidth()) / 2) &&
          std::abs(thatObject->GetY() - thisObject->GetY()) < ((thisObject->GetHeight() + thatObject->GetHeight()) / 2));
}


int GameWorld::NextWaveTime() const {
  return std::max(150, 600 - GetWave() * 20);
}

void GameWorld::AddZombieWave() {
  for (int i = 0; i < (GetWave() + 5) / 10 + 1; i++) {
    AddRandomZombie();
  }
}

void GameWorld::AddRandomZombie() {
  int wave = GetWave();
  int p1 = 20;
  int p2 = 2 * std::max(wave - 5, 0);
  int p3 = 3 * std::max(wave - 10, 0);

  int roll = randInt(1, p1 + p2 + p3);

  int spawnX = randInt(WINDOW_WIDTH - 10, WINDOW_WIDTH);
  int spawnY = FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT;

  if (roll <= p1) {
    Instantiate(std::make_shared<RegularZombie>(spawnX, spawnY, shared_from_this()));
  }
  else if (roll <= p1 + p2) {
    Instantiate(std::make_shared<PoleVaultingZombie>(spawnX, spawnY, shared_from_this()));
  }
  else {
    Instantiate(std::make_shared<BucketHeadZombie>(spawnX, spawnY, shared_from_this()));
  }
}