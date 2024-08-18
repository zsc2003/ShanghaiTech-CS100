#ifndef WORLDBASE_H__
#define WORLDBASE_H__

#include <iostream>
#include <set>
#include <memory>

#include "pvz/utils.hpp"


class WorldBase {
public:
  WorldBase() = default;

  virtual ~WorldBase() = default;

  virtual void Init() = 0;

  virtual LevelStatus Update() = 0;

  virtual void CleanUp() = 0;

};


#endif // !WORLDBASE_H__
