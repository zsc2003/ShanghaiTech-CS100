#ifndef PLANTS_HPP
#define PLANTS_HPP

#include "pvz/GameObject/GameObject.hpp"
#include "pvz/GameWorld/GameWorld.hpp"

class CooldownMask : public GameObject {
public:
  CooldownMask(int x, int y, GameWorld *world, int cooldownTime)
      : GameObject{ImageID::COOLDOWN_MASK, x,     y,           LayerID::COOLDOWN_MASK, SEED_WIDTH, SEED_HEIGHT,
                   AnimID::NO_ANIMATION,   world, cooldownTime} {}

  void Update() override { DecreaseHP(1); }

  void OnClick() override {}
};

class SeedBase : public GameObject {
public:
  SeedBase(ImageID imageID, int index, GameWorld *world, int price, int cooldownTime)
      : GameObject{imageID,    130 + index * 60, WINDOW_HEIGHT - 44,   LayerID::UI,
                   SEED_WIDTH, SEED_HEIGHT,      AnimID::NO_ANIMATION, world},
        m_price{price}, m_cooldownTime{cooldownTime} {}

  void Update() override {}

  void OnClick() override {
    if (GetWorld()->IsHoldingShovel() || GetWorld()->HasSelectedSeed())
      return;
    if (GetWorld()->GetSunlight() >= m_price) {
      GetWorld()->IncreaseSunlight(-m_price);
      GetWorld()->AddObject<CooldownMask>(GetX(), GetY(), GetWorld(), m_cooldownTime);
      GetWorld()->SetSelectedSeed(this);
    }
  }

  virtual void PlantAt(int x, int y) const = 0;

  virtual bool IsWallnut() const = 0;

private:
  int m_price;
  int m_cooldownTime;
};

class Wallnut;

template <typename PlantType> class Seed : public SeedBase {
public:
  using SeedBase::SeedBase;

  void PlantAt(int x, int y) const override { GetWorld()->AddObject<PlantType>(x, y, GetWorld()); }

  bool IsWallnut() const override { return std::is_same_v<PlantType, Wallnut>; }
};

class Shovel : public GameObject {
public:
  explicit Shovel(GameWorld *world)
      : GameObject{ImageID::SHOVEL, 600, WINDOW_HEIGHT - 40, LayerID::UI, 50, 50, AnimID::NO_ANIMATION, world} {}

  void Update() override {}

  void OnClick() override {
    if (GetWorld()->HasSelectedSeed())
      return;
    GetWorld()->SetHoldingShovel(!GetWorld()->IsHoldingShovel());
  }
};

class Plant : public GameObject {
public:
  Plant(ImageID image, int x, int y, GameWorld *world, int hp)
      : GameObject{image, x, y, LayerID::PLANTS, 60, 80, AnimID::IDLE, world, hp} {}

  void OnClick() override {
    if (GetWorld()->IsHoldingShovel()) {
      SetDead();
      GetWorld()->SetHoldingShovel(false);
    }
  }

  bool IsPlant() const final { return true; }
};

class Sunflower : public Plant {
public:
  Sunflower(int x, int y, GameWorld *world)
      : Plant{ImageID::SUNFLOWER, x, y, world, 300}, m_sunTimer{randInt(30, 600)} {}

  void Update() override;

  static std::unique_ptr<Seed<Sunflower>> CreateSeed(int index, GameWorld *world) {
    return std::make_unique<Seed<Sunflower>>(ImageID::SEED_SUNFLOWER, index, world, 50, 240);
  }

private:
  int m_sunTimer;

  static constexpr int PRODUCE_COOLDOWN = 600;
};

class Peashooter : public Plant {
public:
  Peashooter(int x, int y, GameWorld *world)
      : Plant{ImageID::PEASHOOTER, x, y, world, 300}, m_peaTimer{ATTACK_COOLDOWN} {}

  void Update() override;

  static std::unique_ptr<Seed<Peashooter>> CreateSeed(int index, GameWorld *world) {
    return std::make_unique<Seed<Peashooter>>(ImageID::SEED_PEASHOOTER, index, world, 100, 240);
  }

private:
  int m_peaTimer;

  static constexpr auto ATTACK_COOLDOWN = 30;
};

class Wallnut : public Plant {
public:
  Wallnut(int x, int y, GameWorld *world) : Plant{ImageID::WALLNUT, x, y, world, HP_MAX} {}

  void Update() override {
    if (IsCracked())
      ChangeImage(ImageID::WALLNUT_CRACKED);
  }

  void OnClick() override;

  static std::unique_ptr<Seed<Wallnut>> CreateSeed(int index, GameWorld *world) {
    return std::make_unique<Seed<Wallnut>>(ImageID::SEED_WALLNUT, index, world, 50, 900);
  }

private:
  static constexpr auto HP_MAX = 4000;

  bool IsCracked() const { return 3 * GetHP() < HP_MAX; }
};

class CherryBomb : public Plant {
public:
  CherryBomb(int x, int y, GameWorld *world)
      : Plant{ImageID::CHERRY_BOMB, x, y, world, 4000}, m_explodeTimer{EXPLODE_PREPARE} {}

  void Update() override;

  static std::unique_ptr<Seed<CherryBomb>> CreateSeed(int index, GameWorld *world) {
    return std::make_unique<Seed<CherryBomb>>(ImageID::SEED_CHERRY_BOMB, index, world, 150, 1200);
  }

private:
  int m_explodeTimer;

  static constexpr auto EXPLODE_PREPARE = 15;
};

class Repeater : public Plant {
public:
  Repeater(int x, int y, GameWorld *world)
      : Plant{ImageID::REPEATER, x, y, world, 300}, m_isRed{false}, m_attackTimer{ATTACK_COOLDOWN},
        m_secondPeaTimer{0} {}

  void Update() override;

  static std::unique_ptr<Seed<Repeater>> CreateSeed(int index, GameWorld *world) {
    return std::make_unique<Seed<Repeater>>(ImageID::SEED_REPEATER, index, world, 200, 240);
  }

private:
  bool m_isRed;
  int m_attackTimer;
  int m_secondPeaTimer;

  static constexpr auto ATTACK_COOLDOWN = 30;
  static constexpr auto SECOND_PEA_COOLDOWN = 5;
};

#endif // PLANTS_HPP
