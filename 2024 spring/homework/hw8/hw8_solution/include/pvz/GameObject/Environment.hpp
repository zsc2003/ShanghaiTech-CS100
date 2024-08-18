#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameObject/Plants.hpp"

class Background : public GameObject {
public:
  explicit Background(GameWorld *world)
      : GameObject{ImageID::BACKGROUND, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,    LayerID::BACKGROUND,
                   WINDOW_WIDTH,        WINDOW_HEIGHT,    AnimID::NO_ANIMATION, world} {}
  void Update() override {}
  void OnClick() override {}
};

class PlantingSpot : public GameObject {
public:
  PlantingSpot(int row, int col, GameWorld *world)
      : GameObject{ImageID::NONE,
                   FIRST_COL_CENTER + col * LAWN_GRID_WIDTH,
                   FIRST_ROW_CENTER + row * LAWN_GRID_HEIGHT,
                   LayerID::UI,
                   60,
                   80,
                   AnimID::NO_ANIMATION,
                   world} {}
  void Update() override {}
  void OnClick() override;
};

class Sun : public GameObject {
public:
  Sun(int x, int y, GameWorld *world, bool isFromSky, int dropTime, int velocityY)
      : GameObject{ImageID::SUN, x, y, LayerID::SUN, 80, 80, AnimID::IDLE, world, STAY_TIME}, m_isFromSky{isFromSky},
        m_dropTime{dropTime}, m_velocityY{velocityY} {}

  static std::unique_ptr<Sun> CreateFromSunflower(const Sunflower &sunflower, GameWorld *world) {
    return std::make_unique<Sun>(sunflower.GetX(), sunflower.GetY(), world, false, 12, 4);
  }

  static std::unique_ptr<Sun> CreateFromSky(GameWorld *world) {
    return std::make_unique<Sun>(randInt(75, WINDOW_WIDTH - 75), WINDOW_HEIGHT - 1, world, true, randInt(63, 263), -2);
  }

  void Update() override;

  void OnClick() override;

private:
  bool m_isFromSky;
  int m_dropTime;
  int m_velocityY;

  static constexpr auto STAY_TIME = 300;
};

#endif // ENVIRONMENT_HPP