#pragma once

#include <string>

#include "ImageSizeInfo.h"

class RawImage
{
public:
	static RawImage* allocImage(int width, int height);
	static RawImage* loadImage(const std::string fileName);
	
	RawImage();
	RawImage(ImageSizeInfo info);
	~RawImage();

	void alloc();
	void blit(RawImage& other, int x, int y) const;

	int getWidth() const;
	int getHeight() const;
	const unsigned char* getBitmap() const;
	ImageSizeInfo getInfo() const;
private:
	ImageSizeInfo mInfo;
	unsigned char* mData;
};
