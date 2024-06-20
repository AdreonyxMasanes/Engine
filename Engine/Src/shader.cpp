#include "shader.h"
shader::shader()
{

}

shader::shader(const char* vertexFilePath, const char* fragmentFilePath)
{
	ID = glCreateProgram();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	
	std::string vertexCode;
	std::string fragmentCode;
	
	std::ifstream vertexFile;
	std::ifstream fragmentFile;

	try
	{
		// open files
		vertexFile.open(vertexFilePath);
		fragmentFile.open(fragmentFilePath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexFile.rdbuf();
		fShaderStream << fragmentFile.rdbuf();
		// close file handlers
		vertexFile.close();
		fragmentFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}

	const char* vertexCharCode = vertexCode.c_str();
	const char* fragmentCharCode = fragmentCode.c_str();

	glShaderSource(vertexShader, 1, &vertexCharCode, nullptr);
	glShaderSource(fragmentShader, 1, &fragmentCharCode, nullptr);

	glCompileShader(vertexShader);
	checkShaderStatus(vertexShader, success, infoLog);

	glCompileShader(fragmentShader);
	checkShaderStatus(fragmentShader, success, infoLog);

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	checkLinkStatus(ID, success, infoLog);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void shader::use()
{
	glUseProgram(ID);
}

void shader::destroy()
{
	glDeleteProgram(ID);
}

void shader::checkShaderStatus(GLuint shaderID, int& status, char* infoLog)
{
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		std::cerr << "FAILED TO COMPILE SHADER\n" << infoLog << std::endl;
	}
}

void shader::checkLinkStatus(GLuint programID, int& status, char* infoLog)
{
	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if (!success)
	{
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		std::cerr << "FAILED TO LINK PROGRAM\n" << infoLog << std::endl;
	}
}
