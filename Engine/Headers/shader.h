#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H
#include <GLAD/include/glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
class shader
{
public:
	GLuint ID;
	shader();
	shader(const char* vertexFilePath, const char* fragmentFilePath);
	void use();
	void destroy();
private:
    char infoLog[512];
    int success;
private:
    void checkShaderStatus(GLuint shaderID, int& status, char* infoLog);
    void checkLinkStatus(GLuint programID, int& status, char* infoLog);
};

#endif // !SHADER_CLASS_H
