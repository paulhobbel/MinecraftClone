#pragma once

#include <string>
#include <glad/glad.h>

#include "GLResource.h"

class Shader : public GLResource
{
public:
	Shader(std::string& vertFile, std::string& fragFile);
	Shader(const Shader& other);
	~Shader() override;

	void create() override;
	void dispose() override;
private:
	GLint mId;
};