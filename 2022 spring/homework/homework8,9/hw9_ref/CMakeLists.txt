cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Dawnbreaker")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

#SET(FREEGLUT_REPLACE_GLUT ON CACHE BOOL "" FORCE)

add_subdirectory(
  "${CMAKE_CURRENT_LIST_DIR}/third_party/SOIL/"
  "${CMAKE_CURRENT_BINARY_DIR}/SOIL"
  EXCLUDE_FROM_ALL
)

add_subdirectory(
  "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/"
  "${CMAKE_CURRENT_BINARY_DIR}/freeglut"
  EXCLUDE_FROM_ALL
)

set(FREEGLUT_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/third_party/freeglut/include")

add_library(
  ProvidedFramework
  STATIC
  src/ProvidedFramework/ObjectBase.h
  src/ProvidedFramework/ObjectBase.cpp
  src/ProvidedFramework/WorldBase.h
  src/ProvidedFramework/WorldBase.cpp
  src/ProvidedFramework/GameManager.h
  src/ProvidedFramework/GameManager.cpp
  src/ProvidedFramework/SpriteManager.h
  src/ProvidedFramework/SpriteManager.cpp
  src/utils.h
)

target_link_libraries(
  ProvidedFramework
  freeglut
  SOIL
)

target_include_directories(
  ProvidedFramework
  PUBLIC 
  ${FREEGLUT_INCLUDE_DIR}
  src/
  src/ProvidedFramework/
)

#add_library(
#  PartForYou
#  STATIC
#  src/PartForYou/GameWorld.h
#  src/PartForYou/GameWorld.cpp
#  src/PartForYou/GameObjects.h
#  src/PartForYou/GameObjects.cpp
#  src/utils.h
#)
#
#target_link_libraries(
#  PartForYou
#  ProvidedFramework
#)
#
#target_include_directories(
#  PartForYou
#  PUBLIC 
#  src/
#  src/ProvidedFramework/
#  src/PartForYou/
#)

add_library(
  GameObject
  STATIC
  src/GameObject/GameObject.h
  src/GameObject/GameObject.cpp
)

target_link_libraries(
  GameObject
  ProvidedFramework
)

target_include_directories(
  GameObject
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
)

add_library(
  Background
  STATIC
  src/Background/Background.h
  src/Background/Background.cpp
  src/Background/Star.h
  src/Background/Star.cpp
  src/Background/Explosion.h
  src/Background/Explosion.cpp
)

target_link_libraries(
  Background
  GameObject
)

target_include_directories(
  Background
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
)

add_library(
  Projectile
  STATIC
  src/Projectile/Projectile.h
  src/Projectile/Projectile.cpp
  src/Projectile/BlueBullet.h
  src/Projectile/BlueBullet.cpp
  src/Projectile/Meteor.h
  src/Projectile/Meteor.cpp
  src/Projectile/RedBullet.h
  src/Projectile/RedBullet.cpp
)

target_link_libraries(
  Projectile
  GameObject
)

target_include_directories(
  Projectile
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
)

add_library(
  Dbreaker
  STATIC
  src/Dawnbreaker/Dawnbreaker.h
  src/Dawnbreaker/Dawnbreaker.cpp
)

target_link_libraries(
  Dbreaker
  GameObject
  Projectile
)

target_include_directories(
  Dbreaker
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
  src/Projectile/
)

add_library(
  Goodie
  STATIC
  src/Goodie/Goodie.h
  src/Goodie/Goodie.cpp
  src/Goodie/PowerUpGoodie.h
  src/Goodie/PowerUpGoodie.cpp
  src/Goodie/MeteorGoodie.h
  src/Goodie/MeteorGoodie.cpp
  src/Goodie/HpRestoreGoodie.h
  src/Goodie/HpRestoreGoodie.cpp
)

target_link_libraries(
  Goodie
  GameObject
  Dbreaker
)

target_include_directories(
  Goodie
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
  src/Dawnbreaker/
)

add_library(
  AlienShip
  STATIC
  src/AlienShip/AlienShip.h
  src/AlienShip/AlienShip.cpp
  src/AlienShip/Alphatron.h
  src/AlienShip/Alphatron.cpp
  src/AlienShip/Sigmatron.h
  src/AlienShip/Sigmatron.cpp
  src/AlienShip/Omegatron.h
  src/AlienShip/Omegatron.cpp
)

target_link_libraries(
  AlienShip
  GameObject
  Background
  Projectile
  Goodie
)

target_include_directories(
  AlienShip
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
  src/Background/
  src/Projectile/
  src/Goodie/
)

add_library(
  GameWorld
  STATIC
  src/GameWorld/GameWorld.h
  src/GameWorld/GameWorld.cpp
)

target_link_libraries(
  GameWorld
  GameObject
  Dbreaker
  Background
  Projectile
  Goodie
  AlienShip
)

target_include_directories(
  GameWorld
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
  src/GameObject/
  src/Dawnbreaker/
  src/Background/
  src/Projectile/
  src/Goodie/
  src/AlienShip/
)

add_executable(
  ${PROJECT_NAME}
  src/main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  ProvidedFramework
  GameWorld
)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  src/
  src/ProvidedFramework/
  src/GameWorld/
)
