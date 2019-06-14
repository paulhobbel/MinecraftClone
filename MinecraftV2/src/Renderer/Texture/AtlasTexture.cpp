#include "AtlasTexture.h"
#include <vector>
#include <iostream>

#define STB_RECT_PACK_IMPLEMENTATION
#include <stb_rect_pack.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "Image/RawImage.h"

int round_up_po2(int n) {
	int x = 1;
	while (x < n) x <<= 1;
	return x;
}

TextureAtlasSprite& AtlasTexture::registerSprite(std::string& location)
{
	if (mRegisteredSprites.find({ location }) != mRegisteredSprites.end())
		return *mRegisteredSprites.at(location);

	auto registeredSprite = new TextureAtlasSprite(location);

	mRegisteredSprites.emplace(location, registeredSprite);

	return *registeredSprite;
}

void AtlasTexture::compile()
{
	//std::vector<RawImage*> images;
	AtlasImpl atlas;
	
	for(auto& entry : mRegisteredSprites)
	{
		std::string location = "res/textures/" + entry.first + ".png";
		const auto image = RawImage::loadImage(location);

		if (image != nullptr)
			atlas.addImage(image);
	}

	while (atlas.getStatus() != AtlasImpl::ATLAS_IMPL_DONE)
	{
		atlas.packImages();
	}

	atlas.compile();
}

AtlasTexture::AtlasImpl::AtlasImpl()
{
	mNodes = new stbrp_node[4096];
	mRects = new stbrp_rect[MAX_SPRITES];
}

AtlasTexture::AtlasImpl::~AtlasImpl()
{
	delete[] mNodes;
	delete[] mRects;
	//delete[] mAtlasImage;
}

AtlasTexture::AtlasImpl::AtlasStatus AtlasTexture::AtlasImpl::getStatus() const
{
	return mStatus;
}

void AtlasTexture::AtlasImpl::addImage(RawImage* image)
{
	mImages.emplace_back(image);
}

bool AtlasTexture::AtlasImpl::packImages()
{
	for (size_t i = 0; i < mImages.size(); i++)
	{
		const auto image = mImages[i];

		mRects[i].id = i;
		mRects[i].w = image->getWidth();
		mRects[i].h = image->getHeight();

		if (mRects[i].w > mAtlasInfo.width) mAtlasInfo.width = round_up_po2(mRects[i].w);
		if (mRects[i].h > mAtlasInfo.height) mAtlasInfo.height = round_up_po2(mRects[i].h);
	}

	stbrp_context ctx;
	stbrp_init_target(&ctx, mAtlasInfo.width, mAtlasInfo.height, mNodes, 4096);
	stbrp_pack_rects(&ctx, mRects, mImages.size());

	for (size_t i = 0; i < mImages.size(); i++)
	{
		if (!mRects[i].was_packed)
		{
			if(mAtlasInfo.height < mAtlasInfo.width)
			{
				mAtlasInfo.height = mAtlasInfo.width;
			} else
			{
				mAtlasInfo.width *= 2;
			}

			return false;
		}
	}

	mStatus = ATLAS_IMPL_DONE;
	return true;
}

bool AtlasTexture::AtlasImpl::compile()
{
	if (mStatus != ATLAS_IMPL_DONE)
		return false;

	mAtlasImage = new RawImage(mAtlasInfo);

	for(size_t i = 0; i < mImages.size(); i++)
	{
		mAtlasImage->blit(*mImages[mRects[i].id], mRects[i].x, mRects[i].y);
	}

	stbi_write_png("test.png", mAtlasImage->getWidth(), mAtlasImage->getHeight(), 4, mAtlasImage->getBitmap(), 0);
}
