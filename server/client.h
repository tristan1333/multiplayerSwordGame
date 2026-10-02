#ifndef ENETCLIENT
#define ENETCLIENT
#include <enet/enet.h>
#include <string>
class Client
{
	public:
		Client();
		ENetHost* client;
		ENetAddress address;
		ENetPeer* peer;
		void initialiseClient(ENetAddress&);
	private:

};


#endif
