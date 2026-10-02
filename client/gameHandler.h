#ifndef _GAME_
#define _GAME_
#include "player.h"
#include "enet/enet.h"

class Game
{
public:
	Player controlledPlayer;
	Player enemyPlayer;
	SDL_Texture* background;
	bool victoryPause = false; //when true, display score
	int pauseTime = 0; //
	void handlePacket(ENetPacket*);
	Game();
	void handleGame(SDL_Event&, const Uint8*, ENetPeer*);
};


#endif