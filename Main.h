#pragma once

class Shader;
class Data;
class Texture;

class Main {
public:
	bool initialize();
	void renderLoop();
	void shutdown();

private:
	GLFWwindow* mWindow;
	Shader* mShader;
	Data* mShape;
	Texture* mTexture1;
	Texture* mTexture2;

	void processInput(GLFWwindow* mWindow);
};