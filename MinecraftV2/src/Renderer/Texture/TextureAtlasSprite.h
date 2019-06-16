#pragma once

#include <string>
#include <glm/vec2.hpp>

#include "Image/RawImage.h"

class AtlasTexture;

class TextureAtlasSprite final
{
	friend class AtlasTexture;
public:
	TextureAtlasSprite(const std::string& name);
	~TextureAtlasSprite();

	void loadSprite();

	bool isLinked() const;
	int getWidth() const;
	int getHeight() const;
	glm::ivec2 getOrigin() const;

	RawImage& getImage() const;
	const unsigned char* getBitmap() const;

protected:
	void linkAtlas(int x, int y, int originX, int originY);

private:
	bool mLinked = false;
	glm::ivec2 mOrigin;
	glm::vec2 mMinUv;
	glm::vec2 mMaxUv;

	std::string mName;
	RawImage* mImage = nullptr;
};
