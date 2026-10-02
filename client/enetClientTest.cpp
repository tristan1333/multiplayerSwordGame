// enetClientTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <enet/enet.h>
#include "enetHelperFunctions.h"
#include "SDL.h"
#include "SDLCore.h"
#include "gameHandler.h"
#include "fileReady.h"
#undef main
int main()
{
	if (enet_initialize() != 0)
	{
		std::cout << stderr, "Failed to init enet";
		return false;
	}
	if(!initSdl())
	{
		return 0;
	}
    ENetHost* client;
	Game mainGame = Game();
    client = enet_host_create(NULL, 1, 2, 0, 0);
	int lastPacketSent = 0;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;
	ENetPacket* packet;
	SDL_Event e;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	//int number = 64;
	//uint8_t data[4];
	//intToBytes(number, data);
	//int test = bytesToInt(data);
	//std::cout << "Test is " << test << "\n";
	
	enet_address_set_host(&address, getIP().c_str());
	std::cout << getIP();
	address.port = 10558;
	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL)
	{
		std::cout << "No available peer!";
	}
	if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connected to server! 127.0.0.1, 7777";
	}
	else
	{
		enet_peer_reset(peer);
		std::cout << "Connection to server failed";
	}
	//testMessage = "OPX200";
	//packet = enet_packet_create(testMessage.c_str(), testMessage.length() + 1, ENET_PACKET_FLAG_RELIABLE);
	//enet_peer_send(peer, 0, packet);
	//enet_packet_destroy(packet);
	//delete data;
	//data[4];
	//number = 48;
	//intToBytes(number, data);
	//packet = enet_packet_create(data, sizeof(data), ENET_PACKET_FLAG_RELIABLE);
	//enet_peer_send(peer, 0, packet);
	//enet_peer_disconnect(peer, 0);
	bool quit = false;
	if(client == NULL)
	{
		return 0;
	}
	while(!quit)
	{
		while (enet_host_service(client, &event, 0) > 0)
		{

			//packet = enet_packet_create(testMessage.c_str(), testMessage.length() + 1, ENET_PACKET_FLAG_RELIABLE);
			//enet_peer_send(peer, 0, packet);
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				{
				std::cout << "COnnection made!";
				break;
				}
			case ENET_EVENT_TYPE_RECEIVE:
				mainGame.handlePacket(event.packet);
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "Disconnect successful!";
				break;
			}
			if (SDL_GetTicks() - 10 < lastPacketSent)
			{//
				//std::string testMessage = "pee";
				//packet = enet_packet_create(testMessage.c_str(), testMessage.length() + 1, ENET_PACKET_FLAG_RELIABLE);
				//enet_peer_send(peer, 0, packet);
				//std::cout << "PEE";
			}
			//std::string holdMessage = "HOL";
			//packet = enet_packet_create(holdMessage.c_str(), holdMessage.length() + 1, ENET_PACKET_FLAG_RELIABLE);

		}
		mainGame.handleGame(e, currentKeyStates, peer);
		lastPacketSent = SDL_GetTicks();

		//testMessage.append("A");

	}

	enet_host_destroy(client);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
