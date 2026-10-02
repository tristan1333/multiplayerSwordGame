#ifndef _HELPER_ENET
#define _HELPER_ENET
#include <enet/enet.h>
#include <stdint.h>

void intToBytes(int value, uint8_t* bytes);
int bytesToInt(uint8_t* bytes);


#endif