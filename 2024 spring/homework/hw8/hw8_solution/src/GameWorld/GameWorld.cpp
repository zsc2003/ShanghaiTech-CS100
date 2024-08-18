#include "pvz/GameWorld/GameWorld.hpp"
#include "pvz/GameObject/Environment.hpp"
#include "pvz/GameObject/Plants.hpp"
#include "pvz/GameObject/Zombies.hpp"

#include <algorithm>
#include <list>

bool GameWorld::SelectedIsWallnut() const {
  return m_selectedSeed->IsWallnut();
}

void GameWorld::ReleaseSelectedSeed(int x, int y) {
  m_selectedSeed->PlantAt(x, y);
  ResetSelectedSeed();
}

void GameWorld::Init() {
  m_sunlight = 50;
  m_sunlightDisplay.emplace(60, WINDOW_HEIGHT - 78);
  m_sunCD = FIRST_SUN_TIME;
  m_waveCnt = 0;
  m_waveDisplay.emplace(WINDOW_WIDTH - 160, 8, "", 0, 0, 0, false);
  m_waveCD = FIRST_WAVE_TIME;
  AddObject<Background>(this);
  AddObject(Sunflower::CreateSeed(0, this));
  AddObject(Peashooter::CreateSeed(1, this));
  AddObject(Wallnut::CreateSeed(2, this));
  AddObject(CherryBomb::CreateSeed(3, this));
  AddObject(Repeater::CreateSeed(4, this));
  AddObject<Shovel>(this);
  for (auto row = 0; row < GAME_ROWS; row++)
    for (auto col = 0; col < GAME_COLS; col++)
      AddObject<PlantingSpot>(row, col, this);
}

LevelStatus GameWorld::Update() {
  if (--m_sunCD == 0) {
    AddObject(Sun::CreateFromSky(this));
    m_sunCD = TICKS_PER_SUN;
  }

  if (--m_waveCD == 0) {
    ++m_waveCnt;
    GenerateWave();
    m_waveCD = NextWaveTime();
  }

  for (const auto &obj : m_objects) {
    if (!obj->IsDead())
      obj->Update();
  }

  PerformCollisions();

  m_objects.remove_if([](const auto &obj) { return obj->IsDead(); });

  if (std::any_of(m_objects.begin(), m_objects.end(),
                  [](const auto &obj) { return obj->IsZombie() && obj->GetX() < 0; })) {
    m_waveDisplay->SetColor(1, 1, 1);
    m_waveDisplay->MoveTo(330, 50);
    m_waveDisplay->SetText(std::to_string(m_waveCnt));
    return LevelStatus::LOSING;
  }

  for (const auto &obj : m_objects) {
    if (obj->IsZombie()) {
      auto zombie = static_cast<Zombie *>(obj.get());
      if (zombie->IsEating() && !CollidesWithAnyPlant(*zombie))
        zombie->PlayAnimation(AnimID::WALK);
    }
  }

  m_sunlightDisplay->SetText(std::to_string(m_sunlight));
  m_waveDisplay->SetText("Wave " + std::to_string(m_waveCnt));

  return LevelStatus::ONGOING;
}

bool GameWorld::HasZombieOnRightOf(const Plant &plant) const {
  return std::any_of(m_objects.begin(), m_objects.end(), [&plant](const auto &obj) {
    return obj->IsZombie() && std::abs(obj->GetY() - plant.GetY()) <= 1 && obj->GetX() > plant.GetX();
  });
}

bool GameWorld::CollidesWithAnyPlant(const Zombie &zombie) const {
  return std::any_of(m_objects.begin(), m_objects.end(),
                     [&zombie](const auto &obj) { return obj->IsPlant() && CollisionHappens(*obj, zombie); });
}

void GameWorld::GenerateWave() {
  for (int i = 0; i < (m_waveCnt + 15) / 10; i++) {
    int p1 = 20;
    int p2 = 2 * std::max(m_waveCnt - 8, 0);
    int p3 = 3 * std::max(m_waveCnt - 15, 0);

    int roll = randInt(1, p1 + p2 + p3);

    int x = randInt(WINDOW_WIDTH - 40, WINDOW_WIDTH - 1);
    int y = FIRST_ROW_CENTER + randInt(0, 4) * LAWN_GRID_HEIGHT;

    if (roll <= p1)
      AddObject<RegularZombie>(x, y, this);
    else if (roll <= p1 + p2)
      AddObject<PoleVaultingZombie>(x, y, this);
    else
      AddObject<BucketHeadZombie>(x, y, this);
  }
}

void GameWorld::PerformCollisions() {
  for (const auto &obj1 : m_objects)
    for (const auto &obj2 : m_objects) {
      if (obj1 == obj2 || obj1->IsDead() || obj2->IsDead())
        continue;
      if (CollisionHappens(*obj1, *obj2))
        obj1->Hit(*obj2);
    }
}

GameObject *GameWorld::GetLeftmostZombie() const {
  GameObject *ret{};
  for (const auto &obj : m_objects)
    if (obj->IsZombie() && (!ret || obj->GetX() < ret->GetX()))
      ret = obj.get();
  return ret;
}