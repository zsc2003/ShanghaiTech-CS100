#include "Zombies.hpp"
#include "UI.hpp"

#include "GameWorld.hpp"

Zombie::Zombie(ImageID imgID, int x, int y, pGameWorld world, int hp, int speed)
  : GameObject(imgID, x, y, LAYER_ZOMBIES, 20, 100, world, hp, 1, ANIMID_WALK_ANIM), m_speed(speed) {

}

void Zombie::Update() {
  if (!IsAlive()) {
    return;
  }

  SpecialActions();
  if (GetCurrentAnimation() != ANIMID_EAT_ANIM) {
    Move();
  }
}

void Zombie::Move() {
  MoveTo(GetX() - m_speed, GetY());
}

void Zombie::SpecialActions() {

}

void Zombie::OnCollision(std::shared_ptr<GameObject> other) {
  if (other->GetType() != GameObject::Type::Plant) {
    return;
  }

  // Shouldn't eat on special cases
  if (GetCurrentAnimation() != ANIMID_WALK_ANIM && GetCurrentAnimation() != ANIMID_EAT_ANIM) {
    return;
  }
  else {
    // Alive plant: start eating
    if (GetCurrentAnimation() == ANIMID_WALK_ANIM) {
      PlayAnimation(ANIMID_EAT_ANIM);
    }
  }


  other->TakeDamage(3);

}


RegularZombie::RegularZombie(int x, int y, pGameWorld world) : Zombie(IMGID_REGULAR_ZOMBIE, x, y, world, 200, 1) {}

BucketHeadZombie::BucketHeadZombie(int x, int y, pGameWorld world) : Zombie(IMGID_BUCKET_HEAD_ZOMBIE, x, y, world, 1300, 1) {}


void BucketHeadZombie::SpecialActions() {
  if (GetHP() <= 200) {
    ChangeImage(IMGID_REGULAR_ZOMBIE);
  }
}

PoleVaultingZombie::PoleVaultingZombie(int x, int y, pGameWorld world) : Zombie(IMGID_POLE_VAULTING_ZOMBIE, x, y, world, 340, 2), m_jumpCountDown(0) {
  PlayAnimation(ANIMID_RUN_ANIM);
}

void PoleVaultingZombie::SpecialActions() {
  if (GetCurrentAnimation() == ANIMID_RUN_ANIM) {
    MoveTo(GetX() - 40, GetY());
    if (GetWorld()->IsCollidingWithPlant(shared_from_this())) {
      PlayAnimation(ANIMID_JUMP_ANIM);
      m_speed = 0;
      m_jumpCountDown = 42;
    }
    MoveTo(GetX() + 40, GetY());
  }
  if (m_jumpCountDown > 0) {
    if (--m_jumpCountDown <= 0) {
      MoveTo(GetX() - 150, GetY());
      PlayAnimation(ANIMID_WALK_ANIM);
      m_speed = 1;
    }
  }
}
