#pragma once
#include "Player.h"
#include "Texture.h"

#define NUM_TEX		 2

enum {
	TEXTURE_COS,
	TEXTURE_
};

enum Color
{
	Red,
	Green,
	Blue,
	Yellow,
	White,
	Black,
	Magenta,
	Lime
};

class Data
{
public:
	Data(void);
	~Data(void);
	void GetSize(int img, int *w, int *h);
	int GetID(int img);
	bool Load();
	void SetColor(Color color);
private:
	float ColorTable[3][8];
	bool LoadImage(int img, char *filename, int type = GL_RGBA);
	Texture textures[NUM_TEX];
};