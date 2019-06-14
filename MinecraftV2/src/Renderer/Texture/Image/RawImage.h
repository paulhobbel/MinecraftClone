#pragma once

#include <string>

#include "ImageSizeInfo.h"

class RawImage
{
public:
	static RawImage* allocImage(int width, int height);
	static RawImage* loadImage(std::string& fileName);
	
	RawImage();
	RawImage(ImageSizeInfo info);
	~RawImage();

	void alloc();
	void blit(RawImage& other, int x, int y) const;

	int getWidth() const;
	int getHeight() const;
	const uint32_t* getBitmap() const;
	ImageSizeInfo getInfo() const;
private:
	ImageSizeInfo mInfo;
	uint32_t* mData;
};
