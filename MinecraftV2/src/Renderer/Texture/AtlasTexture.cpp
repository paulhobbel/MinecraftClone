#include "AtlasTexture.h"
#include <iostream>

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb_rect_pack.h>

#include "../../Util/Stopwatch.h"

std::shared_ptr<TextureAtlasSprite> AtlasTexture::registerSprite(const std::string& location)
{
	if (mSprites.find(location) != mSprites.end())
		return mSprites.at(location);

	auto sprite = std::make_shared<TextureAtlasSprite>(location);

	mSprites.emplace(location, sprite);

	return sprite;
}

std::weak_ptr<TextureAtlasSprite> AtlasTexture::getSprite(std::string& location)
{
	if (mSprites.find(location) == mSprites.end())
		return std::weak_ptr<TextureAtlasSprite>();

	return mSprites.at(location);
}

void AtlasTexture::stitch()
{
	Stopwatch stopwatch;
	
	for(auto& entry : mSprites)
	{
		entry.second->loadSprite();
	}
	std::cout << "[DEBUG/AtlasTexture] Loaded " << mSprites.size() << " sprites, took " << stopwatch.reset() << "ms" << std::endl;

	std::map<int, std::weak_ptr<TextureAtlasSprite>> rectToSpriteMap;
	packSprites(rectToSpriteMap);
	allocAtlas();
	linkSprites(rectToSpriteMap);

	std::cout << "[INFO/AtlasTexture] Stitched atlas texture to dimension [ " << mContext.width << "x" << mContext.height << " ], took " << stopwatch.reset() << "ms" << std::endl;
}

void AtlasTexture::upload()
{
	Stopwatch stopwatch;

	//RawImage* atlasImage = RawImage::allocImage(mContext.width, mContext.height);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, getId());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mContext.width, mContext.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

	for(auto& entry : mSprites)
	{
		const auto sprite = entry.second;
		const auto origin = sprite->getOrigin();
		glTexSubImage2D(GL_TEXTURE_2D, 0, origin.x, origin.y, sprite->getWidth(), sprite->getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, sprite->getBitmap());
		//atlasImage->blit(sprite->getImage(), sprite->getOrigin().x, sprite->getOrigin().y);
		//sprite->unloadSprite();
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

	//delete atlasImage;

	const auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "[Error/AtlasTexture] An error occured while uploading atlas: " << error << std::endl;
	}
	std::cout << "[DEBUG/AtlasTexture] Uploaded atlas, took " << stopwatch.reset() << "ms" << std::endl;
}

void AtlasTexture::packSprites(std::map<int, std::weak_ptr<TextureAtlasSprite>>& rectToSpriteMap)
{
	mContext.numRects = static_cast<int>(mSprites.size());
	mContext.nodes = new stbrp_node[4096];
	mContext.rects = new stbrp_rect[mContext.numRects];

	auto itr = mSprites.begin();
	for (auto i = 0; itr != mSprites.end(); ++itr, i++)
	{
		auto& rect = mContext.rects[i];

		rect.id = i;
		rect.w = itr->second->getWidth();
		rect.h = itr->second->getHeight();
		rectToSpriteMap.emplace(i, itr->second);

		if (rect.w > mContext.width) mContext.width = rect.w;
		if (rect.h > mContext.height) mContext.height = rect.h;
	}
}

void AtlasTexture::allocAtlas()
{
	if(mContext.numRects == 0)
	{
		std::cout << "[ERROR/AtlasTexture] Failed to allocate atlas, no sprites to allocate!" << std::endl;
		return;
	}

	while(!mContext.allocated)
	{
		stbrp_init_target(&mContext.context, mContext.width, mContext.height, mContext.nodes, 4096);

		if (!stbrp_pack_rects(&mContext.context, mContext.rects, mContext.numRects))
		{
			if (mContext.height < mContext.width)
			{
				mContext.height = mContext.width;
			}
			else
			{
				mContext.width *= 2;
			}

			continue;
		}

		mContext.allocated = true;
	}

	delete[] mContext.nodes;
}

void AtlasTexture::linkSprites(std::map<int, std::weak_ptr<TextureAtlasSprite>> rectToSpriteMap) const
{
	for(int i = 0; i < mContext.numRects; i++)
	{
		auto& rect = mContext.rects[i];
		auto sprite = rectToSpriteMap.at(i).lock();

		sprite->linkAtlas(mContext.width, mContext.height, rect.x, rect.y);
	}

	delete[] mContext.rects;
}