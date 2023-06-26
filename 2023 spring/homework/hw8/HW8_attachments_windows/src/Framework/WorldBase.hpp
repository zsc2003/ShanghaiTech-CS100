#ifndef WORLDBASE_H__
#define WORLDBASE_H__

#include <iostream>
#include <set>
#include <memory>

#include "utils.hpp"


class WorldBase {
public:
  WorldBase();
  virtual ~WorldBase();

  virtual void Init() = 0;

  virtual LevelStatus Update() = 0;

  virtual void CleanUp() = 0;

  int GetWave() const;
  void SetWave(int level);

  int GetSun() const;
  void SetSun(int sun);

private:
  int m_wave;
  int m_sun;
};


#endif // !WORLDBASE_H__
