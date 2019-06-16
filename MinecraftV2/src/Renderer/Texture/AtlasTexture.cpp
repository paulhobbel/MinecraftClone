#include "AtlasTexture.h"
#include <iostream>
#include <string>

using namespace std::string_literals;

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb_rect_pack.h>

#include "Image/RawImage.h"

#include "../../Util/Stopwatch.h"

TextureAtlasSprite& AtlasTexture::registerSprite(std::string& location)
{
	if (mSprites.find(location) != mSprites.end())
		return *mSprites.at(location);

	auto registeredSprite = new TextureAtlasSprite(location);

	mSprites.emplace(location, registeredSprite);

	return *registeredSprite;
}

TextureAtlasSprite& AtlasTexture::getSprite(std::string& location)
{
	auto noexists = TextureAtlasSprite("noexists");

	if (mSprites.find(location) == mSprites.end())
		return noexists;

	return *mSprites.at(location);
}

void AtlasTexture::compile()
{
	Stopwatch stopwatch;
	AtlasContext context(static_cast<int>(mSprites.size()));
	
	for(auto& entry : mSprites)
	{
		entry.second->loadSprite();
	}
	std::cout << "[DEBUG/AtlasTexture] Loaded " << mSprites.size() << " sprites, took " << stopwatch.reset() << "ms" << std::endl;

	std::map<int, TextureAtlasSprite*> rectToSpriteMap;
	packSprites(context, rectToSpriteMap);
	allocAtlas(context);
	linkSprites(context, rectToSpriteMap);
	stitchAtlas(context);
}

AtlasTexture::AtlasContext::AtlasContext(const int numRects)
{
	num_rects = numRects;
	nodes = new stbrp_node[4096];
	rects = new stbrp_rect[numRects];
	
}

void AtlasTexture::packSprites(AtlasContext& context, std::map<int, TextureAtlasSprite*>& rectToSpriteMap)
{
	auto itr = mSprites.begin();
	for (auto i = 0; itr != mSprites.end(); ++itr, i++)
	{
		auto& rect = context.rects[i];

		rect.id = i;
		rect.w = itr->second->getWidth();
		rect.h = itr->second->getHeight();
		rectToSpriteMap.emplace(i, itr->second);

		if (rect.w > context.width) context.width = rect.w;
		if (rect.h > context.height) context.height = rect.h;
	}
}

void AtlasTexture::allocAtlas(AtlasContext& context)
{
	if(context.num_rects == 0)
	{
		std::cout << "[ERROR/AtlasTexture] Failed to allocate atlas, no sprites to allocate!" << std::endl;
		return;
	}

	Stopwatch stopwatch;

	while(!context.allocated)
	{
		stbrp_init_target(&context.context, context.width, context.height, context.nodes, 4096);

		if (!stbrp_pack_rects(&context.context, context.rects, context.num_rects))
		{
			if (context.height < context.width)
			{
				context.height = context.width;
			}
			else
			{
				context.width *= 2;
			}

			continue;
		}

		context.allocated = true;
	}

	mAtlasImage = RawImage::allocImage(context.width, context.height);

	std::cout << "[DEBUG/AtlasTexture] Allocated atlas image with dimension [ " << mAtlasImage->getWidth() << "x" << mAtlasImage->getHeight() << " ], took " << stopwatch.reset() << "ms" << std::endl;
}

void AtlasTexture::linkSprites(AtlasContext& context, std::map<int, TextureAtlasSprite*> rectToSpriteMap)
{
	for(int i = 0; i < context.num_rects; i++)
	{
		auto& rect = context.rects[i];
		rectToSpriteMap.at(i)->linkAtlas(context.width, context.height, rect.x, rect.y);
	}
}

void AtlasTexture::stitchAtlas(AtlasContext& context)
{
	if(mAtlasImage == nullptr)
	{
		std::cout << "[ERROR/AtlasTexture] Unable to stitch sprites! mAtlasImage not allocated, did you not call allocAtlas?" << std::endl;
		return;
	}

	Stopwatch stopwatch;

	for (auto& entry : mSprites)
	{
		mAtlasImage->blit(entry.second->getImage(), entry.second->getOrigin().x, entry.second->getOrigin().y);
	}
	std::cout << "[DEBUG/AtlasTexture] Stitched " << mSprites.size() << " sprites in the atlas texture, took " << stopwatch.reset() << "ms" << std::endl;
}


