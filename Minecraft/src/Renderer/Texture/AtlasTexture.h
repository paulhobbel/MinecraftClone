#pragma once

#include <map>
#include <string>
#include <memory>
#include <stb_rect_pack.h>

#include "BaseTexture.h"
#include "TextureAtlasSprite.h"

class AtlasTexture final : public BaseTexture
{
public:
	std::shared_ptr<TextureAtlasSprite> registerSprite(const std::string& location);
	std::weak_ptr<TextureAtlasSprite> getSprite(std::string& location);

	void stitch();
	void upload() override;

private:
	struct AtlasContext
	{
		stbrp_context context{};
		stbrp_node* nodes;
		stbrp_rect* rects;

		int numRects;

		bool allocated = false;
		int width = 0;
		int height = 0;
	};

	void packSprites(std::map<int, std::weak_ptr<TextureAtlasSprite>>& rectToSpriteMap);
	void allocAtlas();
	void linkSprites(std::map<int, std::weak_ptr<TextureAtlasSprite>> rectToSpriteMap) const;

	AtlasContext mContext{};
	std::map<std::string, std::shared_ptr<TextureAtlasSprite>> mSprites;
};
