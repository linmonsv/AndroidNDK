#include <iostream>

#include "libHello.h"

void Hello(Hello_CallBack _Hello_CallBack)
{
	if(NULL != _Hello_CallBack) {
		_Hello_CallBack("World in CallBack!");
	} else {
		std::cout << "World!" << std::endl;
	}
}
