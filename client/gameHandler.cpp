#include "gameHandler.h"
#include "SDLCore.h"
#include <iostream>
#define TARGETFPS 60
#define TICKSPERFRAME 1000/TARGETFPS
extern std::vector<SDL_Texture*> textures;
Game::Game()
{
	enemyPlayer = Player(0, 0, 32, 32, EAST);
	controlledPlayer = Player(640 - 32, 480 - 32, 32, 32, WEST);
	background = textures[2];
}

void Game::handleGame(SDL_Event& e, const Uint8* currentKeyStates, ENetPeer* peer)
{
	SDL_RenderClear((mainren));
	renSpec(mainren, background, 640, 480, 0, 0);
	if (victoryPause)
	{
		controlledPlayer.renderPlayer();
		enemyPlayer.renderPlayer();
		SDL_RenderPresent(mainren);
		return;
	}
	else if(enemyPlayer.checkSwordCollision(controlledPlayer.swordHitbox, controlledPlayer.facing))
	{
		victoryPause = true;
		std::string victorPacket = "OPV1";
		ENetPacket* packet = enet_packet_create(victorPacket.c_str(), victorPacket.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
	}
		controlledPlayer.handlePlayer(e, currentKeyStates);
		enemyPlayer.handlePlayer();
		SDL_RenderPresent(mainren);
		ENetPacket* packet;
		std::string packetX = "OPX";
		packetX.append(std::to_string((int)controlledPlayer.getX()));
		packet = enet_packet_create(packetX.c_str(), packetX.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		std::string packetY = "OPY";
		packetY.append(std::to_string((int)controlledPlayer.getY()));
		packet = enet_packet_create(packetY.c_str(), packetY.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		std::string packetF = "OPF";
		packetF.append(std::to_string(controlledPlayer.facing));
		packet = enet_packet_create(packetF.c_str(), packetF.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
}
	//std::cout << "Handling game!";	

void Game::handlePacket(ENetPacket* packet)
{
	//std::string test = std::to_string(packet.);
	char* rawData = (char*)packet->data;
	std::string message = rawData;
	std::string messageType = message.substr(0, 3);
	std::string storedValue = message.erase(0, 3);
	double valueGrabbed = std::stoi(storedValue);
	std::cout << message;
	if (messageType == "OPX")
	{
		enemyPlayer.setX(valueGrabbed);
	}
	else if (messageType == "OPY")
	{
		enemyPlayer.setY(valueGrabbed);
	}
	else if (messageType == "OPF")
	{
		enemyPlayer.facing = valueGrabbed;
	}
	else if(messageType == "OPS")  //Opponent score
	{
		if(valueGrabbed == 1)
		{
			victoryPause = true;
		}
	}
	else if(messageType == "OPV")
	{
		victoryPause = true;
	}
	else if(messageType == "OPR")
	{
		victoryPause = false;
		enemyPlayer.reset(0, 0, 32, 32, EAST);
		controlledPlayer.reset(640 - 32, 480 - 32, 32, 32, WEST);
	}
	//	std::cout << packet->data;
	//	uint8_t* rawData = packet->data;
		//const char* characterData = (char*)rawData;
		//std::string message = std::to_string(*rawData);
	return;
}
