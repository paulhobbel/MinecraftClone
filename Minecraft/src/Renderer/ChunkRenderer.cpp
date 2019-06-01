#include <iostream>

#include <glm/vec3.hpp>

#include "../World/Chunk/ChunkMesh.h"
#include "ChunkRenderer.h"
#include "../Camera.h"

#include "../Model.h"
#include "../Shader/Shader.h"
#include "../Texture/Texture.h"

namespace
{
	const std::array<GLfloat, 12> frontFace
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1
	};

	const std::array<GLfloat, 12> backFace
	{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0
	};

	const std::array<GLfloat, 12> leftFace
	{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0
	};

	const std::array<GLfloat, 12> rightFace
	{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1
	};

	const std::array<GLfloat, 12> topFace
	{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0
	};

	const std::array<GLfloat, 12> bottomFace
	{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	constexpr GLfloat LIGHT_TOP = 1.0f;
	constexpr GLfloat LIGHT_X = 0.8f;
	constexpr GLfloat LIGHT_Z = 0.6f;
	constexpr GLfloat LIGHT_BOT = 0.4f;
}

Texture dirtTexture;

ChunkRenderer::ChunkRenderer()
{
	ChunkMesh mesh;
	
	mesh.AddFace(frontFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, LIGHT_Z);
	mesh.AddFace(frontFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { 1, 0, 0 }, LIGHT_Z);
	mesh.AddFace(frontFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { -1, 0, 0 }, LIGHT_Z);

	mesh.AddFace(topFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { -1, 0, 0 }, LIGHT_TOP);
	mesh.AddFace(topFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, LIGHT_TOP);
	mesh.AddFace(topFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { 1, 0, 0 }, LIGHT_TOP);

	mesh.AddFace(rightFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { 1, 0, 0 }, LIGHT_X);
	mesh.AddFace(leftFace, { 0, 1, 1, 1, 1, 0, 0, 0 }, { 0, 0, 0 }, { -1, 0, 0 }, LIGHT_X);

	m_chunks.push_back(mesh);

	
	/*mesh.vertices = {
		0, 0, 0,
		1, 0, 0,
		0, 1, 0,
		
		1, 0, 0,
		1, 1, 0,
		0, 1, 0
	};

	mesh.indices = {
		0, 1, 2, 3, 4, 5
	};*/

	//model.AddData(mesh);
}

void ChunkRenderer::Init()
{
	m_shader.Create();

	dirtTexture.Create("res/textures/dirt.png");

	for (auto& mesh : m_chunks)
	{
		mesh.BufferMesh();
	}
}

void ChunkRenderer::Add(const ChunkMesh& mesh)
{
	m_chunks.push_back(mesh);
}

void ChunkRenderer::Render(Camera& camera)
{
	//model.AddData();
	//camera.LoadProjectionMatrix();

	if (m_chunks.empty())
	{
		return;
	}

	//camera.LoadViewMatrix();

	//glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);

	m_shader.UseProgram();

	m_shader.LoadProjectionViewMatrix(camera.getProjectionViewMatrix());

	dirtTexture.Bind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (auto& mesh : m_chunks)
	{
		auto& model = mesh.GetModel();
		model.BindVAO();

		glDrawElements(GL_TRIANGLES, model.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	GLenum lastError = glGetError();

	if(lastError != GL_NO_ERROR)
		std::cout << "[INFO/ChunkRenderer] Last GL Error: " << lastError << std::endl;

	//m_chunks.clear();
}
