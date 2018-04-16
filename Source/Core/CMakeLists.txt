include(${CMAKE_CURRENT_LIST_DIR}/Events/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/FrameWorks/CMakeLists.txt)
include(${CMAKE_CURRENT_LIST_DIR}/Graphics/CMakeLists.txt)

FILE(GLOB CoreFiles
  "${CMAKE_CURRENT_LIST_DIR}/CoreEngine.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/CoreEngine.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/CoreEvents.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/CoreEvents.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Texture.h"
  "${CMAKE_CURRENT_LIST_DIR}/Texture.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/stb_image.h"
)

target_sources(
Kodi-Engine PUBLIC
  ${CoreFiles}
)

source_group("Core"   FILES   ${CoreFiles})
