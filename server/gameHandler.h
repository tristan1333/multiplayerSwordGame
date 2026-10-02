#ifndef _GAME_
#define _GAME_
#include "player.h"
#include "enet/enet.h"
#include "client.h"
class Game
{
public:
	Player controlledPlayer;
	Player enemyPlayer;
	bool victoryPause = false; //when true, display score
	int pauseTime = 0; //Records when the game was paused
	int pauseLength = 1000; //how long we pause the game for when a hit is struck
	SDL_Texture* background;
	void handlePacket(ENetPacket*);
	Game();
	void handleGame(SDL_Event&, const Uint8*, Client);
};


#endif