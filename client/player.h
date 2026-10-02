#ifndef _PLAYER_
#define _PLAYER_
#include "SDL.h"
#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3
class Player
{
public:
	Player();
	Player(double, double, double, double, int);


	int lastSpin = 0;
	int spinCap = 100;
	void reset(double, double, double, double, int);
	void setX(double);
	void setY(double);
	void setW(double);
	void setH(double);
	bool canSpin();
	void setSwordHitbox();
	double getX();
	double getY();
	double getW();
	double getH();
	int facing = EAST;
	SDL_Rect getHitbox();
	double getSpeed();
	void applySpeed(double, double);
	void setHitbox(double, double, double, double);
	void renderPlayer();
	bool checkSwordCollision(SDL_Rect, int);
	void handlePlayer(SDL_Event, const Uint8*);
	void handlePlayer();
	SDL_Texture* texture;
	SDL_Texture* sword;
	SDL_Rect swordHitbox = { 0,0,0,0 };
private:
	double x, y, w, h;
	double speed = 1;
	SDL_Rect hitbox;
};

#endif
