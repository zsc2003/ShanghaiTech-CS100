#ifndef SEEDPACKET_HPP__
#define SEEDPACKET_HPP__

#include "GameObject.hpp"

class SeedPacket : public GameObject {
public:
  SeedPacket(ImageID imgID, int x, int y, pGameWorld world, int sunCost, int maxCoolDown);

  void Update() override;
  void OnClick() override;

  virtual void CreateSpawn() = 0;
protected:
  const int m_sunCost;
  const int m_maxCoolDown;
  int m_coolDownTime;
};

class SeedPacketCoolDown : public GameObject {
public:
  SeedPacketCoolDown(int x, int y, pGameWorld world, int coolDown);
  void Update() override;
private:
  int m_coolDown;
};

class SunflowerSeed : public SeedPacket {
public:
  SunflowerSeed(int x, int y, pGameWorld world);
  void CreateSpawn() override;
};

class PeashooterSeed : public SeedPacket {
public:
  PeashooterSeed(int x, int y, pGameWorld world);
  void CreateSpawn() override;
};

class WallnutSeed : public SeedPacket {
public:
  WallnutSeed(int x, int y, pGameWorld world);
  void CreateSpawn() override;
};

class CherryBombSeed : public SeedPacket {
public:
  CherryBombSeed(int x, int y, pGameWorld world);
  void CreateSpawn() override;
};

class RepeaterSeed : public SeedPacket {
public:
  RepeaterSeed(int x, int y, pGameWorld world);
  void CreateSpawn() override;
};

class ZombieSeed : public SeedPacket {
public:
  ZombieSeed(int x, int y, pGameWorld world);
  void CreateSpawn() override;
};


#endif // !SEEDPACKET_HPP__
