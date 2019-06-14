#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

#include "RawImage.h"

RawImage::RawImage() : mInfo({0, 0, 0}), mData(nullptr)
{
}

RawImage::RawImage(ImageSizeInfo info) : mInfo(info), mData(nullptr)
{
	alloc();
}

RawImage* RawImage::allocImage(int width, int height)
{
	const auto image = new RawImage();

	image->mData = static_cast<uint32_t*>(calloc(4, width * height));

	return image;
}

RawImage* RawImage::loadImage(std::string& fileName)
{
	auto image = new RawImage();

	//stbi_set_flip_vertically_on_load(true);
	void* data = stbi_load(fileName.c_str(), &image->mInfo.width, &image->mInfo.height, &image->mInfo.bpp, STBI_rgb_alpha);

	image->mData = (uint32_t*) data;

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
	mData = static_cast<uint32_t*>(calloc(4, mInfo.width * mInfo.height));
	if (mData == nullptr)
		std::cout << "Unable to allocate memory!" << std::endl;
}

void RawImage::blit(RawImage& other, int x, int y) const
{
	for(int i = 0; i < other.getHeight(); i++)
	{
		int dy = y + i;
		if (dy < 0 || dy >= getHeight()) continue;

		for(int j = 0; j < other.getWidth(); j++)
		{
			int dx = x + j;
			if (dx < 0 || dx >= getWidth()) continue;
			mData[dx + dy * getWidth()] = other.mData[i * other.getWidth() + j];
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

const uint32_t* RawImage::getBitmap() const
{
	return mData;
}

ImageSizeInfo RawImage::getInfo() const
{
	return mInfo;
}
