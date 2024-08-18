#ifndef ZOMBIES_HPP
#define ZOMBIES_HPP

#include "pvz/GameObject/GameObject.hpp"

class Zombie : public GameObject {
public:
  Zombie(ImageID imageID, int x, int y, GameWorld *world, int hp, int velocity, AnimID initialAnim = AnimID::WALK)
      : GameObject{imageID, x, y, LayerID::ZOMBIES, 20, 80, initialAnim, world, hp}, m_velocity{velocity} {}

  bool IsZombie() const final { return true; }

  bool IsWalking() const { return GetCurrentAnimation() == AnimID::WALK; }

  bool IsEating() const { return GetCurrentAnimation() == AnimID::EAT; }

  bool IsRunning() const { return GetCurrentAnimation() == AnimID::RUN; }

  void Hit(GameObject &other) override;

  void SetVelocity(int velocity) { m_velocity = velocity; }

private:
  int m_velocity;

protected:
  void DefaultUpdate() {
    if (!IsEating())
      MoveTo(GetX() - m_velocity, GetY());
  }
};

class RegularZombie : public Zombie {
public:
  RegularZombie(int x, int y, GameWorld *world) : Zombie{ImageID::REGULAR_ZOMBIE, x, y, world, HP_MAX, 1} {}

  void Update() final { DefaultUpdate(); }

  static constexpr auto HP_MAX = 200;
};

class BucketHeadZombie : public Zombie {
public:
  BucketHeadZombie(int x, int y, GameWorld *world)
      : Zombie{ImageID::BUCKET_HEAD_ZOMBIE, x, y, world, 1300, 1} {}

  void Update() final {
    if (GetHP() <= RegularZombie::HP_MAX)
      ChangeImage(ImageID::REGULAR_ZOMBIE);
    DefaultUpdate();
  }
};

class PoleVaultingZombie : public Zombie {
public:
  PoleVaultingZombie(int x, int y, GameWorld *world)
      : Zombie{ImageID::POLE_VAULTING_ZOMBIE, x, y, world, 340, 2, AnimID::RUN}, m_jumpTimer{0} {}

  void Update() final;

private:
  int m_jumpTimer;
};

#endif // ZOMBIES_HPP