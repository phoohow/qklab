#include "TwinTaskKill.h"
#include <iostream>
#include <string>

/*
A Tool function: kill process by name in windows platform
*/
int main(int argc, char *argv[])
{
	if (1 == argc)
	{
		std::cerr << "Must have at least 1 processname!\n";
		return 0;
	}

	for (int i = 1; i < argc; ++i)
		killProcess(argv[i]);

	return 0;
}
