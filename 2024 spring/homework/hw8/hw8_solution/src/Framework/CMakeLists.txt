IF(APPLE)
  add_definitions(-DGL_SILENCE_DEPRECATION)
ENDIF()

set(FREEGLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/freeglut/include")

add_library(
  Framework
  STATIC
  ObjectBase.cpp
  TextBase.cpp
  GameManager.cpp
  SpriteManager.cpp
)

IF(APPLE)
  target_link_libraries(
    Framework
    SOIL
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework GLUT"
  )

ELSE()
  target_link_libraries(
    Framework
    freeglut
    SOIL
  )

  target_include_directories(
    Framework
    PUBLIC
    ${FREEGLUT_INCLUDE_DIR}
  )
ENDIF()
