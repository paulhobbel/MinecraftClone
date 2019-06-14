#pragma once
#include <string>

#include "Image/RawImage.h"

class TextureAtlasSprite
{
public:
	TextureAtlasSprite(std::string& name);

private:
	std::string mName;
};
