#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"



int main() {
    Engine engine("OpenGL", 800, 600);
    engine.init();

    engine.loop();

    return 0;
}