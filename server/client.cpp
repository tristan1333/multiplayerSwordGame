#include "client.h"
#include <iostream>

Client::Client()
{
	peer = nullptr;
	client = nullptr;
}

void Client::initialiseClient(ENetAddress& tAddress)
{
	//client = enet_host_create(NULL, 1, 2, 0, 0);
	//address = tAddress;
	//enet_address_set_host(&address, "127.0.0.1");
	//address.port = 7777;
	//peer = enet_host_connect(client, &address, 1, 0);
}
