#include <iostream>

#include <stb_image.h>

#include "SimpleTexture.h"


void SimpleTexture::loadFromFileS(const std::string& file)
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

	glBindTexture(GL_TEXTURE_2D, getId());

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(data);
}
