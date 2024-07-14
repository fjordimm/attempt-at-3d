
add_executable(AttemptAt3DExec
	src/AttemptAt3D/Program.cpp
	src/AttemptAt3D/WindowHandling/Window.cpp
)

target_include_directories(AttemptAt3DExec PUBLIC include)

find_package(OpenGL REQUIRED)
target_link_libraries(AttemptAt3DExec OpenGL::GL)
target_link_libraries(AttemptAt3DExec OpenGL::GLU)
target_include_directories(AttemptAt3DExec PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../glew/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../glew/lib/glew32s.lib)

target_compile_options(AttemptAt3DExec PRIVATE -DUNICODE)
