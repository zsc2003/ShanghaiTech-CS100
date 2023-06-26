#include "WorldBase.hpp"
#include "GameManager.hpp"

WorldBase::WorldBase() : m_wave(0), m_sun(50) {}

WorldBase::~WorldBase() {}

int WorldBase::GetWave() const {
  return m_wave;
}

void WorldBase::SetWave(int wave) {
  m_wave = wave;
}

int WorldBase::GetSun() const {
  return m_sun;
}

void WorldBase::SetSun(int sun) {
  m_sun = sun;
}

