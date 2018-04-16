FILE(GLOB BufferFiles

  "${CMAKE_CURRENT_LIST_DIR}/Buffer.h"
  "${CMAKE_CURRENT_LIST_DIR}/Buffer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/ElementBuffer.h"
  "${CMAKE_CURRENT_LIST_DIR}/ElementBuffer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/VertexArray.h"
  "${CMAKE_CURRENT_LIST_DIR}/VertexArray.cpp"

)

target_sources(
Kodi-Engine PUBLIC
  ${BufferFiles}
)

source_group("Core\\Graphics\\Buffers"   FILES   ${BufferFiles})
