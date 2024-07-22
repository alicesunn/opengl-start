#pragma once

class VertexShader {
public:
	VertexShader() {
		// generate buffer ID
		glGenBuffers(1, &mVBO);

		// bind buffer so calls on GL_ARRAY_BUFFER will configure VBO
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		// copy vertex data into buffer memory 
		// STATIC_DRAW = data is set once and used many times
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// create shader
		mVertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(mVertexShader, 1, &vertexShaderSource, NULL); // attach source code
		glCompileShader(mVertexShader);

		checkErrors();
	}

	// bind VAO and configure with member VBO and vertices data
	void configureVAO(unsigned int mVAO) const {
		mVAO = mVAO;
		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	unsigned int getShader() const { return mVertexShader; };
	unsigned int getVBO() const { return mVBO; };

private:
	unsigned int mVBO; // vertex buffer object ID
	unsigned int mVertexShader;
	unsigned int mVAO;

	// GLSL source code of basic vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// 3 vertices with xyz coordinates (test data)
	float vertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
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