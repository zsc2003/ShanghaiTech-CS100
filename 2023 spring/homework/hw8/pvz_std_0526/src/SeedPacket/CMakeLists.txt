cmake_minimum_required(VERSION 3.16)

add_library(
  SeedPacket
  STATIC
  SeedPacket.hpp
  SeedPacket.cpp
  Spawn.hpp
)

target_link_libraries(
  SeedPacket
  Plants
  GameObject
)

target_include_directories(
  SeedPacket
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Plants/
)
