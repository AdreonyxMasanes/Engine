#include "vao.h"

vao::vao()
{
	glGenVertexArrays(1, &ID);
}

void vao::LinkAttrib(vbo &vbo, int layout, int numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.unbind();
}

void vao::bind()
{
	glBindVertexArray(ID);
}

void vao::unbind()
{
	glBindVertexArray(0);
}

void vao::destroy()
{
	glDeleteBuffers(1, &ID);
}
