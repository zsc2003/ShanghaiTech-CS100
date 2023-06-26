#include "GameWorld.h"

#include <sstream>

GameWorld::GameWorld() : m_dawnbreaker(nullptr), m_gameObjects(), m_lives(3) {

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

  for (auto& gameObject : m_gameObjects) {
    gameObject->Update();
  }

  if (!GetDawnbreaker()->IsAlive()) {
    m_lives--;
    return LevelStatus::DAWNBREAKER_DESTROYED;
  }

  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    if (!(*iter)->IsAlive()) {
      delete (*iter);
      iter = m_gameObjects.erase(iter);
    }
    else {
      ++iter;
    }
  }

  return LevelStatus::ONGOING;
}

void GameWorld::CleanUp() {
  m_dawnbreaker = nullptr;

  auto iter = m_gameObjects.begin();
  while (iter != m_gameObjects.end()) {
    delete (*iter);
    iter = m_gameObjects.erase(iter);
  }
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