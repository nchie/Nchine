cmake_minimum_required(VERSION 3.9)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARIES glfw3 dl Xrandr Xinerama Xxf86vm Xcursor X11 pthread assimp IrrXML z)

include_directories(Enchine/include)
link_directories(lib)

#SET(CMAKE_CXX_FLAGS_RELEASE  "-O3")

add_executable(Renderer main.cpp include/glad/glad.c Engine.cpp Engine.h Enchine/Resources/ShaderProgram.cpp Enchine/Resources/ShaderProgram.h Enchine/Renderer/Renderer.cpp Enchine/Renderer/Renderer.h Enchine/Resources/Geometry.cpp Enchine/Resources/Geometry.h Enchine/Resources/Material.cpp Enchine/Resources/Material.h Enchine/Resources/Texture2D.cpp Enchine/Resources/Texture2D.h Enchine/Enchine.h Enchine/Scene/SceneGraph.cpp Enchine/Scene/SceneGraph.h Enchine/Scene/SceneNode.cpp Enchine/Scene/SceneNode.h Enchine/Renderer/RenderCommand.h Enchine/Renderer/RenderTarget.cpp Enchine/Renderer/RenderTarget.h Enchine/Resources/ResourceCache.h Enchine/Resources/ResourceLibrary.cpp Enchine/Resources/ResourceLibrary.h Enchine/Renderer/GLContext.cpp Enchine/Renderer/GLContext.h Enchine/Camera/Camera.cpp Enchine/Camera/Camera.h Enchine/Renderer/UniformBuffer.cpp Enchine/Renderer/UniformBuffer.h Enchine/Renderer/UBData.h Enchine/Resources/TestResources/TestCube.h Enchine/Utilities/overloaded.h Enchine/Resources/ModelLoader.cpp Enchine/Resources/ModelLoader.h Enchine/Resources/Mesh.cpp Enchine/Resources/Mesh.h Enchine/Resources/TextureLoader.cpp Enchine/Resources/TextureLoader.h Enchine/Resources/BinaryFileLoader.cpp Enchine/Resources/BinaryFileLoader.h Enchine/Resources/BaseFactory.h Enchine/Resources/TextureFactory.cpp Enchine/Resources/TextureFactory.h Enchine/Resources/TextureStore.cpp Enchine/Resources/TextureStore.h Enchine/Resources/BinaryLoader.h Enchine/Utilities/locked_queue.h)
target_link_libraries(Renderer ${LIBRARIES})