#include "vbo.h"

vbo::vbo(const GLfloat* verticies, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
}

void vbo::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void vbo::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo::destroy()
{
	glDeleteBuffers(1, &ID);
}
