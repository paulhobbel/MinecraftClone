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
}

//Mesh mesh;
Model model;

ChunkRenderer::ChunkRenderer()
{
	ChunkMesh mesh;
	
	mesh.AddFace(frontFace, {
		0, 1,
		1, 1,
		1, 0,
		0, 0
	}, { 0, 0, 0 }, { 0, 0, 0 });
	mesh.AddFace(frontFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { 1, 0, 0 });
	mesh.AddFace(frontFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { -1, 0, 0 });

	mesh.AddFace(topFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { -1, 0, 0 });
	mesh.AddFace(topFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { 0, 0, 0 });
	mesh.AddFace(topFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { 1, 0, 0 });

	mesh.AddFace(rightFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { 1, 0, 0 });
	mesh.AddFace(leftFace, { 0, 1, 2, 2, 3, 0 }, { 0, 0, 0 }, { -1, 0, 0 });

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

void ChunkRenderer::Add(const ChunkMesh& mesh)
{
	m_chunks.push_back(mesh);
}

void ChunkRenderer::Render(Camera& camera)
{
	//model.AddData();
	camera.LoadProjectionMatrix();

	if (m_chunks.empty())
	{
		return;
	}

	camera.LoadViewMatrix();

	//glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glColor3f(0, 0, 0);

	ChunkShader shader;
	shader.UseProgram();

	Texture texture("res/textures/dirt.png");
	texture.Bind();

	// Bind textures

	for (auto& mesh : m_chunks)
	{
		model.AddData(mesh.GetMesh());
		model.BindVAO();

		glDrawElements(GL_TRIANGLES, model.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	//m_chunks.clear();
}
