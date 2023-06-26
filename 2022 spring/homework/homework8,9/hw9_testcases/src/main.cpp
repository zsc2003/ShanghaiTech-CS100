#include <iostream>
#include <memory>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "GameManager.h"
#include "GameWorld.h"
#include "ObjectBase.h"

#define LOCAL_TEST

#define TEST_ALL

inline void report_if_wrong(bool condition, long line) {
  if (!condition) {
#ifdef LOCAL_TEST
    std::cout << "Wrong answer on line " << line << std::endl;
#else
    std::ofstream ofs("./out.txt");
    ofs << "Wrong answer on line " << line << std::endl;
    ofs.close();
#endif // LOCAL_TEST
    exit(0);
  }
}

#ifdef assert
#undef assert
#endif

#define assert(COND) report_if_wrong(COND, __LINE__)
#define NO_ADDITIONAL_TEST [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {}

const int DAWNBREAKER_X = 100;
const int DAWNBREAKER_Y = 750;
const int BLUEBULLET_X = 100;
const int BLUEBULLET_Y = 300;
const int METEOR_X = 100;
const int METEOR_Y = 700;
const int ENEMY_X = 500;
const int ENEMY_Y = 500;
const int REDBULLET_X = ENEMY_X;
const int REDBULLET_Y = ENEMY_Y;
const int GOODIE_X = 500;
const int GOODIE_Y = 100;

// Updating the game while freezing each object at fixed positions
void freeze(std::shared_ptr<GameWorld> world, int frames) {
  for (auto& obj : ObjectBase::GetObjects(0)) {
    if (obj->GetImageID() == IMGID_DAWNBREAKER) {
      obj->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
      break;
    }
  }
  for (int i = 0; i < frames; i++) {
    // Dawnbreaker & Enemies
    for (auto& obj : ObjectBase::GetObjects(0)) {
      if (obj->GetImageID() != IMGID_DAWNBREAKER) {
        obj->MoveTo(ENEMY_X, ENEMY_Y);
      }
    }
    // Projectiles
    for (auto& obj : ObjectBase::GetObjects(1)) {
      if (obj->GetImageID() == IMGID_BLUE_BULLET) {
        obj->MoveTo(BLUEBULLET_X, BLUEBULLET_Y);
      } else if (obj->GetImageID() == IMGID_METEOR) {
        obj->MoveTo(METEOR_X, METEOR_Y);
      } else if (obj->GetImageID() == IMGID_RED_BULLET) {
        obj->MoveTo(REDBULLET_X, REDBULLET_Y);
      }
    }
    // Goodies
    for (auto& obj : ObjectBase::GetObjects(2)) {
      obj->MoveTo(GOODIE_X, GOODIE_Y);
    }
    world->Update();
  }
}

template<typename Func1, typename Func2, typename OnceFunc>
void testProbability(std::shared_ptr<GameWorld> world, double probability, 
  Func1 testProcedure, Func2 eventHappened, OnceFunc additionalTest, int iterations = 100000) {
  double eventHappenedCount = 0;
  bool flagAdditionalTest = false;
  for (int i = 0; i < iterations; i++) {
    world->Init();
    world->SetScore(0);
    ObjectBase* target = nullptr;
    testProcedure(world, target);
    if (eventHappened(world, target)) {
      if (!flagAdditionalTest) {
        additionalTest(world, target);
        flagAdditionalTest = true;
      }
      eventHappenedCount++;
    }
    world->CleanUp();
#ifdef LOCAL_TEST
    if (i % (iterations / 10) == 0) {
      std::cout << i * 100 / iterations << "%" << std::endl;
    }
#endif
  }
#ifdef LOCAL_TEST
  std::cout << "Deviation: " << eventHappenedCount - (probability * iterations) << std::endl;
  std::cout << "4 sigma: " << 4 * std::sqrt((double)iterations * probability * (1.0 - probability)) << std::endl;
#endif
  assert(std::abs(eventHappenedCount - (probability * iterations)) <= 4 * std::sqrt((double)iterations * probability * (1.0 - probability)));
}

inline std::string status() {
  std::string statusBar = GameManager::Instance().GetStatusBarMessage();
  return statusBar.substr(0, statusBar.find_first_of('\n'));
}

