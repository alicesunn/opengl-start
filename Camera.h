#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
	Camera(float startX = 0.0f, float startY = 0.0f, float startZ = 3.0f) {
		// init starting position and view direction/axes
		mPos = glm::vec3(startX, startY, startZ);
		glm::vec3 dir = glm::normalize(mPos - glm::vec3(0.0f, 0.0f, 0.0f));
		mRight = glm::normalize(glm::cross(WORLD_UP, dir));
		mUp = glm::cross(dir, mRight); // ensure mDir and mRight are normalized
		mFront = glm::vec3(0.0f, 0.0f, -1.0f);

		// look at matrix
		updateView();
	}

	// move the camera with WASD
	void moveCamera(GLFWwindow* window, float deltaTime) {
		// consistent camera move speed
		float speed = 2.5f * deltaTime;

		// update right vector
		mRight = glm::normalize(glm::cross(mFront, WORLD_UP));

		// move forward/backwards by adding/subtracting front direction vector
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) // W
			mPos += speed * mFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) // S
			mPos -= speed * mFront;

		// move sideways by adding/subtracting right vector
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) // A
			mPos -= mRight * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) // D
			mPos += mRight * speed;

		updateView();
	}

	// update view with current position and target
	void updateView() { mView = glm::lookAt(mPos, mPos + mFront, WORLD_UP); }

	glm::mat4 getView() const { return mView; }
	glm::vec3 getPos() const { return mPos; }
	void setPos(float x, float y, float z) { mPos = glm::vec3(x, y, z); }

private:
	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f); // up vector in world space

	glm::mat4 mView; // view matrix (aka LookAt)
	glm::vec3 mPos; // camera pos
	glm::vec3 mRight; // +x axis of camera
	glm::vec3 mUp; // +y axis of camera
	glm::vec3 mFront; // -z axis? (direction where camera is looking)
};

#endif