#include "TextureAtlasSprite.h"

TextureAtlasSprite::TextureAtlasSprite(const std::string& name) : mOrigin(0, 0), mMinUv(0, 0), mMaxUv(0, 0), mName(name)
{
}

TextureAtlasSprite::~TextureAtlasSprite()
{
	delete mImage;
}

void TextureAtlasSprite::loadSprite()
{
	mImage = RawImage::loadImage("res/textures/" + mName + ".png");
}

bool TextureAtlasSprite::isLinked() const
{
	return mLinked;
}

int TextureAtlasSprite::getWidth() const
{
	if (mImage == nullptr)
		return 0;
	return mImage->getWidth();
}

int TextureAtlasSprite::getHeight() const
{
	if (mImage == nullptr)
		return 0;
	return mImage->getHeight();
}

glm::ivec2 TextureAtlasSprite::getOrigin() const
{
	return mOrigin;
}

RawImage& TextureAtlasSprite::getImage() const
{
	return *mImage;
}

const unsigned char* TextureAtlasSprite::getBitmap() const
{
	if (mImage == nullptr)
		return nullptr;

	return mImage->getBitmap();
}

void TextureAtlasSprite::linkAtlas(int x, int y, int originX, int originY)
{
	mOrigin = glm::ivec2(originX, originY);
	mMinUv = glm::vec2(float(originX) / float(x), float(originY) / float(y));
	mMaxUv = glm::vec2(float(originX + getWidth()) / float(x), float(originY + getHeight()) / float(y));
	mLinked = true;
}
