#pragma once

class VertexShader {
public:
	VertexShader() {
		mVertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(mVertexShader, 1, &mVertexShaderSource, NULL); // attach source code
		glCompileShader(mVertexShader);

		checkErrors();
	}

	void configureVBO() {
		// generate buffer ID
		glGenBuffers(1, &mVBO);

		// bind buffer so calls on GL_ARRAY_BUFFER will configure VBO
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		// copy vertex data into buffer memory 
		// STATIC_DRAW = data is set once and used many times
		glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);
	}

	// bind VAO and configure with member VBO and vertices data
	void configureVAO(unsigned int& VAO) {
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mVertices), mVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		VAO = mVAO;
	}

	// bind EBO and copy rectangle indices into buffer
	void configureEBO(unsigned int& EBO) {
		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mIndices), mIndices, GL_STATIC_DRAW);
		EBO = mEBO;
	}

	unsigned int getShader() const { return mVertexShader; };
	unsigned int getVBO() const { return mVBO; };
	unsigned int getVAO() const { return mVAO; }

private:
	unsigned int mVertexShader;
	unsigned int mVBO; // vertex buffer object
	unsigned int mVAO; // vertex array object
	unsigned int mEBO; // element buffer object

	// GLSL source code of basic vertex shader
	const char* mVertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// test data
	//float vertices[9] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//};
	float mVertices[12] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int mIndices[6] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	// check for compile-time errors
	void checkErrors() const {
		int success;
		char infoLog[512];
		glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(mVertexShader, 512, NULL, infoLog);
			std::cout << "ERROR: Vertex shader compilation failed. Log:" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
};