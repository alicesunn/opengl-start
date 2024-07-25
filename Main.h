#pragma once

class Shader;
class Data;

class Main {
public:
	bool initialize();
	void renderLoop();
	void shutdown();

private:
	GLFWwindow* mWindow;
	Shader* mShader;
	Data* triangle;

	void processInput(GLFWwindow* mWindow);
};