#include "player.h"
#include "SDLCore.h"
#include <iostream>
extern std::vector<SDL_Texture*> textures;
Player::Player()
{
	setX(0);
	setY(0);
	setW(32);
	setH(32);
	sword = textures[1];
	texture = textures[0];
}

Player::Player(double x, double y, double w = 32, double h = 32, int facing = EAST)
{
	setX(x);
	setY(y);
	setW(w);
	setH(h);
	sword = textures[1];
	texture = textures[0];
	this->facing = facing;
}

void Player::setX(double x)
{
	this->x = x;
}

void Player::setY(double y)
{
	this->y = y;
}

void Player::setW(double w)
{
	this->w = w;
}

void Player::setH(double h)
{
	this->h = h;
}

double Player::getX()
{
	return x;
}

double Player::getY()
{
	return y;
}

double Player::getW()
{
	return w;
}

double Player::getH()
{
	return h;
}

SDL_Rect Player::getHitbox()
{
	return hitbox;
}

void Player::setHitbox(double x, double y, double w, double h)
{
	hitbox.x = x;
	hitbox.y = y;
	hitbox.w = w;
	hitbox.h = h;
}

double Player::getSpeed()
{
	return speed;
}

void Player::applySpeed(double x = 0, double y = 0)
{
	setX(getX() + (getSpeed() * x));
	if (getX() < 0)
	{
		setX(0);
	}
	else if (getX() + getW() > 640)
	{
		setX(640 - getW());
	}
	setY(getY() + (getSpeed() * y));
	if (getY() < 0)
	{
		setY(0);
	}
	else if (getY() + getH() > 480)
	{
		setY(480 - getH());
	}
}

void Player::renderPlayer()
{
	renSpec(mainren, texture, getW(), getH(), getX(), getY() - (getH() / 2) + 5);
	if (facing == EAST)
	{
		renSpec(mainren, sword, 50, 10, getX() + getW(), getY());
	}
	else if (facing == WEST)
	{
		renSpec(mainren, sword, 50, 10, getX() - 50, getY(), SDL_FLIP_HORIZONTAL);
	}
	else if (facing == NORTH)
	{
		renAngle(mainren, sword, getX() - 9, getY() - getH() - 5, 50, 10, -90, NULL, SDL_FLIP_NONE);
	}
	else if (facing == SOUTH)
	{
		renAngle(mainren, sword, getX() - 9, getY() + 35, 50, 10, 90, NULL, SDL_FLIP_NONE);
	}
}


void Player::setSwordHitbox()
{
	if (facing == EAST)
	{
		swordHitbox.x = getX() + getH();
		swordHitbox.y = getY();
		swordHitbox.w = 50;
		swordHitbox.h = 10;
	}
	else if (facing == WEST)
	{
		swordHitbox.x = getX() - 50;
		swordHitbox.y = getY();
		swordHitbox.w = 50;
		swordHitbox.h = 10;
	}
	else if (facing == NORTH)
	{
		swordHitbox.x = getX() + (getW() / 2) - 5;
		swordHitbox.y = getY() - getH() - 20;
		swordHitbox.w = 10;
		swordHitbox.h = 50;
	}
	else if (facing == SOUTH)
	{
		swordHitbox.x = getX() + (getW() / 2) - 5;
		swordHitbox.y = getY() + getH() - 20;
		swordHitbox.w = 10;
		swordHitbox.h = 50;
	}
}

bool Player::checkSwordCollision(SDL_Rect sword, int enemyFacing) //Checks if the sword coollides and checks the facing if a hit is struck
{
	SDL_Rect playerHitbox = { (int)x + 7, (int)y - 9,(int)w - 14, (int)h - 5 };

	SDL_Rect R;
	renSpec(mainren, textures[0], playerHitbox.w, playerHitbox.h, playerHitbox.x, playerHitbox.y);
	renSpec(mainren, textures[0], sword.w, sword.h, sword.x, sword.y);
	if (SDL_IntersectRect(&playerHitbox, &sword, &R))
	{
		if (facing == EAST && enemyFacing == WEST || facing == WEST && enemyFacing == EAST)
		{
			return false;
		}
		else if (facing == NORTH && enemyFacing == SOUTH || facing == SOUTH && enemyFacing == NORTH)
		{
			return false;
		}
		return true;
	}
	return false;
}

void Player::handlePlayer()
{
	setSwordHitbox();
	renderPlayer();
}


void Player::handlePlayer(SDL_Event e, const Uint8* currentKeyStates)
{
	while (SDL_PollEvent(&e) != 0)
	{
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D])
	{
		applySpeed(1, 0);
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A])
	{
		applySpeed(-1, 0);
	}
	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W])
	{
		applySpeed(0, -1);
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S])
	{
		applySpeed(0, 1);
	}
	if (currentKeyStates[SDL_SCANCODE_F])
	{
		if (canSpin())
		{
			if (facing == EAST)
			{
				facing = NORTH;
			}
			else
			{
				facing -= 1;
			}
		}

	}
	if (currentKeyStates[SDL_SCANCODE_G])
	{
		if (canSpin())
		{
			if (facing == NORTH)
			{
				facing = EAST;
			}
			else
			{
				facing += 1;
			}
		}

	}
	setSwordHitbox();
	renderPlayer();
}

void Player::reset(double x, double y, double w, double h, int f)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->facing = f;
}

bool Player::canSpin()
{
	if (lastSpin + spinCap < SDL_GetTicks())
	{
		lastSpin = SDL_GetTicks();
		return true;
	}

	return false;
}