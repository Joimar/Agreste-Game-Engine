project("agreste-game-engine")
cmake_minimum_required(VERSION 3.22)

find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_library(SOIL2 soil2)

add_executable(agreste-game-engine
  Array.cpp
  Camera.cpp
  Cubemap.cpp
  Drawer.cpp
  GameBoard.cpp
  GameObject.cpp
  Mesh.cpp
  Model.cpp
  Physics.cpp
  Player.cpp
  shader.cpp
  source.cpp
  World.cpp
)

set_property(TARGET agreste-game-engine PROPERTY CXX_STANDARD 17)

target_link_libraries(agreste-game-engine GLEW::GLEW)
target_link_libraries(agreste-game-engine glm::glm)
target_link_libraries(agreste-game-engine glfw)
target_link_libraries(agreste-game-engine GL)
target_link_libraries(agreste-game-engine ${SOIL2})
target_link_libraries(agreste-game-engine assimp)
target_link_libraries(agreste-game-engine -lstdc++fs)