#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <cassert>
#include <random>
#include <string>

// This relative path on Mac OS is different from that on other OS, because the
// way Xcode organizes the project files is different from others.
// Change it if the program fails to load assets. You may also use an absolute
// path.
#ifdef __APPLE__
static const std::string ASSET_DIR = "../../assets/";
#else
static const std::string ASSET_DIR = "../assets/";
#endif // __APPLE__

// Returns a random integer within [min, max] (inclusive).
inline int randInt(int min, int max) {
  if (max < min)
    std::swap(max, min);
  static std::random_device rd;
  static std::mt19937 generator(rd());
  std::uniform_int_distribution<> distro(min, max);
  return distro(generator);
}

enum class LevelStatus { ONGOING, LOSING };

enum class KeyCode {
  NONE,
  ENTER, // Enter
  QUIT   // Esc
};

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int LAWN_GRID_WIDTH = 80;
const int LAWN_GRID_HEIGHT = 100;

const int FIRST_ROW_CENTER = 75;
const int FIRST_COL_CENTER = 75;
const int GAME_ROWS = 5;
const int GAME_COLS = 9;

const int SEED_WIDTH = 50;
const int SEED_HEIGHT = 70;

enum class ImageID {
  NONE = 0,
  BACKGROUND,
  SUN,
  SHOVEL,
  COOLDOWN_MASK,
  SUNFLOWER = 10,
  PEASHOOTER,
  WALLNUT,
  CHERRY_BOMB,
  REPEATER,
  WALLNUT_CRACKED,
  RED_REPEATER,
  SEED_SUNFLOWER = 20,
  SEED_PEASHOOTER,
  SEED_WALLNUT,
  SEED_CHERRY_BOMB,
  SEED_REPEATER,
  SEED_RED_REPEATER,
  REGULAR_ZOMBIE = 30,
  BUCKET_HEAD_ZOMBIE,
  POLE_VAULTING_ZOMBIE,
  PEA = 40,
  EXPLOSION,
  RED_PEA,
  ZOMBIES_WON = 100
};

enum class AnimID { NO_ANIMATION = 0, IDLE, WALK, EAT, RUN, JUMP };

const int MAX_LAYERS = 7;

enum class LayerID {
  SUN = 0,
  ZOMBIES,
  PROJECTILES,
  PLANTS,
  COOLDOWN_MASK,
  UI,
  BACKGROUND,
};

const int MS_PER_FRAME = 33;

#endif // !UTILS_HPP__
