FILE(GLOB GraphicsFiles
  "${CMAKE_CURRENT_LIST_DIR}/Shader.hpp"
  "${CMAKE_CURRENT_LIST_DIR}/Shader.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Texture.h"
  "${CMAKE_CURRENT_LIST_DIR}/Texture.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/stb_image.h"
  "${CMAKE_CURRENT_LIST_DIR}/Renderable.h"
  "${CMAKE_CURRENT_LIST_DIR}/Renderable.cpp"
)

target_sources(
Kodi-Engine PUBLIC
  ${GraphicsFiles}
)

source_group("Core\\Graphics"   FILES   ${GraphicsFiles})
