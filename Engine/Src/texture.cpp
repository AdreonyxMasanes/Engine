#include "texture.h"

texture::texture(const char* name)
{
	// STBI LOADS IMAGES OPPOSITE OF V
	stbi_set_flip_vertically_on_load(true);


	int twidth, theight, numColChannels;
	unsigned char* data = stbi_load(name, &twidth, &theight, &numColChannels, 0);

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, twidth, theight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "FAILED TO LOAD IMAGE TEX" << std::endl;
	}
	stbi_image_free(data);
}

void texture::useTexture()
{
	glBindTexture(GL_TEXTURE_2D, ID);
}