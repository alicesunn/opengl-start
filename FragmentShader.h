#pragma once

class FragmentShader {
public:
	FragmentShader() {
		// create shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // attach source code
		glCompileShader(fragmentShader);

		checkErrors();
	}

	unsigned int getShader() const { return fragmentShader; };

private:
	unsigned int fragmentShader;

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
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR: Fragment shader compilation failed. Log:" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
};