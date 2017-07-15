#include "stdafx.h"
#include "Data.h"
#include <fstream>
#include <string>
#include <sstream>

Data::Data(void) {}
Data::~Data(void) {}
int Data::GetID(int img)
{
	return textures[img].GetID();
}
void Data::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w, h);
}
bool Data::LoadImage(int img, char *filename, int type)
{
	int res;
	res = textures[img].Load(filename, type);
	if (!res) return false;

	return true;
}

void Data::SetColor(Color color)
{
	glColor3f(ColorTable[0][color], ColorTable[1][color], ColorTable[2][color]);
};

bool Data::Load()
{
	ColorTable[0][Red] = 255;
	ColorTable[1][Red] = 0;
	ColorTable[2][Red] = 0;
	ColorTable[0][Green] = 0;
	ColorTable[1][Green] = 112;
	ColorTable[2][Green] = 0;
	ColorTable[0][Blue] = 0;
	ColorTable[1][Blue] = 0;
	ColorTable[2][Blue] = 255;
	ColorTable[0][Yellow] = 255;
	ColorTable[1][Yellow] = 255;
	ColorTable[2][Yellow] = 0;
	ColorTable[0][White] = 255;
	ColorTable[1][White] = 255;
	ColorTable[2][White] = 255;
	ColorTable[0][Black] = 0;
	ColorTable[1][Black] = 0;
	ColorTable[2][Black] = 0;
	ColorTable[0][Magenta] = 255;
	ColorTable[1][Magenta] = 0;
	ColorTable[2][Magenta] = 144;
	ColorTable[0][Lime] = 255;
	ColorTable[1][Lime] = 0;
	ColorTable[2][Lime] = 0;


	/*
	int res;

	res = LoadImage(IMG_GRASS_TOP, "Textures/grass_top.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_GRASS_SIDE, "Textures/grass_side.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_HEALTH, "Textures/zycie.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LEAVES_OAK, "Textures/leaves_oak.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LEAVES_SPRUCE, "Textures/leaves_spruce.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LEAVES_BIRCH, "Textures/leaves_birch.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LOG_OAK, "Textures/log_oak.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LOG_SPRUCE, "Textures/log_spruce.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LOG_BIRCH, "Textures/log_birch.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_PLANKS_OAK, "Textures/planks_oak.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_PLANKS_BIRCH, "Textures/planks_birch.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_DIRT, "Textures/dirt.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_FLOOR, "Textures/floor.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_TELEPORT, "Textures/teleport.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_A, "Textures/A.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_B, "Textures/B.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_C, "Textures/C.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_D, "Textures/D.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LOGO, "Textures/Untitled_logo.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_SKY, "Textures/Sky2.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_MENU_EASY, "Textures/Menu_Easy.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_MENU_NORMAL, "Textures/Menu_Normal.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_MENU_HARD, "Textures/Menu_Hard.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_MENU_VERY_HARD, "Textures/Menu_VeryHard.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_WIN, "Textures/Win.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_LOSE, "Textures/Lose.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_CORRECT, "Textures/Correct.png", GL_RGBA);
	if (!res) return false;
	res = LoadImage(IMG_WRONG, "Textures/Wrong.png", GL_RGBA);
	if (!res) return false;


#pragma region Resources
	std::string lineAsString;
	std::ifstream inputFile("Resources/0.txt");
	if (!inputFile.is_open())
		throw std::exception("Can't read file");
	while (!inputFile.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile >> lineAsString;
				Level0[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputFile1("Resources/1.txt");
	if (!inputFile1.is_open())
		throw std::exception("Can't read file");
	while (!inputFile1.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile1 >> lineAsString;
				Level1[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputFile2("Resources/2.txt");
	if (!inputFile2.is_open())
		throw std::exception("Can't read file");
	while (!inputFile2.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile2 >> lineAsString;
				Level2[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputFile3("Resources/3.txt");
	if (!inputFile3.is_open())
		throw std::exception("Can't read file");
	while (!inputFile3.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile3 >> lineAsString;
				Level3[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputFile4("Resources/4.txt");
	if (!inputFile4.is_open())
		throw std::exception("Can't read file");
	while (!inputFile4.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile4 >> lineAsString;
				Level4[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputFile5("Resources/5.txt");
	if (!inputFile5.is_open())
		throw std::exception("Can't read file");
	while (!inputFile5.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile5 >> lineAsString;
				Level5[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputFile6("Resources/6.txt");
	if (!inputFile6.is_open())
		throw std::exception("Can't read file");
	while (!inputFile6.eof())
	{
		for (int i = 0; i < 38; i++) {
			for (int j = 0; j < 40; j++) {
				inputFile6 >> lineAsString;
				Level6[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputarea("Resources/area.txt");
	if (!inputarea.is_open())
		throw std::exception("Can't read file");
	while (!inputarea.eof())
	{
		for (int i = 0; i < 75; i++) {
			for (int j = 0; j < 75; j++) {
				inputarea >> lineAsString;
				Height[i][j] = lineAsString[0];
			}
		}
	}
	std::ifstream inputQuestion("Resources/area.txt");
	if (!inputarea.is_open())
		throw std::exception("Can't read file");
	while (!inputarea.eof())
	{
		for (int i = 0; i < 75; i++) {
			for (int j = 0; j < 75; j++) {
				inputarea >> lineAsString;
				Height[i][j] = lineAsString[0];
			}
		}
	}

	std::ifstream inputtrees("Resources/trees.txt");
	if (!inputtrees.is_open())
		throw std::exception("Can't read file");
	float number;
	while (!inputtrees.eof())
	{
		vec3 tmp;
		inputtrees >> tmp.x;
		tmp.y = 0;
		inputtrees >> tmp.z;
		trees.push_back(tmp);
	
	}

	LoadQuestion("str");
	RotateQuestionAnswers();
	for (int i = 0; i < ammoutOfQuestions; i++)
		UsedQuestions.push_back(false);

#pragma endregion 

	*/
	return true;
}