#ifndef VAO_CLASS_H
#define VAO_CLASS_H
#include <GLAD/include/glad/glad.h>
#include "vbo.h"
class vao
{
public:
	GLuint ID;
public:
	vao();
	void LinkAttrib(vbo &vbo, int layout, int numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void bind();
	void unbind();
	void destroy();

};

#endif // !VAO_CLASS_H
