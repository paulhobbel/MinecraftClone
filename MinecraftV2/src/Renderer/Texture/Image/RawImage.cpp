#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "RawImage.h"

RawImage::RawImage() : mInfo({0, 0, 0}), mData(nullptr)
{
}

RawImage::RawImage(ImageSizeInfo info) : mInfo(info), mData(nullptr)
{
	// QUICKFIX:
	mInfo.bpp = 4;

	alloc();
}

RawImage* RawImage::allocImage(int width, int height)
{
	const auto image = new RawImage();

	image->mData = static_cast<unsigned char*>(calloc(4, width * height));
	image->mInfo = { width, height, 4 };

	return image;
}

RawImage* RawImage::loadImage(const std::string fileName)
{
	auto image = new RawImage();

	//stbi_set_flip_vertically_on_load(true);
	image->mData = stbi_load(fileName.c_str(), &image->mInfo.width, &image->mInfo.height, &image->mInfo.bpp, STBI_rgb_alpha);

	if (image->mData == nullptr)
	{
		std::cout << "[ERROR/RawImage] Failed to load [ " << fileName << " ]" << std::endl;
	}

	return image;
}

RawImage::~RawImage()
{
	delete mData;
}

void RawImage::alloc()
{
	mData = static_cast<unsigned char*>(calloc(mInfo.bpp, mInfo.width * mInfo.height));
	if (mData == nullptr)
		std::cout << "Unable to allocate memory!" << std::endl;
}

void RawImage::blit(RawImage& other, int x, int y) const
{
	for(int i = 0; i < other.getHeight(); i++)
	{
		int dy = y + i;
		if (dy < 0 || dy >= getHeight())
			continue;

		for(int j = 0; j < other.getWidth(); j++)
		{
			int dx = x + j;
			if (dx < 0 || dx >= getWidth())
				continue;

			memcpy(
				mData + (mInfo.bpp * (dy * getWidth() + dx)),
				other.mData + (mInfo.bpp * (i * other.getWidth() + j)),
				mInfo.bpp);
		}
	}
}

int RawImage::getWidth() const
{
	return mInfo.width;
}

int RawImage::getHeight() const
{
	return mInfo.height;
}

const unsigned char* RawImage::getBitmap() const
{
	return mData;
}

ImageSizeInfo RawImage::getInfo() const
{
	return mInfo;
}
