#include <iostream>

#include "libHello.h"

unsigned char MyHello(const char *szWorld) {
	std::cout << "MyHello : " << szWorld << std::endl;
}

int main(int argc, char *argv[])
{
	Hello(0);
	
	Hello(MyHello);
	return 0;
}
