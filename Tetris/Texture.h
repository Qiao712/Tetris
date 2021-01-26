#pragma once
#include<string>
#include<queue>
#include"MySDL.h"
#include"res.h"
using namespace std;

/*
* ��װ������
* 
* 
*/
class Texture
{
public:
	//path���ļ�·����
	Texture(string path);
	~Texture();

	//��Ⱦ
	void render(int x, int y, int h, int w);
	void render(int x, int y);

	//get
	int getHeight() { return height; }
	int getWidth() { return width; }
private:
	//���ļ�������������\res��Ѱ��
	void loadFromBMP(string path);
	
	
	SDL_Texture* texture;
	int height = 0;
	int width = 0;
};