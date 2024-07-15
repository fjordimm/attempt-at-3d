
add_executable(AttemptAt3DExec
	src/AttemptAt3D/Program.cpp
	src/AttemptAt3D/FileLoading/FileLoading.cpp
	src/AttemptAt3D/Debug/Debug_logging.cpp
)

configure_file(CMakeConfig.h.in CMakeConfig.h)

target_include_directories(AttemptAt3DExec PUBLIC include)
target_include_directories(AttemptAt3DExec PUBLIC "${PROJECT_BINARY_DIR}/libs/AttemptAt3D")

find_package(OpenGL REQUIRED)
target_link_libraries(AttemptAt3DExec OpenGL::GL)
target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/lib/glfw3.lib)
target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/lib/glew32s.lib)
target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLM/include)
