#include "MySDL.h"
#include "Game.h"
#include "res.h"

SDL_Window* win;       //����ָ��
SDL_Renderer* ren;	  //��Ⱦ��ָ��

bool init()
{
	//��ʼ��
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	//��������
	win = SDL_CreateWindow("Qiao's Tetris", 100, 100, 32 * 13, 32*20, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 0;
	}

	//������Ⱦ��
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 0;
	}

	return 1;
}


void clean()
{
	SDL_DestroyWindow(win);
	SDL_Quit();
}


void logError(std::string message)
{
	cout << message << "-SDL:" << SDL_GetError() << endl;
}

//last = true ��ʶ ��ȡ��һ��ʱ��������������
unsigned long long getTimeInterval(bool last)
{
	static unsigned long long time1 = 0, time2 = 0, interval;

	if (last) return interval;
	
	time2 = SDL_GetTicks();
	interval = time2 - time1;
	time1 = time2;
	return interval;
}

unsigned int getTime()
{
	return SDL_GetTicks();
}
