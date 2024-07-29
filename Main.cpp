#include "Main.h"

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
    mTexture1 = new Texture("container.jpg", true, true, false);
    mTexture2 = new Texture("awesomeface.png", true, true, true);

    // tell uniform variables which texture unit to sample
    mShader->use();
    mShader->setInt("texture1", 0);
    mShader->setInt("texture2", 1);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // sets a color value which glClear uses to clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // the specified buffers

        // bind container/happy face texture to rect
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTexture1->getTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, mTexture2->getTexture());

        // activate shader
        mShader->use();

        // update transform matrices every frame
        updateMatrices(false, true, true);

        drawThings();

        // reset binding
        //glBindVertexArray(0);

        // swap buffers and poll IO events
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

void Main::drawThings() {
    // bind VAO to active
    glBindVertexArray(mShape->getVAO());

    // draw 10 cubes
    for (int i = 0; i < 10; i++) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
        model = glm::rotate(model, glm::radians((float) (20.0f * i)), glm::vec3(1.0f, 0.3f, 0.5f));
        mShader->setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Main::processInput(GLFWwindow* mWindow) {
    // esc closes the window
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(mWindow, true);
}