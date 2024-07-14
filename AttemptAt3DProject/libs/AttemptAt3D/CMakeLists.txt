
add_executable(AttemptAt3DExec
	src/AttemptAt3D/Program.cpp
)

target_include_directories(AttemptAt3DExec PUBLIC include)

find_package(OpenGL REQUIRED)
target_link_libraries(AttemptAt3DExec OpenGL::GL)
target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/lib/glfw3.lib)
target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/lib/glew32s.lib)
