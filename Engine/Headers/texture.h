#pragma once
#include <iostream>
#include <STB/stb_image.h>
#include <GLAD/include/glad/glad.h>
#include <OPENGL/glfw-3.4/include/GLFW/glfw3.h>

class texture
{
public:
	unsigned int ID;
	texture(const char* fileName);
	void useTexture();
};