#pragma once

#include <map>
#include <string>
#include <stb_rect_pack.h>

#include "BaseTexture.h"
#include "TextureAtlasSprite.h"


#define MAX_SPRITES 256

class AtlasTexture final : public BaseTexture
{
public:
	TextureAtlasSprite& registerSprite(std::string& location);
	TextureAtlasSprite& getSprite(std::string& location);
	void compile();
	void reset();
private:
	struct AtlasContext
	{
		AtlasContext(int numRects);
		
		stbrp_context context{};
		stbrp_node* nodes;
		stbrp_rect* rects;

		int num_rects;

		bool allocated = false;
		int width = 0;
		int height = 0;
	};

	void packSprites(AtlasContext& context, std::map<int, TextureAtlasSprite*>& rectToSpriteMap);
	void allocAtlas(AtlasContext& context);
	void linkSprites(AtlasContext& context, std::map<int, TextureAtlasSprite*> rectToSpriteMap);
	void stitchAtlas(AtlasContext& context);

	RawImage* mAtlasImage = nullptr;
	std::map<std::string, TextureAtlasSprite*> mSprites;
};
