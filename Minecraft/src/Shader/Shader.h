#pragma once

#include <string>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const std::string& vertFile, const std::string& fragFile);
	~Shader();

	void Create();

	void UseProgram();

protected:
	GLuint m_id = 0;
	virtual void GetUniforms() = 0;

private:
	std::string m_vertFile;
	std::string m_fragFile;

	GLuint Compile(const GLchar* source, GLenum type);
	GLuint Link(GLuint vertShaderId, GLuint fragShaderId);
};