#include "gameHandler.h"
#include "SDLCore.h"
#include "fpsHandler.h"
#include <iostream>
#define TARGETFPS 60
#define TICKSPERFRAME 1000/TARGETFPS
extern std::vector<SDL_Texture*> textures;
Game::Game()
{
	controlledPlayer = Player(0, 0, 32, 32, EAST);
	enemyPlayer = Player(640 - 32, 480 - 32, 32, 32, WEST);
	background = textures[2];
}

void Game::handleGame(SDL_Event& e, const Uint8* currentKeyStates, Client otherConnection)
{

	SDL_RenderClear((mainren));
	renSpec(mainren, background, 640, 480, 0, 0);


	if(enemyPlayer.checkSwordCollision(controlledPlayer.swordHitbox, controlledPlayer.facing) && !victoryPause)
	{
		victoryPause = true;
		pauseTime = SDL_GetTicks();
		std::string victorPacket = "OPV1";
		ENetPacket* packet = enet_packet_create(victorPacket.c_str(), victorPacket.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(otherConnection.peer, 0, packet);
	}
	if(victoryPause)
	{
		std::cout << "??";
		if (pauseTime + pauseLength < SDL_GetTicks())
		{
			std::cout << "Unpausing!";
			victoryPause = false;
			//enemyPlayer = Player(640 - 32, 480 - 32, 32, 32, WEST);
			controlledPlayer.reset(0, 0, 32, 32, EAST);
			enemyPlayer.reset(640 - 32, 480 - 32, 32, 32, WEST);
			std::string restartPacket = "OPR1";
			ENetPacket* packet = enet_packet_create(restartPacket.c_str(), restartPacket.length() + 1, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(otherConnection.peer, 0, packet);
			return;
		}
		controlledPlayer.renderPlayer();
		enemyPlayer.renderPlayer();
		SDL_RenderPresent(mainren);
	}
	else
	{
		controlledPlayer.handlePlayer(e, currentKeyStates);
		enemyPlayer.handlePlayer();
		SDL_RenderPresent(mainren);
		ENetPacket* packet;
		std::string packetX = "OPX";
		packetX.append(std::to_string((int)controlledPlayer.getX()));
		std::cout << packetX;
		packet = enet_packet_create(packetX.c_str(), packetX.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(otherConnection.peer, 0, packet);
		std::string packetY = "OPY";
		packetY.append(std::to_string((int)controlledPlayer.getY()));
		packet = enet_packet_create(packetY.c_str(), packetY.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(otherConnection.peer, 0, packet);
		std::string packetF = "OPF";
		packetF.append(std::to_string(controlledPlayer.facing));
		packet = enet_packet_create(packetF.c_str(), packetF.length() + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(otherConnection.peer, 0, packet);
	}
	//enet_packet_destroy(packet);
	//std::cout << "Handling game!";
				   // counter++;
			   // std::string message = std::to_string(counter);
				//packet = enet_packet_create(message.c_str(), message.length() + 1, ENET_PACKET_FLAG_RELIABLE);
			   // enet_peer_send(otherConnection.peer, 0, packet);
			   // enet_packet_destroy(packet);
}

void Game::handlePacket(ENetPacket* packet)
{
	//std::string test = std::to_string(packet.);
	char* rawData = (char*)packet->data;
	std::string message = rawData;
	std::string messageType = message.substr(0, 3);
	std::string storedValue = message.erase(0, 3);
	double valueGrabbed = std::stoi(storedValue);
	if(messageType == "OPX")
	{
		enemyPlayer.setX(valueGrabbed);
	}
	else if(messageType == "OPY")
	{
		enemyPlayer.setY(valueGrabbed);
	}
	else if(messageType == "OPF")
	{
		enemyPlayer.facing = valueGrabbed;
	}
	else if(messageType == "OPV")
	{
		std::cout << "Received victory packet";
		victoryPause = true;
		pauseTime = SDL_GetTicks();
	}
//	std::cout << packet->data;
//	uint8_t* rawData = packet->data;
	//const char* characterData = (char*)rawData;
	//std::string message = std::to_string(*rawData);
	return;
}
