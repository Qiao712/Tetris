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
	
	//��ʼ������
	bool success = init();
	if (!success) return 1;

	//��Ϸ����--����
	Game game;

	//��ѭ��
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		//����GUI��������λ��
		int x, y;
		SDL_GetMouseState(&x, &y);
		Menu::updateMousePosition(x, y);

		//��ȡ�¼�
		while (SDL_PollEvent(&e)) {
			//������˳�
			if (e.type == SDL_QUIT) {
				quit = true;

			//ʹ�ü���״̬
			const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);	//��ȡ��ǰ����״̬
			if (currentKeyStates[SDL_SCANCODE_UP]) game.control(game.TRANSLATE);
			else if (currentKeyStates[SDL_SCANCODE_DOWN]) game.control(game.MOVE_DOWN);
			else if (currentKeyStates[SDL_SCANCODE_LEFT] && !currentKeyStates[SDL_SCANCODE_RIGHT]) game.control(game.MOVE_LEFT);
			else if (!currentKeyStates[SDL_SCANCODE_LEFT] && currentKeyStates[SDL_SCANCODE_RIGHT]) game.control(game.MOVE_RIGHT);
			else game.control(game.NONE);	//����NONEʹcontrolһ����ִ��һ��
		}

		//��Ϸ�߼�����
		game.logic();

		//��Ⱦ
		SDL_RenderClear(ren);
		game.render();
		SDL_RenderPresent(ren);
	}

	clean();
	return 0;
}