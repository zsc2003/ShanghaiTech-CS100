cmake_minimum_required(VERSION 3.16)

add_library(
  GameWorld
  STATIC
  GameWorld.hpp
  GameWorld.cpp
)

target_link_libraries(
  GameWorld
  GameObject
  UI
  SeedPacket
  Plants
  Zombies
  Projectiles
)

target_include_directories(
  GameWorld
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/UI/
  ${CMAKE_SOURCE_DIR}/src/SeedPacket/
  ${CMAKE_SOURCE_DIR}/src/Plants/
  ${CMAKE_SOURCE_DIR}/src/Zombies/
  ${CMAKE_SOURCE_DIR}/src/Projectiles/
)
