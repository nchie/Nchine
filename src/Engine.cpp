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
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_forward_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_forward_callback);
    glfwSetCursorPosCallback(m_window, mouse_forward_callback);

    glfwSetWindowUserPointer(m_window, this);

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
        double current_frame_time = glfwGetTime();
        m_delta_time             = current_frame_time - m_time_last_frame;
        m_time_last_frame        = current_frame_time;

        // input
        // -----
        processInput();

        m_renderer->run();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Engine::processInput()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

    float camera_speed = 2.5 * m_delta_time;
    auto& camera = m_renderer->get_camera();
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move_forward(camera_speed);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move_backward(camera_speed);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move_left(camera_speed);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move_right(camera_speed);

    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
        std::cout << "Time for last frame: " << m_delta_time << " ms. (" << 1/m_delta_time << " fps)" << std::endl;
}

void Engine::mouse_button_callback(int button, int action, int mods)
{
    std::cout << "Time for last frame: " << m_delta_time << " ms. (" << 1/m_delta_time << " fps)" << std::endl;
}

void Engine::mouse_callback(double xpos, double ypos) {
    if (m_lastX == 0 && m_lastY == 0)
    {
        m_lastX = xpos;
        m_lastY = ypos;
    }

    float sensitivity = 0.1f;

    double x_offset = (xpos - m_lastX) * sensitivity;
    double y_offset = (m_lastY - ypos) * sensitivity;

    std::cout << "x offset:" << x_offset << std::endl;
    std::cout << "y offset:" << y_offset << std::endl;

    auto& camera = m_renderer->get_camera();
    camera.adjust_yaw_pitch(x_offset, y_offset);

    m_lastX = xpos;
    m_lastY = ypos;
}

void framebuffer_size_forward_callback(GLFWwindow* window, int width, int height)
{
    auto* engine = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_button_forward_callback(GLFWwindow* window, int button, int action, int mods) { reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->mouse_button_callback(button, action, mods);}
void mouse_forward_callback(GLFWwindow* window, double xpos, double ypos) { reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->mouse_callback(xpos, ypos);}