#include "BlockFace.h"
#include <utility>

BlockFace::BlockFace(std::vector<GLfloat> vertices, GLfloat light) : mVertices(std::move(vertices)), mLight(light)
{
}

std::vector<GLfloat> BlockFace::getVertices()
{
	return mVertices;
}

TextureAtlasSprite& BlockFace::getSprite()
{
	return *mSprite;
}

GLfloat BlockFace::getLight()
{
	return mLight;
}

void BlockFace::setSprite(std::shared_ptr<TextureAtlasSprite> sprite)
{
	mSprite = sprite;
}
