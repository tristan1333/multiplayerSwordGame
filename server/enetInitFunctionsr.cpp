#include "enetInitFunctions.h"
#include <enet/enet.h>
#include <iostream>
bool init()
{
	if (enet_initialize() != 0)
	{
		std::cout << stderr, "Failed to init enet";
		return false;
	}
	return true;
}