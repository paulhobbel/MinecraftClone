﻿#include "BaseTexture.h"

BaseTexture::~BaseTexture()
{
	BaseTexture::dispose(); 
}

GLuint BaseTexture::getId()
{
	if(mId == 0)
		glGenTextures(1, &mId);

	return mId;
}

void BaseTexture::dispose()
{
	if (mId != 0)
		glDeleteTextures(1, &mId);
}
