cmake_minimum_required(VERSION 3.9)
project(Renderer)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARIES glfw3 dl Xrandr Xinerama Xxf86vm Xcursor X11 pthread assimp IrrXML z)

include_directories(Nchine/include)
link_directories(lib)

#SET(CMAKE_CXX_FLAGS_RELEASE  "-O3")

add_executable(Renderer main.cpp include/glad/glad.c Engine.cpp Engine.h Nchine/Resources/ShaderProgram.cpp Nchine/Resources/ShaderProgram.h Nchine/Renderer/Renderer.cpp Nchine/Renderer/Renderer.h Nchine/Resources/Geometry.cpp Nchine/Resources/Geometry.h Nchine/Resources/Material.cpp Nchine/Resources/Material.h Nchine/Resources/Texture2D.cpp Nchine/Resources/Texture2D.h Nchine/Nchine.h Nchine/Scene/SceneGraph.cpp Nchine/Scene/SceneGraph.h Nchine/Scene/SceneNode.cpp Nchine/Scene/SceneNode.h Nchine/Renderer/RenderCommand.h Nchine/Renderer/RenderTarget.cpp Nchine/Renderer/RenderTarget.h Nchine/Resources/ResourceCache.h Nchine/Resources/ResourceLibrary.cpp Nchine/Resources/ResourceLibrary.h Nchine/Renderer/GLContext.cpp Nchine/Renderer/GLContext.h Nchine/Camera/Camera.cpp Nchine/Camera/Camera.h Nchine/Renderer/UniformBuffer.cpp Nchine/Renderer/UniformBuffer.h Nchine/Renderer/UBData.h Nchine/Resources/TestResources/TestCube.h Nchine/Utilities/overloaded.h Nchine/Resources/ModelLoader.cpp Nchine/Resources/ModelLoader.h Nchine/Resources/Mesh.cpp Nchine/Resources/Mesh.h Nchine/Resources/TextureLoader.cpp Nchine/Resources/TextureLoader.h Nchine/Resources/BinaryFileLoader.cpp Nchine/Resources/BinaryFileLoader.h Nchine/Resources/BaseFactory.h Nchine/Resources/TextureFactory.cpp Nchine/Resources/TextureFactory.h Nchine/Resources/TextureStore.cpp Nchine/Resources/TextureStore.h Nchine/Resources/BinaryLoader.h Nchine/Utilities/locked_queue.h)
target_link_libraries(Renderer ${LIBRARIES})