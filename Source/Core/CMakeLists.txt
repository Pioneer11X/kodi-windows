include(${CMAKE_CURRENT_LIST_DIR}/Events/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/FrameWorks/CMakeLists.txt)

target_sources(
Kodi-Engine PUBLIC
  "${CMAKE_CURRENT_LIST_DIR}/CoreEngine.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/CoreEngine.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/CoreEvents.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/CoreEvents.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/stb_image.h"
)
