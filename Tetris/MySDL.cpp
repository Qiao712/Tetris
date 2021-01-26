#include "MySDL.h"
#include "Game.h"
#include "res.h"

SDL_Window* win;       //窗口指针
SDL_Renderer* ren;	  //渲染器指针

bool init()
{
	//初始化
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 0;
	}

	//创建窗口
	win = SDL_CreateWindow("Qiao's Tetris", 100, 100, 32 * 13, 32*20, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 0;
	}

	//创建渲染器
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

//last = true 标识 获取上一次时间间隔，而不更新
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
