#pragma once

#include <string>
#include <glad/glad.h>

class Shader
{
public:
	Shader(const std::string& vertFile, const std::string& fragFile);
	~Shader();

	void create();

	void useProgram();

protected:
	GLuint m_id = 0;
	virtual void getUniforms() = 0;

private:
	std::string m_vertFile;
	std::string m_fragFile;

	GLuint compile(const GLchar* source, GLenum type);
	static GLuint link(GLuint vertShaderId, GLuint fragShaderId);
};