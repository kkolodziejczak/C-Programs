#pragma once
#pragma comment(lib,"corona")

#include "stdafx.h"
#include "corona.h"


class Texture
{
public:
	Texture(void);
	~Texture(void);
	void GetSize(int *w, int *h);
	int  GetID();
	bool Load(char *filename, int type = GL_RGBA, int wraps = GL_REPEAT, int wrapt = GL_REPEAT,
		int magf = GL_LINEAR, int minf = GL_LINEAR, bool mipmap = true);

private:
	int width;
	int height;
	GLuint id;
};

