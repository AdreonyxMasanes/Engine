#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include <GLAD/include/glad/glad.h>
class vbo
{
public:
	GLuint ID;
public:
	vbo(const GLfloat* verticies, GLsizeiptr size);
	void bind();
	void unbind();
	void destroy();
};

#endif // !VBO_CLASS_H
