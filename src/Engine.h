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



public:
    Engine(std::string title, int window_width=800, int window_height = 600);
    virtual ~Engine();

    void init();
    void loop();

private:



};


void processInput(GLFWwindow *window);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);