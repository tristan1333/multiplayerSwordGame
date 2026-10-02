#include "fileReady.h"
#include <fstream>
std::string getIP()
{
	std::ifstream file;
	file.open("ip.txt");
	std::string ip;
	file >> ip;
	file.close();
	return ip;
}
