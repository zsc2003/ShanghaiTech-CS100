#include "GameManager.h"

//#include "SpriteManager.h"
#include "utils.h"
#include "ObjectBase.h"

GameManager::GameManager() : m_gameState(GameManager::GameState::TITLE), m_pause(false), m_pressedKeys(), m_statusBar() {

}

void GameManager::Play(int argc, char** argv, std::shared_ptr<WorldBase> world) {
  m_world = world;
}

//void GameManager::Update() {
//  if (m_pause) return;
//  if (GetKey(KeyCode::QUIT)) {
//    exit(EXIT_SUCCESS);
//  }
//  switch (m_gameState) {
//  case GameManager::GameState::TITLE:
//    Prompt("DAWNBREAKER", "Press Enter to start");
//    if (GetKey(KeyCode::ENTER)) {
//      m_world->Init();
//      m_gameState = GameManager::GameState::ANIMATING;
//      Display();
//    }
//    break;
//  case GameManager::GameState::ANIMATING:
//  {
//    LevelStatus status = m_world->Update();
//    Display();
//    switch (status) {
//    case LevelStatus::ONGOING:
//      break;
//    case LevelStatus::DAWNBREAKER_DESTROYED:
//      m_world->CleanUp();
//      if (m_world->IsGameOver()) {
//        Prompt("GAME OVER", (std::string("You reached level ") + std::to_string(m_world->GetLevel()) +
//                             std::string(", score: ") + std::to_string(m_world->GetScore()) +
//                             std::string(". Press Enter to quit.")).c_str());
//        m_gameState = GameManager::GameState::GAMEOVER;
//        break;
//      }
//      else {
//        Prompt("LEVEL FAILED", "Press Enter to retry level");
//        m_gameState = GameManager::GameState::PROMPTING;
//        break;
//      }
//    case LevelStatus::LEVEL_CLEARED:
//      m_world->CleanUp();
//      m_world->SetLevel(m_world->GetLevel() + 1);
//      Prompt("LEVEL CLEAR!", "Press Enter to continue");
//      m_gameState = GameManager::GameState::PROMPTING;
//      break;
//    }
//    break;
//  }
//  case GameManager::GameState::PROMPTING:
//    if (GetKey(KeyCode::ENTER)) {
//      m_world->Init();
//      m_gameState = GameManager::GameState::ANIMATING;
//      Display();
//    } 
//    break;
//  case GameManager::GameState::GAMEOVER:
//    if (GetKey(KeyCode::ENTER)) {
//      exit(EXIT_SUCCESS);
//    }
//    break;
//  default:
//    break;
//  }
//}

void GameManager::KeyDownEvent(unsigned char key, int x, int y) {
  //if (key == 'p') {
  //  m_pause ^= 1;
  //  return;
  //}
  KeyCode keyCode = ToKeyCode(key);
  if (keyCode != KeyCode::NONE) {
    if (m_pressedKeys.find(keyCode) == m_pressedKeys.end()) {
      m_pressedKeys.insert({ keyCode, true });
    }
  }
}
void GameManager::KeyUpEvent(unsigned char key, int x, int y) {
  KeyCode keyCode = ToKeyCode(key);
  if (keyCode != KeyCode::NONE) {
    if (m_pressedKeys.find(keyCode) != m_pressedKeys.end()) {
      m_pressedKeys.erase(keyCode);
    }
  }
}

//void GameManager::SpecialKeyDownEvent(int key, int x, int y) {
//  KeyCode keyCode = SpecialToKeyCode(key);
//  if (keyCode != KeyCode::NONE) {
//    if (m_pressedKeys.find(keyCode) == m_pressedKeys.end()) {
//      m_pressedKeys.insert({ keyCode, true });
//    }
//  }
//}
//
//void GameManager::SpecialKeyUpEvent(int key, int x, int y) {
//  KeyCode keyCode = SpecialToKeyCode(key);
//  if (keyCode != KeyCode::NONE) {
//    if (m_pressedKeys.find(keyCode) != m_pressedKeys.end()) {
//      m_pressedKeys.erase(keyCode);
//    }
//  }
//}


bool GameManager::GetKey(KeyCode key) const {
  return m_pressedKeys.find(key) != m_pressedKeys.end();
}

bool GameManager::GetKeyDown(KeyCode key) {
  auto keyEntry = m_pressedKeys.find(key);
  if (keyEntry != m_pressedKeys.end()) {
    if (keyEntry->second) {
      m_pressedKeys[keyEntry->first] = false;
      return true;
    }
    else {
      return false;
    }
  }
  return false;
}

void GameManager::ClearKeys() {
  m_pressedKeys.clear();
}

void GameManager::SetStatusBarMessage(std::string message) {
  m_statusBar = message;
}

std::string GameManager::GetStatusBarMessage() const {
  return m_statusBar;
}


double GameManager::NormalizeCoord(double pixels, double totalPixels) const {
  return 2.0 * pixels / totalPixels - 1.0;
}

inline void GameManager::Rotate(double x, double y, double degrees, double& xout, double& yout) const {
  static const double PI = 4 * atan(1.0);
  double theta = (degrees / 360.0) * (2 * PI);
  xout = x * cos(theta) + y * sin(theta);
  yout = y * cos(theta) - x * sin(theta);
}

inline KeyCode GameManager::ToKeyCode(unsigned char key) const {
  switch (key) {
  case '\x1B':
    return KeyCode::QUIT;
  case '\r':
    return KeyCode::ENTER;

  case 'w': case 'W':
    return KeyCode::UP;
  case 'a': case 'A':
    return KeyCode::LEFT;
  case 's': case 'S':
    return KeyCode::DOWN;
  case 'd': case 'D':
    return KeyCode::RIGHT;

  case ' ': case 'j': case 'J':
    return KeyCode::FIRE1;
  case 'k': case 'K':
    return KeyCode::FIRE2;

  default:
    return KeyCode::NONE;
  }
}

//inline KeyCode GameManager::SpecialToKeyCode(int key) const {
//  switch (key) {
//  case GLUT_KEY_UP:
//    return KeyCode::UP;
//  case GLUT_KEY_LEFT:
//    return KeyCode::LEFT;
//  case GLUT_KEY_DOWN:
//    return KeyCode::DOWN;
//  case GLUT_KEY_RIGHT:
//    return KeyCode::RIGHT;
//
//  case GLUT_KEY_CTRL_L:
//    return KeyCode::FIRE2;
//
//  default:
//    return KeyCode::NONE;
//  }
//}