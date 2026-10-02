// eNetServerTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <enet/enet.h>
#include "enetHelperFile.h"
#include "enetInitFunctions.h"
#include <iostream>
#include "client.h"
#include "SDL.h"
#include "SDLCore.h"
#include "player.h"
#include "gameHandler.h"
#define WAITING 0
#define CONNECTED 1
#undef main
//#include "enetInitFunctions.h"
int main()
{
    int lastPacketSent = 0;
    int state = WAITING;
    if (!init())
    {
        return 0;
    }
    if(!initSdl())
    {
        return 0;
    }
    SDL_Event e;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    Game mainGame = Game();
    ENetAddress address;
    ENetHost* server;
    ENetPacket* packet;
    address.host = ENET_HOST_ANY;
    address.port = 10558;
    ENetEvent event;
    Client otherConnection = Client();
    server = enet_host_create(&address, 32, 1, 0, 0);
    if (server == NULL)
    {
        std::cout << stderr << " Server failed!";
    }
    int counter = 0;
    while(1)
    {
        while (enet_host_service(server, &event, 0) > 0)
        {
  
            switch (event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                {
                    std::cout << "New client connected!";
                    otherConnection.peer = event.peer;
                        
                    state = CONNECTED;
                		break;
                }
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    
                    //std::cout << "Packet received!" << "\n";
                    //const char* a = event.packet->data;

                    uint8_t* receivedData = event.packet->data;
                    char* test = (char*)receivedData;
                    std::string a = test;
                    mainGame.handlePacket(event.packet);
                    enet_packet_destroy(event.packet);
                    //int value = bytesToInt(receivedData);
                  //  std::cout << a << "\n";
                }
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:
                    std::cout << "Client disconnected!";
            }
        }
        if(otherConnection.peer != nullptr)
        {
               // std::string message = std::to_string(counter);
               // packet = enet_packet_create(message.c_str(), message.length() + 1, ENET_PACKET_FLAG_RELIABLE);
               // enet_peer_send(otherConnection.peer, 0, packet);
 
            lastPacketSent = SDL_GetTicks();
        }
        else
        {
           }
        if(state == CONNECTED)
        {
            mainGame.handleGame(e, currentKeyStates, otherConnection);
           // sendPlayerX.append(std::stoi(mainGame.controlledPlayer.getX()));
        }

    } 
    enet_host_destroy(server);
   atexit(enet_deinitialize);
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
