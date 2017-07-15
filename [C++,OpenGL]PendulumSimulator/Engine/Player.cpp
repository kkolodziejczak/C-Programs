#include "stdafx.h"
#include "Player.h"

Player::~Player()
{
}
void Player::init()
{
	// Inicjalizacja kamery:
	pos.x = 0.0f;
	pos.y = 18.75f;
	pos.z = 14.0f;

	dir.x = -0.008f;
	dir.y = -0.88f;
	dir.z = -0.46f;

};

float Player::getPosX() const
{
	return pos.x;
}
void Player::setPosX(const float x)
{
	this->pos.x = x;
}
float Player::getPosY() const
{
	return pos.y;
}
void Player::setPosY(const float y)
{
	this->pos.y = y;
}
float Player::getPosZ() const
{
	return pos.z;
}
void Player::setPosZ(const float z)
{
	this->pos.z = z;
}
float Player::getDirX() const
{
	return dir.x;
}
void Player::setDirX(const float x)
{
	this->dir.x = x;
}
float Player::getDirY() const
{
	return dir.y;
}
void Player::setDirY(const float y)
{
	this->dir.y = y;
}
float Player::getDirZ() const
{
	return dir.z;
}
void Player::setDirZ(const float z)
{
	this->dir.z = z;
}
float Player::GetSpeed() const
{
	return speed;
}
void Player::setSpeed(float speed)
{
	this->speed = speed;
}