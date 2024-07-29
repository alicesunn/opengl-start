#pragma once

#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Data.h"
#include "Texture.h"

class Main {
public:
	bool initialize();
	void renderLoop();
	void shutdown();

private:
	float mViewWidth = 800.0f;
	float mViewHeight = 600.0f;

	GLFWwindow* mWindow = nullptr;
	Shader* mShader = nullptr;
	Data* mShape = nullptr;
	Texture* mTexture1 = nullptr;
	Texture* mTexture2 = nullptr;

	void processInput(GLFWwindow* mWindow);
	void drawThings();

	// temp data
	glm::vec3 cubePositions[10] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// update and send the transform matrices to the shader
	void updateMatrices(bool setModel = true, bool setView = true, bool setProj = true) {
		// create matrices
		if (setModel) {
			glm::mat4 model = glm::mat4(1.0f);
			// rotate over time
			model = glm::rotate(model, (float) glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			mShader->setMat4("model", model);
		}

		if (setView) {
			glm::mat4 view = glm::mat4(1.0f);
			// move camera slightly towards viewer (aka move scene slightly backwards)
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			mShader->setMat4("view", view);
		}

		if (setProj) {
			glm::mat4 projection = glm::mat4(1.0f);
			// apply perspective with fov = 45 deg
			projection = glm::perspective(glm::radians(45.0f), mViewWidth / mViewHeight, 0.1f, 100.0f);
			mShader->setMat4("projection", projection);
		}
	}

	// configure GLFW, create window, and configure GLAD
	bool setupWindow() {
		// configure GLFW and inform it which OpenGL version is being used (3.3)
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// create window object
		mWindow = glfwCreateWindow((int) mViewWidth, (int) mViewHeight, "LearnOpenGL", NULL, NULL);
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

		// enable depth testing (far vertices dont override near vertices when drawn out of order)
		glEnable(GL_DEPTH_TEST);

		// set location and size of rendering window (how to display stuff with respect to window)
		// where x,y start from the lower left corner
		glViewport(0, 0, mViewWidth, mViewHeight); // x, y, width, height

		return true;
	}
};

#endif