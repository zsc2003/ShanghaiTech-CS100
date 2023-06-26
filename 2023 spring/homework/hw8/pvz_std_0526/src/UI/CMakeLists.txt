cmake_minimum_required(VERSION 3.16)


add_library(
  UI
  STATIC
  UI.hpp
  UI.cpp
)

target_link_libraries(
  UI
  GameObject
)

target_include_directories(
  UI
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
)