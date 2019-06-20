#pragma once

#include <string>
#include <glm/matrix.hpp>

#include "Shader.h"

class ChunkShader : public Shader
{
public:
	ChunkShader();

	void loadProjectionViewMatrix(const glm::mat4& matrix);

private:
	void getUniforms() override;

	GLint m_projViewMatrixLocation = -1;
};