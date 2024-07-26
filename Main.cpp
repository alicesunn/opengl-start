#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Main.h"
#include "Shader.h"
#include "Data.h"
#include "Texture.h"

// callback for adjusting the viewport on window resize
static void framebuffer_size_callback(GLFWwindow* mWindow, int width, int height) {
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
    bool success = setupWindow();
    if (!success)
        return false;

    // register callbacks after window creation but before render loop:
    // call framebuffer_size_callback on every resize
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

    // initialize shader
    mShader = new Shader("VertexShader.txt", "FragmentShader.txt");

    // set up VBO, VAO, EBO
    mShape = new Data();
    mShape->generateObjects();

    // set up textures
    mTexture1 = new Texture("container.jpg", true, false, false);
    mTexture2 = new Texture("awesomeface.png", false, true, true);
    mShader->use();
    mShader->setInt("texture1", 0);
    mShader->setInt("texture2", 1);
    
    // vector/matrix experimentation

    return true;
}

void Main::shutdown() {
    delete mTexture1;
    delete mTexture2;
    delete mShape;
    delete mShader;
    glfwTerminate();
}

void Main::renderLoop() {
    // initiate render loop
    while (!glfwWindowShouldClose(mWindow)) {
        // handle input
        processInput(mWindow);

        // set background to greenish color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // glClearColor sets a color value which glClear uses
        glClear(GL_COLOR_BUFFER_BIT);         // to clear the specified buffer (aka color buffer)

        // activate shader
        mShader->use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture1->getTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mTexture2->getTexture());

        // experiment: move rect to bottom right and apply rotation over time
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(mShader->getProgram(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glBindVertexArray(mShape->getVAO());

        // draw triangle
        //glDrawArrays(GL_TRIANGLES, 0, 3); // type, VAO starting index, number vertices to draw

        // draw rectangle
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mShape->getEBO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // reset binding
        //glBindVertexArray(0);

        // swap buffers and poll IO events
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void Main::processInput(GLFWwindow* mWindow) {
    // esc closes the window
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
}