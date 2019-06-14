#pragma once

#include <map>
#include <string>
#include <vector>
#include <stb_rect_pack.h>

#include "BaseTexture.h"
#include "TextureAtlasSprite.h"


#define MAX_SPRITES 256

class AtlasTexture final : public BaseTexture
{
public:
	TextureAtlasSprite& registerSprite(std::string& location);
	void compile();
	void reset();
private:

	class AtlasImpl
	{
	public:
		enum AtlasStatus
		{
			ATLAS_IMPL_PENDING,
			ATLAS_IMPL_DONE,
			ATLAS_IMPL_SMALL
		};

		AtlasImpl();
		~AtlasImpl();

		AtlasStatus getStatus() const;

		void addImage(RawImage* image);
		bool packImages();
		bool compile();

	private:
		AtlasStatus mStatus = ATLAS_IMPL_PENDING;

		std::vector<RawImage*> mImages;

		ImageSizeInfo mAtlasInfo;
		RawImage* mAtlasImage = nullptr;
		stbrp_node* mNodes;
		stbrp_rect* mRects;
	};


	std::map<std::string, TextureAtlasSprite*> mRegisteredSprites;
};
