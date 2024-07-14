
add_executable(AttemptAt3DExec
	src/AttemptAt3D/Program.cpp
	src/AttemptAt3D/WindowHandling/Window.cpp
)

target_include_directories(AttemptAt3DExec PUBLIC include)

target_compile_options(AttemptAt3DExec PRIVATE -DUNICODE)
