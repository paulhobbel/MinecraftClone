#include <iostream>

#include "Shader.h"
#include "../Util/FileUtilities.h"

Shader::Shader(const std::string& vertFile, const std::string& fragFile)
{
	auto vertSource = FileUtilities::GetContents("res/shaders/" + vertFile + ".vert");
	auto fragSource = FileUtilities::GetContents("res/shaders/" + fragFile + ".frag");

	// Compile Shader
	auto vertShaderId = Compile(vertSource.c_str(), GL_VERTEX_SHADER);
	auto fragShaderId = Compile(fragSource.c_str(), GL_FRAGMENT_SHADER);

	if (vertShaderId && fragShaderId)
	{
		m_id = Link(vertShaderId, fragShaderId);

		glDeleteShader(vertShaderId);
		glDeleteShader(fragShaderId);
	}

}

Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::UseProgram()
{
	glUseProgram(m_id);
}

GLuint Shader::Compile(const GLchar* source, GLenum type)
{
	GLuint shaderId = glCreateShader(type);

	glShaderSource(shaderId, 1, &source, nullptr);
	glCompileShader(shaderId);

	GLint success = 0;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		std::cout << "[ERROR/Shader] Failed to compile shader: " << shaderId << std::endl;
		return 0;
	}

	return shaderId;
}

GLuint Shader::Link(GLuint vertShaderId, GLuint fragShaderId)
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vertShaderId);
	glAttachShader(program, fragShaderId);

	glLinkProgram(program);

	return program;
}
