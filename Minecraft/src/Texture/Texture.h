#pragma once

#include <string>
#include <glad/glad.h>

class Texture
{
public:
	Texture() = default;
	Texture(const std::string& file);

	~Texture();

	void Bind();

private:
	GLuint m_id;
};