#pragma once
#include <vector>
#include <glad/glad.h>
#include "../../Renderer/Texture/TextureAtlasSprite.h"
#include <memory>

enum BlockFaceEnum : int
{
	UP = 0,
	DOWN = 1,
	NORTH = 2,
	EAST = 3,
	SOUTH = 4,
	WEST = 5,

	NUM_FACES
};

class BlockFace
{
public:
	BlockFace() = default;
	BlockFace(std::vector<GLfloat> vertices, GLfloat light);

	std::vector<GLfloat> getVertices();
	TextureAtlasSprite& getSprite();
	GLfloat getLight();
	void setSprite(std::shared_ptr<TextureAtlasSprite> sprite);

private:
	std::vector<GLfloat> mVertices;
	std::shared_ptr<TextureAtlasSprite> mSprite;
	GLfloat mLight;
};
