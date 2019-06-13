#pragma once

class GLResource
{
public:
	
	virtual ~GLResource() = default;
	virtual void create();
	virtual void dispose();
};