#ifndef EBO_CLASS_H
#define EBO_CLASS_H
#include <GLAD/include/glad/glad.h>
class ebo
{
public:
	GLuint ID;
public:
	ebo(const GLuint* indiciess, GLsizeiptr size);
	void bind();
	void unbind();
	void destroy();
};

#endif // !EBO_CLASS_H
