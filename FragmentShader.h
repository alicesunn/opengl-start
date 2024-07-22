#pragma once

class FragmentShader {
public:
	FragmentShader() {
		// create shader
		mFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(mFragmentShader, 1, &fragmentShaderSource, NULL); // attach source code
		glCompileShader(mFragmentShader);

		checkErrors();
	}

	unsigned int getShader() const { return mFragmentShader; }

private:
	unsigned int mFragmentShader = 0;

	// GLSL source code of basic fragment shader
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	// check for compile-time errors
	void checkErrors() const {
		int success;
		char infoLog[512];
		glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(mFragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR: Fragment shader compilation failed. Log:" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
};