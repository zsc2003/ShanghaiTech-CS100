#ifndef GAMEWORLD_HPP__
#define GAMEWORLD_HPP__

#include <algorithm>
#include <list>
#include <memory>
#include <optional>

#include "pvz/Framework/TextBase.hpp"
#include "pvz/Framework/WorldBase.hpp"
#include "pvz/GameObject/GameObject.hpp"
#include "pvz/utils.hpp"

class Zombie;
class Plant;
class SeedBase;

class GameWorld : public WorldBase {
public:
  GameWorld() = default;

  ~GameWorld() = default;

  void Init() override;

  LevelStatus Update() override;

  void CleanUp() override {
    m_selectedSeed = nullptr;
    m_objects.clear();
    m_waveDisplay.reset();
    m_sunlightDisplay.reset();
  }

  /// @brief Increase the sunlight by @c inc. If @c inc is negative, the
  /// sunlight is actually decreased.
  void IncreaseSunlight(int inc) { m_sunlight += inc; }

  int GetSunlight() const { return m_sunlight; }

  void AddObject(std::unique_ptr<GameObject> object) { m_objects.push_back(std::move(object)); }

  template <typename T, typename... Args> void AddObject(Args &&...args) {
    AddObject(std::make_unique<T>(std::forward<Args>(args)...));
  }

  void SetSelectedSeed(const SeedBase *seed) {
    assert(!HasSelectedSeed());
    m_selectedSeed = seed;
  }

  bool HasSelectedSeed() const { return m_selectedSeed; }

  bool SelectedIsWallnut() const;

  void ReleaseSelectedSeed(int x, int y);

  void ResetSelectedSeed() { m_selectedSeed = nullptr; }

  bool IsHoldingShovel() const { return m_isHoldingShovel; }

  void SetHoldingShovel(bool holdingShovel = true) { m_isHoldingShovel = holdingShovel; }

  bool HasZombieOnRightOf(const Plant &plant) const;

  bool CollidesWithAnyPlant(const Zombie &zombie) const;

  static bool CollisionHappens(const GameObject &a, const GameObject &b) {
    return (std::abs(b.GetX() - a.GetX()) < ((a.GetWidth() + b.GetWidth()) / 2) &&
            std::abs(b.GetY() - a.GetY()) < ((a.GetHeight() + b.GetHeight()) / 2));
  }

  GameObject *GetLeftmostZombie() const;

private:
  int m_sunlight{};
  std::optional<TextBase> m_sunlightDisplay;
  int m_sunCD{};

  int m_waveCnt{};
  std::optional<TextBase> m_waveDisplay;
  int m_waveCD{};

  std::list<std::unique_ptr<GameObject>> m_objects;

  const SeedBase *m_selectedSeed;
  bool m_isHoldingShovel{};

  static constexpr auto TICKS_PER_SUN = 300;
  static constexpr auto FIRST_SUN_TIME = 180;
  static constexpr auto FIRST_WAVE_TIME = 1200;

  auto NextWaveTime() const { return std::max(150, 600 - 20 * m_waveCnt); }

  void GenerateWave();

  void PerformCollisions();
};

#endif // !GAMEWORLD_HPP__
