
FILE(GLOB WindowFiles
  "${CMAKE_CURRENT_LIST_DIR}/WindowGLFW.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/WindowGLFW.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/WindowSDL.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/WindowSDL.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/WindowSFML.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/WindowSFML.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/WindowInterface.h"
  "${CMAKE_CURRENT_LIST_DIR}/WindowInterface.cpp"
)

target_sources(
Kodi-Engine PUBLIC
  ${WindowFiles}
)

source_group("Core\\Window"   FILES   ${WindowFiles})
