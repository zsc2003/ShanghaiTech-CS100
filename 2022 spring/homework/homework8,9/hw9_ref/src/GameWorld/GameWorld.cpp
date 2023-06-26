#include "GameWorld.h"

#include <sstream>

#include "GameObject.h"
#include "Dawnbreaker.h"
#include "Star.h"
#include "Alphatron.h"
#include "Sigmatron.h"
#include "Omegatron.h"

GameWorld::GameWorld() : m_dawnbreaker(nullptr), m_gameObjects(), m_lives(3), m_enemiesDestroyed(0), m_enemiesOnScreen(0) {

}

GameWorld::~GameWorld() {}

void GameWorld::Init() { 
  m_dawnbreaker = new Dawnbreaker(300, 100, this);
  m_gameObjects.push_back(m_dawnbreaker);

  for (int i = 0; i < 30; i++) {
    m_gameObjects.push_back(new Star(randInt(0, WINDOW_WIDTH), randInt(0, WINDOW_HEIGHT - 1), randInt(10, 40) / 100.0, this));
  }
}

LevelStatus GameWorld::Update() {
  if (randInt(1, 30) == 1) {
      m_gameObjects.push_back(new Star(randInt(0, WINDOW_WIDTH), WINDOW_HEIGHT - 1, randInt(10, 40) / 100.0, this));
  }

  int enemiesToDestroy = EnemiesRequiredForLevel() - m_enemiesDestroyed;
  int targetEnemies = std::min(enemiesToDestroy, MaxEnemiesOnScreen());
  if (m_enemiesOnScreen < targetEnemies) {
    if (randInt(1, 100) <= targetEnemies - m_enemiesOnScreen) {
      AddRandomEnemy();
    }
  }

  for (auto& gameObject : m_gameObjects) {
    gameObject->Update();
  }

  if (!GetDawnbreaker()->IsAlive()) {
    m_lives--;
    return LevelStatus::DAWNBREAKER_DESTROYED;
  }

  if (m_enemiesDestroyed >= EnemiesRequiredForLevel()) {
    return LevelStatus::LEVEL_CLEARED;
  }

  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    if (!(*iter)->IsAlive()) {
      // Enemy ships (both destroyed and that fly off screen) count to "on screen".
      if ((*iter)->IsEnemy() && (*iter)->GetType() == GameObject::Type::SPACESHIP) {
        m_enemiesOnScreen--;
      }
      delete (*iter);
      iter = m_gameObjects.erase(iter);
    }
    else {
      ++iter;
    }
  }

  std::stringstream sstr;
  sstr << "HP: " << GetDawnbreaker()->GetHP() << "/100" << "   Meteors: " << GetDawnbreaker()->GetMeteors() << "   Lives: " << m_lives <<
    "   Level: " << GetLevel() << "   Enemies: " << m_enemiesDestroyed << "/" << 3 * GetLevel() << "   Score: " << GetScore() << std::endl;
  SetStatusBarMessage(sstr.str());

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  m_dawnbreaker = nullptr;

  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    delete (*iter);
    iter = m_gameObjects.erase(iter);
  }

  m_enemiesDestroyed = 0;
  m_enemiesOnScreen = 0;

}

bool GameWorld::IsGameOver() const{
  return m_lives <= 0;
}

void GameWorld::Instantiate(GameObject* newGameObject) {
  m_gameObjects.push_back(newGameObject);
}

Dawnbreaker* GameWorld::GetDawnbreaker() const {
  return m_dawnbreaker;
}

void GameWorld::CheckCollisions(GameObject* thisObject) {
  // Only alive objects can collide.
  if (!thisObject->IsAlive()) {
    return;
  }

  for (auto& thatObject : m_gameObjects) {
    // The same object! Move on.
    if (thatObject == thisObject) {
      continue;
    }

    // Cannot collide with dead objects!
    if (!thatObject->IsAlive()) {
      continue;
    }

    // On collision, they deal damage respectively.
    if (CanCollide(thisObject, thatObject) && CollisionHappens(thisObject, thatObject)) {
      thisObject->TakeDamage(thatObject->GetCollisionDamage());
      thatObject->TakeDamage(thisObject->GetCollisionDamage());
    }

    // If this object dies, it cannot collide any more.
    if (!thisObject->IsAlive()) {
      break;
    }
  }
}

void GameWorld::RecordAnEnemyDestroyed() {
  m_enemiesDestroyed++;
}


// The most tricky function: collision check.
// We check collisions by two factors:
// two objects' sides (enemy/ally), and two objects' types (spaceship/projectile/goodie)
bool GameWorld::CanCollide(GameObject* thisObject, GameObject* thatObject) {

  // Enemies cannot collide.
  if (thisObject->IsEnemy() && thatObject->IsEnemy()) {
    return false;
  }

  // Two allies: the only case is our ship with a goodie.
  if (!thisObject->IsEnemy() && !thatObject->IsEnemy()) {
    if (thisObject->GetType() == GameObject::Type::SPACESHIP && thatObject->GetType() == GameObject::Type::GOODIE) {
      return true;
    }
    else if (thisObject->GetType() == GameObject::Type::GOODIE && thatObject->GetType() == GameObject::Type::SPACESHIP) {
      return true;
    }
    else {
      return false;
    }
  }

  // One ally, one enemy:
  //
  // The only illegal situations are: 
  // (1) background + any enemy
  // (2) goodie + any enemy
  // (3) projectile + projectile
  //
  // Okay, now it becomes simple:
  if (thisObject->GetType() == GameObject::Type::BACKGROUND || thatObject->GetType() == GameObject::Type::BACKGROUND) {
    return false;
  }

  if (thisObject->GetType() == GameObject::Type::GOODIE || thatObject->GetType() == GameObject::Type::GOODIE) {
    return false;
  }

  if (thisObject->GetType() == GameObject::Type::PROJECTILE && thatObject->GetType() == GameObject::Type::PROJECTILE) {
    return false;
  }

  return true;

}

inline bool GameWorld::CollisionHappens(GameObject* thisObject, GameObject* thatObject) {
  double distance = std::sqrt(
    (thatObject->GetX() - thisObject->GetX()) * (thatObject->GetX() - thisObject->GetX()) +
    (thatObject->GetY() - thisObject->GetY()) * (thatObject->GetY() - thisObject->GetY())
  );
  return distance < (thisObject->GetSize() + thatObject->GetSize()) * 30.0;
}

inline int GameWorld::MaxEnemiesOnScreen() const {
  return (5 + GetLevel()) / 2;
}
inline int GameWorld::EnemiesRequiredForLevel() const {
  return GetLevel() * 3;
}

void GameWorld::AddRandomEnemy() {
  int level = GetLevel();
  int p1 = 6;
  int p2 = 2 * std::max(level - 1, 0);
  int p3 = 3 * std::max(level - 2, 0);

  int roll = randInt(1, p1 + p2 + p3);
  if (roll <= p1) {
    Instantiate(new Alphatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 20 + 2 * level, this, 4 + level, 2 + level / 5));
  }
  else if (roll <= p1 + p2) {
    Instantiate(new Sigmatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 25 + 5 * level, this, 0, 2 + level / 5));
  }
  else {
    Instantiate(new Omegatron(randInt(0, WINDOW_WIDTH - 1), WINDOW_HEIGHT - 1, 20 + level, this, 2 + 2 * level, 3 + level / 4));
  }
  m_enemiesOnScreen++;
}

