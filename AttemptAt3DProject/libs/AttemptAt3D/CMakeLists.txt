
configure_file(CMakeConfig.h.in CMakeConfig.h)

add_executable(AttemptAt3DExec
	"src/AttemptAt3D/Program.cpp"
	"src/AttemptAt3D/Head.cpp"
	"src/AttemptAt3D/WorldState.cpp"
	"src/AttemptAt3D/(Debug)/_logging.cpp"
	"src/AttemptAt3D/(FileLoading)/FileLoading.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderProgram.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/InSpace.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/ThreeDShape.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/(Abstract)/HasNormals.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/Flat.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderPrograms/Smooth.cpp"
	"src/AttemptAt3D/(Drawing)/(Shaders)/ShaderProgramManager.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/MeshData.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/Mesh.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/MeshSample.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/InvertedPyramid.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/Cube.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/MeshSamples/Sphere.cpp"
	"src/AttemptAt3D/(Drawing)/(Meshes)/MeshManager.cpp"
	"src/AttemptAt3D/(Util)/(Tran)/Tran.cpp"
	"src/AttemptAt3D/(Util)/(Tran)/Vec.cpp"
	"src/AttemptAt3D/(Form)/Form.cpp"
	"src/AttemptAt3D/(Form)/Forms/Camera.cpp"
	"src/AttemptAt3D/(Form)/Forms/Sun.cpp"
	"src/AttemptAt3D/(Form)/PhysicForm.cpp"
	"src/AttemptAt3D/(PtrForGlfw)/PtrForGlfw.cpp"
	"src/AttemptAt3D/(InputManager)/InputManager.cpp"
	"src/AttemptAt3D/(Util)/(Color)/Color.cpp"
)

target_include_directories(AttemptAt3DExec PUBLIC include)
target_include_directories(AttemptAt3DExec PUBLIC "${PROJECT_BINARY_DIR}/libs/AttemptAt3D")

target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../GLFW/lib/ninja-libglfw3.a)

target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/include)
target_link_libraries(AttemptAt3DExec ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/lib/ninja-libglew32.a)

target_include_directories(AttemptAt3DExec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../GLM/include)

find_package(OpenGL REQUIRED)
target_link_libraries(AttemptAt3DExec OpenGL::GL)

target_compile_options(AttemptAt3DExec PRIVATE -O2)
