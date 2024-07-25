#pragma once

#ifndef DATA_H
#define DATA_H

#include <glad/glad.h>

#include "stb_image.h"

class Data {
public:
	// generate and configure VBO, VAO, and EBO
	void generateObjects() {
		// generate IDs
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		// bind VAO
		glBindVertexArray(mVAO);

		// VBO
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mRectVertices), mRectVertices, GL_STATIC_DRAW);

		// EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mRectIndices), mRectIndices, GL_STATIC_DRAW);

		// configure position data 
		// params: shader var location, # values in data, type of data, normalize true/false,
		//         stride (distance between start of each set of values), offset
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0); // position var location = 0

		// configure color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// configure texture data
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	unsigned int getVBO() const { return mVBO; }
	unsigned int getVAO() const { return mVAO; }
	unsigned int getEBO() const { return mEBO; }

private:
	// OpenGl state objects
	unsigned int mVBO; // vertex buffer object
	unsigned int mVAO; // vertex array object
	unsigned int mEBO; // element buffer object

	// test data
	float mTextureCoords[6] = { // for triangle
		0.0f, 0.0f, // lower left
		1.0f, 0.0f, // lower right
		0.5f, 1.0f  // top
	};
	float mTriangleVertices[18] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right (red)
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left (green)
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top (blue)
	};
	float mRectVertices[32] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	unsigned int mRectIndices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
};

#endif