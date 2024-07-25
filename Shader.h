#pragma once

#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	// reads and builds shader from vertex/fragment source code
	Shader(const char* vertexPath, const char* fragmentPath) {
		std::string vertexString, fragmentString;
		std::ifstream vertexFile, fragmentFile;

		// ensure ifstreams can throw exceptions
		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		// retrieve code from files
		try {
			// open files
			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);

			// read files into streams
			std::stringstream vertexStream, fragmentStream;
			vertexStream << vertexFile.rdbuf();
			fragmentStream << fragmentFile.rdbuf();

			// close files
			vertexFile.close();
			fragmentFile.close();

			// convert streams to strings
			vertexString = vertexStream.str();
			fragmentString = fragmentStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "(constructor, Shader.h) ERROR: Shader file read failed." << std::endl;
		}

		// prepare to compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		const char* vertexCode = vertexString.c_str();
		const char* fragmentCode = fragmentString.c_str();

		// compile vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);

		// check for compile errors
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "(constructor, Shader.h) ERROR: Vertex shader compilation failed. Logs:" << std::endl;
			std::cout << infoLog << std::endl;
		}

		// compile fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentCode, NULL);
		glCompileShader(fragment);

		// check for compile errors
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "(constructor, Shader.h) ERROR: Fragment shader compilation failed. Logs:" << std::endl;
			std::cout << infoLog << std::endl;
		}

		// after successful compilation, create the shader program
		mProgram = glCreateProgram();
		glAttachShader(mProgram, vertex);
		glAttachShader(mProgram, fragment);
		glLinkProgram(mProgram);

		// check for linking errors
		glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
			std::cout << "(constructor, Shader.h) ERROR: Shader program linking failed. Logs:" << std::endl;
			std::cout << infoLog << std::endl;
		}

		// clean up shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// activate shader
	void use() {
		glUseProgram(mProgram);
	}

	unsigned int getProgram() const { return mProgram; }

	// query and set a uniform boolean variable
	void setBool(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(mProgram, name.c_str()), (int) value);
	}

	// query and set a uniform int variable
	void setInt(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
	}

	// query and set a uniform float variable
	void setFloat(const std::string& name, float value) const {
		glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
	}

private:
	unsigned int mProgram; // shader program id

};

#endif