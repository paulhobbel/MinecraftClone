#include "Shader.h"

Shader::Shader(std::string& vertFile, std::string& fragFile)
{
	
}

Shader::Shader(const Shader& other)
{
	mId = other.mId;
}

Shader::~Shader()
{
	dispose();
}


void Shader::dispose()
{
	if (mId)
		glDeleteProgram(mId);
}


