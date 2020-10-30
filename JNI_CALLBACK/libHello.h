#pragma once
extern "C" {
	typedef unsigned char(*Hello_CallBack)(const char* szWorld);

	void Hello(Hello_CallBack _Hello_CallBack);
}
