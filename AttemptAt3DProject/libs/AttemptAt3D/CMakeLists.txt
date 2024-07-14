
add_executable(AttemptAt3DExec
	src/AttemptAt3D/Program.cpp
	src/AttemptAt3D/WindowHandling/Window.cpp
)

target_include_directories(AttemptAt3DExec PUBLIC include)

find_package(OpenGL REQUIRED)
target_link_libraries(AttemptAt3DExec OpenGL::GL)
target_link_libraries(AttemptAt3DExec OpenGL::GLU)
# find_package(GLEW REQUIRED)
# target_link_libraries(AttemptAt3DExec GLEW::GLEW)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../glew/lib/glew32.lib)

target_compile_options(AttemptAt3DExec PRIVATE -DUNICODE)
