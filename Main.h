#pragma once

class Shader;
class Data;
class Texture;

class Main {
public:
	bool initialize();
	void renderLoop();
	void shutdown();

private:
	GLFWwindow* mWindow;
	Shader* mShader;
	Data* mShape;
	Texture* mTexture1;
	Texture* mTexture2;

	void processInput(GLFWwindow* mWindow);

	// initialization helper functions
	
	// configure GLFW, create window, and configure GLAD
	bool setupWindow() {
		// configure GLFW and inform it which OpenGL version is being used (3.3)
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// create window object
		mWindow = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
		if (!mWindow) {
			std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(mWindow);

		// init GLAD, which manages function pointers for OpenGL
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// set location and size of rendering window (how to display stuff with respect to window)
		// where x,y start from the lower left corner
		glViewport(0, 0, 800, 600); // x, y, width, height

		return true;
	}
};