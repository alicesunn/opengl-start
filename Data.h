#pragma once

#ifndef DATA_H
#define DATA_H

class Data {
public:
	// generate VBO and buffer the vertex data
	void configureVBO() {
		// generate buffer ID
		glGenBuffers(1, &mVBO);

		// bind buffer so calls on GL_ARRAY_BUFFER will configure VBO
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		// copy vertex data into buffer memory 
		// STATIC_DRAW = data is set once and used many times
		glBufferData(GL_ARRAY_BUFFER, sizeof(mTriangleVertices), mTriangleVertices, GL_STATIC_DRAW);
	}

	// bind VAO and configure with member VBO and vertices data
	// (make sure to run configureVBO first)
	void configureVAO() {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mTriangleVertices), mTriangleVertices, GL_STATIC_DRAW);

		// position data 
		// params: shader var location, # values in color data, type of color data, normalize,
		//         stride (distance between start of each set of values), offset
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0); // position var location = 0

		// color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	// bind EBO and copy rectangle indices into buffer
	void configureEBO() {
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mRectIndices), mRectIndices, GL_STATIC_DRAW);
	}

	unsigned int getVBO() const { return mVBO; }
	unsigned int getVAO() const { return mVAO; }
	unsigned int getEBO() const { return mEBO; }

private:
	unsigned int mVBO; // vertex buffer object
	unsigned int mVAO; // vertex array object
	unsigned int mEBO; // element buffer object

	// test data
	float mTriangleVertices[18] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right (red)
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // bottom left (green)
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f  // top (blue)
	};
	float mRectVertices[12] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int mRectIndices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
};

#endif