cmake_minimum_required(VERSION 3.9)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARIES glfw3 dl Xrandr Xinerama Xxf86vm Xcursor X11 pthread assimp)

include_directories(include)
link_directories(lib)

#SET(CMAKE_CXX_FLAGS_RELEASE  "-O3")

add_executable(Renderer src/main.cpp glad.c src/Engine.cpp src/Engine.h src/Enchine/Materials/ShaderProgram.cpp src/Enchine/Materials/ShaderProgram.h src/Enchine/Renderer/Renderer.cpp src/Enchine/Renderer/Renderer.h src/Enchine/Meshes/Mesh.cpp src/Enchine/Meshes/Mesh.h src/Enchine/Meshes/VertexAttributes.h src/Enchine/Materials/Material.cpp src/Enchine/Materials/Material.h src/Enchine/Materials/Texture2D.cpp src/Enchine/Materials/Texture2D.h src/Enchine/Materials/UniformValue.h src/Enchine/Enchine.h src/Enchine/Materials/UniformValueSampler.h src/Enchine/Scene/SceneGraph.cpp src/Enchine/Scene/SceneGraph.h src/Enchine/Scene/SceneNode.cpp src/Enchine/Scene/SceneNode.h src/Enchine/Renderer/RenderCommand.h src/Enchine/Renderer/RenderTarget.cpp src/Enchine/Renderer/RenderTarget.h src/Enchine/Resources/ResourceCache.h src/Enchine/Resources/ResourceLoader.cpp src/Enchine/Resources/ResourceLoader.h src/Enchine/Resources/ResourceLibrary.cpp src/Enchine/Resources/ResourceLibrary.h src/Enchine/Renderer/GLContext.cpp src/Enchine/Renderer/GLContext.h src/Enchine/Camera/Camera.cpp src/Enchine/Camera/Camera.h src/Enchine/Renderer/UniformBuffer.cpp src/Enchine/Renderer/UniformBuffer.h src/Enchine/Renderer/UBData.h src/Enchine/Resources/TestResources/TestCube.h src/Enchine/Utilities/overloaded.h src/Enchine/Resources/ModelLoader.cpp src/Enchine/Resources/ModelLoader.h)
target_link_libraries(Renderer ${LIBRARIES})