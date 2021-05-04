#include<iostream>
#include<string>
#include"MySDL.h"
#include"Texture.h"
#include"res.h"
#include"BlockFactory.h"
#include"Game.h"
#include"Menu.h"
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
	while (!quit) {
		//更新GUI所需的鼠标位置
		int x, y;
		SDL_GetMouseState(&x, &y);
		Menu::updateMousePosition(x, y);

		//获取事件
		while (SDL_PollEvent(&e)) {
			//程序的退出
			if (e.type == SDL_QUIT) {
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