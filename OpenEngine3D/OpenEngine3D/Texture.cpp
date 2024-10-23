#include "Texture.h"
#include "stb_image.h"
 
Texture::Texture(const std::string& fileName) 
{
	unsigned int width, height, numComponents;
	char* imageData =  stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTextImage2D();

	stbi_image_free(imageData);
}

Texture::~Texture() 
{

}