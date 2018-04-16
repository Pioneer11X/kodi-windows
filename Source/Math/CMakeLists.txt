

FILE(GLOB MathFiles
  "${CMAKE_CURRENT_LIST_DIR}/vec2.h"
)

target_sources(
Kodi-Engine PUBLIC
  ${MathFiles}
)

source_group("Math"   FILES   ${MathFiles})
