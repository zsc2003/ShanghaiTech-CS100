add_library(
  GameWorld
  STATIC
  GameWorld.cpp
)

target_link_libraries(
  GameWorld
  Environment
  Plants
  Zombies
)
