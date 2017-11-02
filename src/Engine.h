//
// Created by aejt on 10/22/17.
//

#pragma once

#include <string>
#include <memory>

#include "Enchine/Renderer/Renderer.h"
#include "Enchine/Renderer/Renderer.h"

class GLFWwindow;


class Engine {
private:
    GLFWwindow* m_window;

    // settings
    int m_window_width = 800;
    int m_window_height = 600;
    std::string m_window_title;

    std::unique_ptr<Enchine::Renderer> m_renderer;


    // TODO: Remove these?
    double m_time_last_frame;
    double m_delta_time;

    double m_lastX = 0;
    double m_lastY = 0;


public:
    Engine(std::string title, int window_width=800, int window_height = 600);
    virtual ~Engine();

    void init();
    void loop();

    void mouse_button_callback(int button, int action, int mods);
    void mouse_callback(double xpos, double ypos);

private:
    void processInput();



};


// GLFW callback-forwarding
void mouse_button_forward_callback(GLFWwindow* window, int button, int action, int mods);
void mouse_forward_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_forward_callback(GLFWwindow* window, int width, int height);