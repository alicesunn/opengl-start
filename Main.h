#pragma once

class VertexShader;
class FragmentShader;

class Main {
public:
	bool initialize();
	void renderLoop();
	void shutdown();

private:
	unsigned int mShaderProgram;
	unsigned int mVAO; // vertex array object
	unsigned int mEBO; // element buffer object

	GLFWwindow* mWindow;
	VertexShader* mVertexShader;
	FragmentShader* mFragmentShader;

	void processInput(GLFWwindow* mWindow);

	// link vertex/fragment shaders to shader program object and activate it
	void initializeShaderObject(unsigned int mVertexShader, unsigned int mFragmentShader) {
		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, mVertexShader);
		glAttachShader(mShaderProgram, mFragmentShader);
		glLinkProgram(mShaderProgram);

		// check for linking errors
		int success;
		char infoLog[512];
		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR: Shader program linking failed. Log:" << std::endl;
			std::cout << infoLog << std::endl;
		}

		// activate
		glUseProgram(mShaderProgram);

		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);
	}
};