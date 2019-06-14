#pragma once

#include <glad/glad.h>
#include "../GLResource.h"

class BaseTexture : public GLResource
{
public:
	virtual ~BaseTexture();

	GLuint getId();

	void dispose() override;
protected:
	GLuint mId = 0;
};
