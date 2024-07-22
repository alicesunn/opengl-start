#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Main.h"
#include "VertexShader.h"
#include "FragmentShader.h"

// callback for adjusting the viewport on window resize
static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main()
{
    Main m = Main();
    if (m.initialize()) {
        m.renderLoop();
        m.shutdown();
    }
    return 0;
}

bool Main::initialize() {
    // configure GLFW and inform it which OpenGL version is being used (3.3)
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window object
    window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    // init GLAD, which manages function pointers for OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // set location and size of rendering window (how to display stuff with respect to window)
    // where x,y start from the lower left corner
    glViewport(0, 0, 800, 600); // x, y, width, height

    // register any callbacks after window creation but before render loop:
    // call framebuffer_size_callback on every resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    initializeShaderObject(VertexShader().getShader(), FragmentShader().getShader());

    return true;
}

void Main::shutdown() {
    // clean up
    glfwTerminate();
}

void Main::renderLoop() {
    // initiate render loop
    while (!glfwWindowShouldClose(window)) {
        // handle input
        processInput(window);

        // rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // glClearColor sets a color value which glClear uses
        glClear(GL_COLOR_BUFFER_BIT);         // to clear the specified buffer (aka color buffer)

        // check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Main::processInput(GLFWwindow* window) {
    // esc closes the window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}