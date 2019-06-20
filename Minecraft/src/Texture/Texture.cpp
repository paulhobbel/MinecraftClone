#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "Texture.h"


void Texture::Create(const std::string& file)
{
	// Load image file
	stbi_set_flip_vertically_on_load(true);
	int width, height, bpp;
	auto data = stbi_load(file.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

	if (data == 0)
	{
		std::cout << "[ERROR/Texture] Failed to load [ " << file << " ], are the resources there?" << std::endl;
		return;
	}

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
