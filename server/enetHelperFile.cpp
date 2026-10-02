#include "enetHelperFile.h"
#include <stdint.h>

void intToBytes(int value, uint8_t* bytes)
{
	bytes[0] = (value >> 24) & 0xFF;
	bytes[1] = (value >> 16) & 0xFF;
	bytes[2] = (value << 8) & 0xFF;
	bytes[3] = value & 0xFF;
}

int bytesToInt(uint8_t* bytes)
{
	int value = int((unsigned char)(bytes[0] << 24) | (unsigned char)(bytes[1] << 16) | (unsigned char) (bytes[2] << 8) | (unsigned char) bytes[3]);
	return value;
}