ObjectBase* findObject(int layer, int imageID) {
  for (auto& obj : ObjectBase::GetObjects(layer)) {
    if (obj->GetImageID() == imageID) {
      return obj;
    }
  }
  return nullptr;
}

int main(int argc, char** argv) {
  std::shared_ptr<GameWorld> world = std::make_shared<GameWorld>();
  GameManager::Instance().Play(argc, argv, world);
  
#ifdef LOCAL_TEST

#ifdef TEST_ALL
  for (int tcase = 1; tcase <= 20; tcase++) {
#else
  int tcase = 0;
  std::cin >> tcase;
  //int tcase = 1;
#endif // TEST_ALL

#else
  int tcase = atoi(argv[1]);
#endif // LOCAL_TEST

  GameManager::Instance().ClearKeys();
  world->SetLevel(1);
  world->SetScore(0);
  //std::thread timerThread(&timer, 15000, tcase); // 15 sec per case
  try {
    switch (tcase)
    {
    case 1: // A multi-file check by python script.
    {
      break;
    }
    case 2: // A CMake target number check by python script.
    {
      break;
    }
    case 3: // 3% chance to add an enemy during frame 1, level 1.
    {
      testProbability(world, 0.03,
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          world->Update();
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) -> bool {
          assert(ObjectBase::GetObjects(0).size() <= 2);
          target = findObject(0, IMGID_ALPHATRON);
          return target != nullptr;
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          assert(target->GetImageID() == IMGID_ALPHATRON);
          assert(target->GetDirection() == 180);
          assert(target->GetSize() == 1.0);
          assert(target->GetY() == WINDOW_HEIGHT - 1 || target->GetY() == WINDOW_HEIGHT - 1 - 2);
        }, 20000);
      break;
    }
    case 4: // 6/173 chance that an enemy is Alphatron in level 35.
    {
      testProbability(world, 6.0 / 173.0,
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) { 
          world->SetLevel(35);
          while (ObjectBase::GetObjects(0).size() < 2) {
            world->Update();
          }
          target = findObject(0, IMGID_ALPHATRON);
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) -> bool {
          return target != nullptr;
        },
        NO_ADDITIONAL_TEST, 10000);
      break;
    }
    case 5: // 99/173 chance that an enemy is Omegatron in level 35.
    {
      testProbability(world, 99.0 / 173.0,
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          world->SetLevel(35);
          while (ObjectBase::GetObjects(0).size() < 2) {
            world->Update();
          }
          target = findObject(0, IMGID_OMEGATRON);
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) -> bool {
          return target != nullptr;
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          assert(target->GetImageID() == IMGID_OMEGATRON);
          assert(target->GetDirection() == 180);
          assert(target->GetSize() == 1.0);
          assert(target->GetY() == WINDOW_HEIGHT - 1 || target->GetY() == WINDOW_HEIGHT - 1 - 11);
        }, 10000);
      break;
    }
    case 6: // Status bar on first frame
    {
      world->Init();
      world->Update();
      assert(status() == "HP: 100/100   Meteors: 0   Lives: 3   Level: 1   Enemies: 0/3   Score: 0");
      world->CleanUp();
      break;
    }
    case 7: // Crash against an Alphatron
    {
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();
    
      // Create an Alphatron
      while (ObjectBase::GetObjects(0).size() < 2) {
        world->Update();
      }

      auto iter = ObjectBase::GetObjects(0).begin();
      while (iter != ObjectBase::GetObjects(0).end()) {
        if (*iter != dawnbreaker) {
          (*iter)->MoveTo(100, 100);
        }
        iter++;
      }

      dawnbreaker->MoveTo(100, 100);
      world->Update();
      assert(ObjectBase::GetObjects(0).size() == 1);
      assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 1   Enemies: 1/3   Score: 50");
      assert(ObjectBase::GetObjects(3).size() == 1);
      ObjectBase* explosion = *ObjectBase::GetObjects(3).begin();
      assert(explosion->GetImageID() == IMGID_EXPLOSION);
      assert(explosion->GetDirection() == 0);
      assert(explosion->GetSize() == 4.5 || explosion->GetSize() == 4.3);
      assert(explosion->GetX() == 100 && explosion->GetY() == 100);

      world->Update();
      assert(explosion->GetSize() == 4.3 || explosion->GetSize() == 4.1);

      for (int i = 0; i < 20; i++) {
        world->Update();
      }
      assert(ObjectBase::GetObjects(3).size() == 0);
      world->CleanUp();
      break;
    }
    case 8: // Clear level 1 by crashing against Alphatrons
    {
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();
    
      // Create all 3 Alphatrons
      freeze(world, 1000);
      assert(ObjectBase::GetObjects(0).size() == 4);

      auto iter = ObjectBase::GetObjects(0).begin();
      int numAlphatron = 1;
      while (iter != ObjectBase::GetObjects(0).end()) {
        if (*iter != dawnbreaker) {
          (*iter)->MoveTo(numAlphatron * 100, numAlphatron * 100);
          numAlphatron++;
        }
        iter++;
      }

      dawnbreaker->MoveTo(100, 100);
      world->Update();
      assert(ObjectBase::GetObjects(0).size() == 3);
      assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 1   Enemies: 1/3   Score: 50");
      dawnbreaker->MoveTo(200, 200);
      world->Update();
      assert(ObjectBase::GetObjects(0).size() == 2);
      assert(status() == "HP: 60/100   Meteors: 0   Lives: 3   Level: 1   Enemies: 2/3   Score: 100");
      dawnbreaker->MoveTo(300, 300);
      if (world->Update() != LevelStatus::LEVEL_CLEARED) {
        assert(world->Update() == LevelStatus::LEVEL_CLEARED);
      }
      world->CleanUp();
      break;
    }
    case 9: // Alphatron behaviors
    {
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

      // Create an Alphatron
      while (ObjectBase::GetObjects(0).size() < 2) {
        world->Update();
      }

      ObjectBase* alphatron = findObject(0, IMGID_ALPHATRON);
      assert(alphatron != nullptr);

      alphatron->MoveTo(300, 600);
      dawnbreaker->MoveTo(300, 100);

      while (ObjectBase::GetObjects(1).size() < 1) {
        world->Update();
        alphatron->MoveTo(300, 600);
      }

      ObjectBase* redBullet = findObject(1, IMGID_RED_BULLET);
      assert(redBullet != nullptr);
      assert(redBullet->GetImageID() == IMGID_RED_BULLET);
      assert(redBullet->GetDirection() == 180);
      assert(redBullet->GetSize() == 0.5);
      assert(redBullet->GetX() == 300 && (redBullet->GetY() == 550 || redBullet->GetY() == 544));
      world->Update();
      assert(redBullet->GetX() == 300 && (redBullet->GetY() == 544 || redBullet->GetY() == 538));

      redBullet->MoveTo(300, 100);
      world->Update();
      assert(ObjectBase::GetObjects(1).size() == 0);
      assert(status() == "HP: 95/100   Meteors: 0   Lives: 3   Level: 1   Enemies: 0/3   Score: 0");

      alphatron->MoveTo(-1, 300);
      world->Update();
      assert(alphatron->GetX() == 1 && alphatron->GetY() == 298);

      alphatron->MoveTo(WINDOW_WIDTH, 300);
      world->Update();
      assert(alphatron->GetX() == WINDOW_WIDTH - 2 && alphatron->GetY() == 298);

      world->CleanUp();
      break;
    }
    case 10: // Shooting an Alphatron
    {
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

      // Create an Alphatron
      while (ObjectBase::GetObjects(0).size() < 2) {
        world->Update();
      }

      ObjectBase* alphatron = findObject(0, IMGID_ALPHATRON);
      assert(alphatron != nullptr);

      GameManager::Instance().KeyDownEvent(' ', 0, 0);
      alphatron->MoveTo(ENEMY_X, ENEMY_Y);
      dawnbreaker->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
      world->Update();
      assert(ObjectBase::GetObjects(1).size() == 1);
      ObjectBase* blueBullet = findObject(1, IMGID_BLUE_BULLET);
      assert(blueBullet != nullptr);
      blueBullet->MoveTo(ENEMY_X, ENEMY_Y);
      world->Update();
      assert(ObjectBase::GetObjects(1).size() == 0);
      world->CleanUp();
      break;
    }
    case 11: // Shooting -- double-checking collision
    {
      {
        world->SetLevel(1);
        world->Init();
        ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

        // Make sure a bullet spawns first
        GameManager::Instance().KeyDownEvent(' ', 0, 0);
        world->Update();
        while (ObjectBase::GetObjects(0).size() == 2) {
          world->CleanUp();
          world->Init();
          dawnbreaker = *ObjectBase::GetObjects(0).begin();
          world->Update();
        }
        GameManager::Instance().KeyUpEvent(' ', 0, 0);

        assert(ObjectBase::GetObjects(1).size() == 1);
        ObjectBase* blueBullet = findObject(1, IMGID_BLUE_BULLET);
        assert(blueBullet != nullptr);

        // Create an Alphatron
        while (ObjectBase::GetObjects(0).size() < 2) {
          freeze(world, 1);
        }

        ObjectBase* alphatron = findObject(0, IMGID_ALPHATRON);
        assert(alphatron != nullptr);

        alphatron->MoveTo(-1, 200 + 2 * 2);
        blueBullet->MoveTo(3, 200 - 44 - 6 * 2);
        world->Update();
        assert(ObjectBase::GetObjects(1).size() == 1);
        assert(alphatron->GetX() == 1 && alphatron->GetY() == 200 + 2);
        assert(blueBullet->GetX() == 3 && blueBullet->GetY() == 200 - 44 - 6);

        world->Update();
        assert(ObjectBase::GetObjects(1).size() == 0);
        world->CleanUp();
      }
      // The same process, with the creation order reversed.
      {
        world->SetLevel(1);
        world->Init();
        ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

        // Create an Alphatron
        while (ObjectBase::GetObjects(0).size() < 2) {
          freeze(world, 1);
        }

        freeze(world, 1);
        GameManager::Instance().KeyDownEvent(' ', 0, 0);
        world->Update();
        GameManager::Instance().KeyUpEvent(' ', 0, 0);

        assert(ObjectBase::GetObjects(1).size() == 1);
        ObjectBase* blueBullet = findObject(1, IMGID_BLUE_BULLET);
        assert(blueBullet != nullptr);


        ObjectBase* alphatron = findObject(0, IMGID_ALPHATRON);
        assert(alphatron != nullptr);

        alphatron->MoveTo(-1, 200 + 2 * 2);
        blueBullet->MoveTo(3, 200 - 44 - 6 * 2);
        world->Update();
        assert(ObjectBase::GetObjects(1).size() == 1);
        assert(alphatron->GetX() == 1 && alphatron->GetY() == 200 + 2);
        assert(blueBullet->GetX() == 3 && blueBullet->GetY() == 200 - 44 - 6);

        world->Update();
        assert(ObjectBase::GetObjects(1).size() == 0);
        world->CleanUp();
      }
      break;
    }
    case 12: // Killing an Alphatron
    {
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

      // 5 bullets
      GameManager::Instance().KeyDownEvent(' ', 0, 0);
      freeze(world, 44);
      GameManager::Instance().KeyUpEvent(' ', 0, 0);

      assert(ObjectBase::GetObjects(1).size() == 5);

      // Create an Alphatron
      while (ObjectBase::GetObjects(0).size() < 2) {
        freeze(world, 1);
      }

      ObjectBase* alphatron = findObject(0, IMGID_ALPHATRON);
      assert(alphatron != nullptr);

      for (int i = 0; i < 5; i++) {
        alphatron->MoveTo(20, 200);
        ObjectBase* blueBullet = findObject(1, IMGID_BLUE_BULLET);
        assert(blueBullet != nullptr);
        blueBullet->MoveTo(20, 190);
        world->Update();
        assert(ObjectBase::GetObjects(1).size() == 4 - i);
      }

      // That Alphatron at y = 200 should have died
      for (auto& obj : ObjectBase::GetObjects(0)) {
        if (obj->GetImageID() != IMGID_DAWNBREAKER) {
          assert(obj->GetY() > 200);
        }
      }
      assert(world->GetScore() == 50);
      assert(status() == "HP: 100/100   Meteors: 0   Lives: 3   Level: 1   Enemies: 1/3   Score: 50");

      world->CleanUp();
      break;
    }
    case 13: // Sigmatron behaviors
    {
      world->SetLevel(35);
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

      // Re-roll so that the first enemy is a Sigmatron
      ObjectBase* sigmatron = nullptr;
      while ((sigmatron = findObject(0, IMGID_SIGMATRON)) == nullptr) {
        world->CleanUp();
        world->Init();
        dawnbreaker = *ObjectBase::GetObjects(0).begin();
        world->Update();
      }
      assert(sigmatron->GetDirection() == 180);
      assert(sigmatron->GetSize() == 1.0);
      assert(sigmatron->GetY() == WINDOW_HEIGHT - 1 || sigmatron->GetY() == WINDOW_HEIGHT - 1 - 9);

      sigmatron->MoveTo(-1, 600);
      world->Update();
      assert(sigmatron->GetX() == 8 && sigmatron->GetY() == 591);

      world->Update();
      assert(sigmatron->GetX() == 17 && sigmatron->GetY() == 582);

      dawnbreaker->MoveTo(25, 100);

      world->Update();
      assert(sigmatron->GetX() == 17 && sigmatron->GetY() == 572);

      dawnbreaker->MoveTo(100, 100);
      world->Update();
      assert(sigmatron->GetX() == 17 && sigmatron->GetY() == 562);

      world->CleanUp();
      break;
    }
    case 14: // 20%: drop an HP restore goodie & HP restore goodie tests
    {
      testProbability(world, 0.2,
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          world->SetLevel(35);
          ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

          // Re-roll so that the first enemy is a Sigmatron
          ObjectBase* sigmatron = nullptr;
          while ((sigmatron = findObject(0, IMGID_SIGMATRON)) == nullptr) {
            world->CleanUp();
            world->Init();
            dawnbreaker = *ObjectBase::GetObjects(0).begin();
            world->Update();
          }

          dawnbreaker->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
          sigmatron->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y + 59);
          world->Update();
          assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 100");

          target = findObject(2, IMGID_HP_RESTORE_GOODIE);
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) -> bool {
          return target != nullptr;
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          assert(target->GetImageID() == IMGID_HP_RESTORE_GOODIE);
          assert(target->GetDirection() == 0);
          assert(target->GetSize() == 0.5);
          assert(target->GetX() == DAWNBREAKER_X && (target->GetY() == DAWNBREAKER_Y + 59 || target->GetY() == DAWNBREAKER_Y + 59 - 2));
        
          freeze(world, 1);

          target->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y + 48);
          world->Update();
          assert(world->GetScore() == 100);
          assert(target->GetX() == DAWNBREAKER_X && target->GetY() == DAWNBREAKER_Y + 46);

          world->Update();
          assert(world->GetScore() == 120);
          assert(status() == "HP: 100/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 120");
          assert(findObject(2, IMGID_HP_RESTORE_GOODIE) == nullptr);
        }, 5000);
      break;
    }
    case 15: // Omegatron behaviors
    {
      world->SetLevel(35);
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

      // Re-roll so that the first enemy is an Omegatron
      ObjectBase* omegatron = nullptr;
      while ((omegatron = findObject(0, IMGID_OMEGATRON)) == nullptr) {
        world->CleanUp();
        world->Init();
        dawnbreaker = *ObjectBase::GetObjects(0).begin();
        world->Update();
      }
      assert(omegatron->GetDirection() == 180);
      assert(omegatron->GetSize() == 1.0);
      assert(omegatron->GetY() == WINDOW_HEIGHT - 1 || omegatron->GetY() == WINDOW_HEIGHT - 1 - 11);
      world->Update();
      assert(ObjectBase::GetObjects(1).size() >= 2);
      ObjectBase* lBullet = nullptr;
      ObjectBase* rBullet = nullptr;
      for (auto& obj : ObjectBase::GetObjects(1)) {
        if (obj->GetY() < WINDOW_HEIGHT - 1 - 50 - 6) {
          if (obj->GetDirection() == 198) {
            assert(lBullet == nullptr);
            lBullet = obj;
          }
          else if (obj->GetDirection() == 162) {
            assert(rBullet == nullptr);
            rBullet = obj;
          }
        }
      }
      assert(lBullet != nullptr && rBullet != nullptr);

      omegatron->MoveTo(-1, 600);
      world->Update();
      assert(omegatron->GetX() == 10 && omegatron->GetY() == 589);

      world->Update();
      assert(omegatron->GetX() == 21 && omegatron->GetY() == 578);

      freeze(world, 1);

      lBullet->MoveTo(200, 500);
      rBullet->MoveTo(200, 500);
      world->Update();
      assert(lBullet->GetX() == 198 && lBullet->GetY() == 494);
      assert(rBullet->GetX() == 202 && rBullet->GetY() == 494);
      world->Update();
      assert(lBullet->GetX() == 196 && lBullet->GetY() == 488);
      assert(rBullet->GetX() == 204 && rBullet->GetY() == 488);

      lBullet->MoveTo(DAWNBREAKER_X + 2, DAWNBREAKER_Y + 44 + 6);
      world->Update();
      assert(status() == "HP: 28/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 0/105   Score: 0");

      world->CleanUp();
      break;
    }
    case 16: // Omegatron energy
    {
      world->SetLevel(35);
      world->Init();
      ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

      // Re-roll so that the first enemy is an Omegatron
      ObjectBase* omegatron = nullptr;
      while ((omegatron = findObject(0, IMGID_OMEGATRON)) == nullptr) {
        world->CleanUp();
        world->Init();
        dawnbreaker = *ObjectBase::GetObjects(0).begin();
        world->Update();
      }
      world->Update();
      assert(ObjectBase::GetObjects(1).size() >= 2);
      ObjectBase* lBullet = nullptr;
      ObjectBase* rBullet = nullptr;
      for (auto& obj : ObjectBase::GetObjects(1)) {
        if (obj->GetY() < WINDOW_HEIGHT - 1 - 50 - 6) {
          if (obj->GetDirection() == 198) {
            assert(lBullet == nullptr);
            lBullet = obj;
          }
          else if (obj->GetDirection() == 162) {
            assert(rBullet == nullptr);
            rBullet = obj;
          }
        }
      }
      assert(lBullet != nullptr && rBullet != nullptr);

      freeze(world, 48);

      lBullet = nullptr;
      rBullet = nullptr;
      omegatron->MoveTo(500, 200);
      world->Update();
      world->Update();
      world->Update(); // The latest frame when shooting bullets is tolerated.
      for (auto& obj : ObjectBase::GetObjects(1)) {
        if (obj->GetY() < 200) {
          if (obj->GetDirection() == 198) {
            assert(lBullet == nullptr);
            lBullet = obj;
          }
          else if (obj->GetDirection() == 162) {
            assert(rBullet == nullptr);
            rBullet = obj;
          }
        }
      }
      assert(lBullet != nullptr && rBullet != nullptr);

      world->CleanUp();
      break;
    }
    case 17: // 40% * 80%: drop a power up goodie & power up goodie tests
    {
      testProbability(world, 0.4 * 0.8,
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          world->SetLevel(35);
          ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

          // Re-roll so that the first enemy is an Omegatron
          ObjectBase* omegatron = nullptr;
          while ((omegatron = findObject(0, IMGID_OMEGATRON)) == nullptr) {
            world->CleanUp();
            world->Init();
            dawnbreaker = *ObjectBase::GetObjects(0).begin();
            world->Update();
          }

          freeze(world, 1);
          dawnbreaker->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
          omegatron->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y + 59);
          world->Update();
          assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 200");

          target = findObject(2, IMGID_POWERUP_GOODIE);
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) -> bool {
          return target != nullptr;
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          assert(target->GetImageID() == IMGID_POWERUP_GOODIE);
          assert(target->GetDirection() == 0);
          assert(target->GetSize() == 0.5);
          assert(target->GetX() == DAWNBREAKER_X && (target->GetY() == DAWNBREAKER_Y + 59 || target->GetY() == DAWNBREAKER_Y + 59 - 2));

          GameManager::Instance().KeyDownEvent(' ', 0, 0);
          freeze(world, 1);
          GameManager::Instance().KeyUpEvent(' ', 0, 0);

          ObjectBase* originalBullet = findObject(1, IMGID_BLUE_BULLET);
          assert(originalBullet != nullptr);
          freeze(world, 10);

          // Collide with power up goodie
          target->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y + 48);
          world->Update();
          assert(world->GetScore() == 200);
          assert(target->GetX() == DAWNBREAKER_X && target->GetY() == DAWNBREAKER_Y + 46);

          world->Update();
          assert(world->GetScore() == 220);
          assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 220");
          assert(findObject(2, IMGID_POWERUP_GOODIE) == nullptr);

          // fire a new bullet
          GameManager::Instance().KeyDownEvent(' ', 0, 0);
          world->Update();
          assert(originalBullet->GetSize() == 0.5);
          originalBullet->MoveTo(originalBullet->GetX(), WINDOW_HEIGHT + 1);
          world->Update();
          ObjectBase* newBullet = findObject(1, IMGID_BLUE_BULLET);
          assert(newBullet->GetSize() == 0.6);
          assert(newBullet->GetY() > DAWNBREAKER_Y);
        
          // freeze while holding FIRE1 to create 7 bullets (8 atk)
          freeze(world, 66);
          GameManager::Instance().KeyUpEvent(' ', 0, 0);


          ObjectBase* omegatron = nullptr;
          while ((omegatron = findObject(0, IMGID_OMEGATRON)) == nullptr) {
            freeze(world, 1);
          }

          // Destroy an Omegatron (55 HP).
          for (int i = 0; i < 7; i++) {
            omegatron->MoveTo(20, 200);
            ObjectBase* blueBullet = findObject(1, IMGID_BLUE_BULLET);
            assert(blueBullet != nullptr);
            assert(blueBullet->GetSize() == 0.6);
            blueBullet->MoveTo(20, 190);
            assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 220");
            world->Update();
          }
          assert(world->GetScore() == 420);
          assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 2/105   Score: 420");
        }, 5000);
      break;
    }
    case 18: // 40% * 20%: drop a meteor goodie & meteor goodie tests
    {
      testProbability(world, 0.4 * 0.2,
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          world->SetLevel(35);
          ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

          // Re-roll so that the first enemy is an Omegatron
          ObjectBase* omegatron = nullptr;
          while ((omegatron = findObject(0, IMGID_OMEGATRON)) == nullptr) {
            world->CleanUp();
            world->Init();
            dawnbreaker = *ObjectBase::GetObjects(0).begin();
            world->Update();
          }

          freeze(world, 1);
          dawnbreaker->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
          omegatron->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y + 59);
          world->Update();
          assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 200");

          target = findObject(2, IMGID_METEOR_GOODIE);
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) -> bool {
          return target != nullptr;
        },
        [](std::shared_ptr<GameWorld> world, ObjectBase*& target) {
          assert(target->GetImageID() == IMGID_METEOR_GOODIE);
          assert(target->GetDirection() == 0);
          assert(target->GetSize() == 0.5);
          assert(target->GetX() == DAWNBREAKER_X && (target->GetY() == DAWNBREAKER_Y + 59 || target->GetY() == DAWNBREAKER_Y + 59 - 2));

          // Unable to fire a meteor without meteor goodie
          GameManager::Instance().KeyDownEvent('K', 0, 0);
          freeze(world, 1);
          GameManager::Instance().KeyUpEvent('K', 0, 0);
          assert(findObject(1, IMGID_METEOR) == nullptr);

          // Collide with meteor goodie
          target->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y + 48);
          world->Update();
          assert(world->GetScore() == 200);
          assert(target->GetX() == DAWNBREAKER_X && target->GetY() == DAWNBREAKER_Y + 46);

          world->Update();
          assert(world->GetScore() == 220);
          assert(status() == "HP: 80/100   Meteors: 1   Lives: 3   Level: 35   Enemies: 1/105   Score: 220");
          assert(findObject(2, IMGID_METEOR_GOODIE) == nullptr);

          // Fire a meteor
          freeze(world, 1);
          findObject(0, IMGID_DAWNBREAKER)->MoveTo(METEOR_X, METEOR_Y - 100);
          GameManager::Instance().KeyDownEvent('K', 0, 0);
          world->Update();
          ObjectBase* meteor = findObject(1, IMGID_METEOR);
          assert(meteor != nullptr);
          assert(meteor->GetImageID() == IMGID_METEOR);
          assert(meteor->GetDirection() == 0 || meteor->GetDirection() == 5);
          assert(meteor->GetSize() == 2.0);
          assert(meteor->GetX() == METEOR_X && (meteor->GetY() == METEOR_Y || meteor->GetY() == METEOR_Y + 2));
          assert(status() == "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: 1/105   Score: 220");

          meteor->SetDirection(80);
          freeze(world, 1);
          assert(meteor->GetDirection() == 85);
          assert(meteor->GetSize() == 2.0);
          assert(meteor->GetX() == METEOR_X && meteor->GetY() == METEOR_Y + 2);
          world->Update();
          assert(meteor->GetDirection() == 90);
          assert(meteor->GetSize() == 2.0);
          assert(meteor->GetX() == METEOR_X && meteor->GetY() == METEOR_Y + 4);

          // Generate some enemies
          freeze(world, 10);
          for (auto& obj : ObjectBase::GetObjects(0)) {
            if (obj->GetImageID() != IMGID_DAWNBREAKER) {
              obj->MoveTo(ENEMY_X, ENEMY_Y);
            }
          }

          // Wait for long enough to kill enemies, even if students have mistaken bullets to collide.
          int enemies = ObjectBase::GetObjects(0).size() - 1;
          int bullets = ObjectBase::GetObjects(1).size() - 1;
          int frames = enemies + bullets;
          meteor->MoveTo(ENEMY_X, ENEMY_Y);

          for (int i = 0; i < frames; i++) {
            for (auto& obj : ObjectBase::GetObjects(0)) {
              if (obj->GetImageID() == IMGID_DAWNBREAKER) {
                continue;
              }
              if (obj->GetY() > 800) {
                obj->MoveTo(1, WINDOW_HEIGHT - 1);
              }
              else {
                obj->MoveTo(ENEMY_X, ENEMY_Y);
              }
            }
            for (auto& obj : ObjectBase::GetObjects(1)) {
              if (obj != meteor && obj->GetY() > 800) {
                obj->MoveTo(1, WINDOW_HEIGHT - 1);
              }
              else {
                obj->MoveTo(ENEMY_X, ENEMY_Y);
              }
            }
            meteor->MoveTo(ENEMY_X, ENEMY_Y);
            world->Update();
          }
          assert(world->GetScore() >= 220 + 50 * enemies);
          int substringLength = enemies >= 9 ? 64 : 63;
          assert(status().substr(0, substringLength) ==
            "HP: 80/100   Meteors: 0   Lives: 3   Level: 35   Enemies: " + std::to_string(enemies + 1) + "/105");
          assert(ObjectBase::GetObjects(1).size() > bullets);
        }, 5000);
      break;
    }
    case 19: // Dying 3 times
    {
      for (int attempt = 0; attempt < 3; attempt++) {
        world->SetLevel(46);
        world->Init();
        ObjectBase* dawnbreaker = *ObjectBase::GetObjects(0).begin();

        while (ObjectBase::GetObjects(1).size() < 2) {
          freeze(world, 1);
        }
        freeze(world, 1);

        ObjectBase* bullet;
      
        assert(!world->IsGameOver());
        assert(status() == "HP: 100/100   Meteors: 0   Lives: " + std::to_string(3 - attempt) + "   Level: 46   Enemies: 0/138   Score: 0");

        bullet = findObject(1, IMGID_RED_BULLET);
        assert(bullet != nullptr);
        bullet->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
        assert(world->Update() == LevelStatus::ONGOING);
        bullet = findObject(1, IMGID_RED_BULLET);
        assert(bullet != nullptr);
        bullet->MoveTo(DAWNBREAKER_X, DAWNBREAKER_Y);
        assert(world->Update() == LevelStatus::DAWNBREAKER_DESTROYED);
        if (attempt == 2) {
          assert(world->IsGameOver());
        }
        world->CleanUp();
      }
      break;
    }
    case 20: // 5 points for free!!!
    {
      break;
    }
    default:
      assert(false);
      break;
    }
    //timerThread.detach();

    for (int i = 0; i < MAX_LAYERS; i++) {
      assert(ObjectBase::GetObjects(i).size() == 0);
    }
  }
  catch (std::exception& e) {
#ifdef LOCAL_TEST
    std::cout << "Runtime error in case " << tcase << std::endl;
#else
    std::ofstream ofs("./out.txt");
    ofs << "Runtime error in case " << tcase << std::endl;
    ofs.close();
#endif
    exit(0);
  }

#ifdef LOCAL_TEST
  std::cout << "Passed " << tcase << std::endl;
#ifdef TEST_ALL
  }
#endif // TEST_ALL

#else
  std::ofstream ofs("./out.txt");
  ofs << "Passed " << tcase << std::endl;
  ofs.close();
#endif // LOCAL_TEST
}

