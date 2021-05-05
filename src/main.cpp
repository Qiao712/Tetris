#include<iostream>
#include<string>
#include"MySDL.h"
#include"Texture.h"
#include"res.h"
#include"BlockFactory.h"
#include"Game.h"
using namespace std;

int main(int, char**) {
	//初始化窗口
	bool success = init();
	if (!success) return 1;

	//游戏对象--核心
	Game game;

	//主循环
	SDL_Event e;
	bool quit = false;
	int time1 = 0,time2 = 0, delay_wanted = 10;
	while (!quit) {
		//delay
		time2 = getTime();
		if(time2 - time1 < delay_wanted){
			SDL_Delay(delay_wanted - (time2-time1));
			time1 = getTime();
		}else{
			time1 = time2;
		}

		//获取事件
		if (SDL_PollEvent(&e)) {
			//程序的退出
			if (e.type == SDL_QUIT)
				quit = true;

			//使用键盘状态
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);	//获取当前键盘状态
			if (currentKeyStates[SDL_SCANCODE_UP]) game.control(game.TRANSLATE);
			else if (currentKeyStates[SDL_SCANCODE_DOWN]) game.control(game.MOVE_DOWN);
			else if (currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_RIGHT]) game.control(game.MOVE_LEFT);
			else if (!currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_RIGHT]) game.control(game.MOVE_RIGHT);
			else game.control(game.NONE);	//传递NONE使control一定被执行一次
		}

		//游戏逻辑流程
		game.logic();

		//渲染
		SDL_RenderClear(ren);
		game.render();
		SDL_RenderPresent(ren);
	}

	clean();
	return 0;
}