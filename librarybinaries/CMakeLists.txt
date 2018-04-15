
target_link_libraries(Kodi-Engine opengl32)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/GLEW/glew32s.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/GLFW/glfw3.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/SDL2/SDL2.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/SFML/sfml-graphics.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/SFML/sfml-system.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/SFML/sfml-window.lib)


target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/boost/libboost_regex-vc141-mt-gd-x64-1_66.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/boost/libboost_filesystem-vc141-mt-gd-x64-1_66.lib)
target_link_libraries(Kodi-Engine ${CMAKE_CURRENT_LIST_DIR}/boost/libboost_system-vc141-mt-gd-x64-1_66.lib)
