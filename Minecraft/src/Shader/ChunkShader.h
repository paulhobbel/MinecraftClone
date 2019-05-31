#pragma once

#include <string>
#include <glm/matrix.hpp>

#include "Shader.h"

class ChunkShader : public Shader
{
public:
	ChunkShader();

	void LoadProjectionViewMatrix(const glm::mat4& matrix);

private:
	void GetUniforms() override;

	GLuint m_projViewMatrixLocation;
};