#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Engine.h"



int main() {
    Engine engine("Hejsan");
    engine.init();

    engine.loop();

    return 0;
}