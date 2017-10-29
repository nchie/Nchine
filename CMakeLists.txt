cmake_minimum_required(VERSION 3.9)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARIES glfw3 dl Xrandr Xinerama Xxf86vm Xcursor X11 pthread)

include_directories(include)

add_executable(Renderer src/main.cpp glad.c src/Engine.cpp src/Engine.h src/Enchine/Materials/ShaderProgram.cpp src/Enchine/Materials/ShaderProgram.h src/Enchine/Renderer/Renderer.cpp src/Enchine/Renderer/Renderer.h src/Enchine/Meshes/Mesh.cpp src/Enchine/Meshes/Mesh.h src/Enchine/Meshes/VertexAttributes.h src/Enchine/Materials/Material.cpp src/Enchine/Materials/Material.h src/Enchine/Materials/Texture2D.cpp src/Enchine/Materials/Texture2D.h src/Enchine/Materials/UniformValue.h src/Enchine/Enchine.h src/Enchine/Materials/UniformValueSampler.h src/Enchine/Scene/SceneGraph.cpp src/Enchine/Scene/SceneGraph.h src/Enchine/Scene/Scene.cpp src/Enchine/Scene/Scene.h src/Enchine/Renderer/RenderCommand.h src/Enchine/Renderer/RenderTarget.cpp src/Enchine/Renderer/RenderTarget.h src/Enchine/Resources/Cache.h src/Enchine/Resources/Resource.h src/Enchine/Resources/ResourceLoader.cpp src/Enchine/Resources/ResourceLoader.h src/Enchine/Resources/ResourceLibrary.cpp src/Enchine/Resources/ResourceLibrary.h)
target_link_libraries(Renderer ${LIBRARIES})