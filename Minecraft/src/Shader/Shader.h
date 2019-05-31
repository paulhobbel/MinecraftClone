#pragma once

#include <string>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const std::string& vertFile, const std::string& fragFile);
	~Shader();

	void UseProgram();

protected:
	GLuint m_id;
	virtual void GetUniforms() = 0;

private:
	GLuint Compile(const GLchar* source, GLenum type);
	GLuint Link(GLuint vertShaderId, GLuint fragShaderId);
};