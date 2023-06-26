cmake_minimum_required(VERSION 3.16)


add_library(
  Projectiles
  STATIC
  Projectiles.hpp
  Projectiles.cpp
)

target_link_libraries(
  Projectiles
  GameObject
  UI
)

target_include_directories(
  Projectiles
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/UI/
)