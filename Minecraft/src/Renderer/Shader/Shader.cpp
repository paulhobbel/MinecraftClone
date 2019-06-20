#include <iostream>
#include <stdexcept>

#include "Shader.h"
#include "../../Util/FileUtil.h"

Shader::Shader(const std::string& vertFile, const std::string& fragFile)
	: m_vertFile(vertFile), m_fragFile(fragFile)
{
}

Shader::~Shader()
{
	if(m_id)
		glDeleteProgram(m_id);
}

void Shader::create()
{
	if (m_id)
		return;

	try
	{
		std::string vertSource, fragSource;
		FileUtil::getContentsAsString("res/shaders/" + m_vertFile + ".vert", vertSource);
		FileUtil::getContentsAsString("res/shaders/" + m_fragFile + ".frag", fragSource);

		// Compile Shader
		auto vertShaderId = compile(vertSource.c_str(), GL_VERTEX_SHADER);
		auto fragShaderId = compile(fragSource.c_str(), GL_FRAGMENT_SHADER);

		if (vertShaderId && fragShaderId)
		{
			m_id = link(vertShaderId, fragShaderId);

			glDeleteShader(vertShaderId);
			glDeleteShader(fragShaderId);
		}

		getUniforms();
	}
	catch (std::runtime_error e)
	{
		std::cout << "[ERROR/Shader] Failed to create shader, reason: " << e.what() << std::endl;
	}
}

void Shader::useProgram()
{
	glUseProgram(m_id);
}

GLuint Shader::compile(const GLchar* source, GLenum type)
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

GLuint Shader::link(GLuint vertShaderId, GLuint fragShaderId)
{
	GLuint program = glCreateProgram();

	glAttachShader(program, vertShaderId);
	glAttachShader(program, fragShaderId);

	glLinkProgram(program);

	return program;
}
