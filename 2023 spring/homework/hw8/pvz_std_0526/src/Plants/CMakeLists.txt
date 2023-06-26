cmake_minimum_required(VERSION 3.16)


add_library(
  Plants
  STATIC
  Plants.hpp
  Plants.cpp
)

target_link_libraries(
  Plants
  GameObject
  Projectiles
)

target_include_directories(
  Plants
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/Projectiles/
  ${CMAKE_SOURCE_DIR}/src/UI/
)
