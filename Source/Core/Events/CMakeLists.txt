FILE(GLOB EventFiles
  "${CMAKE_CURRENT_LIST_DIR}/EventGLFW.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventGLFW.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventInterface.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventInterface.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventSDL.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventSDL.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventSFML.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/EventSFML.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/KeyboardDefinitions"
  "${CMAKE_CURRENT_LIST_DIR}/MouseDefinitions.h"
)

target_sources(
Kodi-Engine PUBLIC
  ${EventFiles}
)

source_group("Core\\Events"   FILES   ${EventFiles})
