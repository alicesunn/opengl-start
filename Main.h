#pragma once

class Main {
public:
	bool initialize();
	void renderLoop();
	void shutdown();

private:
	unsigned int shaderProgram;

	GLFWwindow* window;

	void processInput(GLFWwindow* window);

	// link vertex/fragment shaders to shader program object and activate it
	void initializeShaderObject(unsigned int vertexShader, unsigned int fragmentShader) {
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		// check for linking errors
		int success;
		char infoLog[512];
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR: Shader program linking failed. Log:" << std::endl;
			std::cout << infoLog << std::endl;
		}

		// activate
		glUseProgram(shaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
};