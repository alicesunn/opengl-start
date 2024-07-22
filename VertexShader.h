#pragma once

class VertexShader {
public:
	VertexShader() {
		// generate buffer ID
		glGenBuffers(1, &VBO);

		// bind buffer so calls on GL_ARRAY_BUFFER will configure VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// copy vertex data into buffer memory 
		// STATIC_DRAW = data is set once and used many times
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// create shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // attach source code
		glCompileShader(vertexShader);

		checkErrors();
	}

	unsigned int getShader() const { return vertexShader; };

private:
	unsigned int VBO; // vertex buffer object ID
	unsigned int vertexShader;

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
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR: Vertex shader compilation failed. Log:" << std::endl;
			std::cout << infoLog << std::endl;
		}
	}
};