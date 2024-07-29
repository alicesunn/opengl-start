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
			std::cout << "(constructor, Shader.h) "
				<< "ERROR: Vertex shader compilation failed.Logs : " << std::endl;
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
			std::cout << "(constructor, Shader.h) "
				<< "ERROR: Fragment shader compilation failed.Logs : " << std::endl;
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
			std::cout << "(constructor, Shader.h) "
				<< "ERROR: Shader program linking failed.Logs : " << std::endl;
			std::cout << infoLog << std::endl;
		}

		// clean up shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// activate shader
	void use() const {
		glUseProgram(mProgram);
	}

	unsigned int getProgram() const { return mProgram; }

	// helper functions that query and set a ___ shader variable
    // ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(mProgram, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(mProgram, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(mProgram, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
	}
	void setVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(mProgram, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

private:
	unsigned int mProgram; // shader program id
};

#endif