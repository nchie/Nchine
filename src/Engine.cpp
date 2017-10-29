//
// Created by aejt on 10/22/17.
//

#include "Engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <exception>


Engine::Engine(std::string title, int window_width, int window_height) :  m_window_width(window_width),
                                                                          m_window_height(window_height),
                                                                          m_window_title(title)
{
}

Engine::~Engine() {
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    m_renderer.release(); // If renderer stays alive longer than glfwTerminate, render will try to deallocate GL objects after glfw have terminated = SIGSEGV!
    glfwTerminate();
}

void Engine::init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    m_window = glfwCreateWindow(m_window_width, m_window_height, m_window_title.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
        throw std::exception(); // Failed to create GLFW window
    }

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::exception();  //Failed to initialize GLAD
    }

    m_renderer = std::make_unique<Enchine::Renderer>();
}

void Engine::loop() {
    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        // input
        // -----
        processInput(m_window);

        m_renderer->run();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
