#pragma once
#include<string>
#include<queue>
#include"MySDL.h"
#include"res.h"
using namespace std;

/*
* 封装的纹理
* 
* 
*/
class Texture
{
public:
	//path：文件路径；
	Texture(string path);
	~Texture();

	//渲染
	void render(int x, int y, int h, int w);
	void render(int x, int y);

	//get
	int getHeight() { return height; }
	int getWidth() { return width; }
private:
	//从文件中载入纹理，从\res中寻找
	void loadFromBMP(string path);
	
	
	SDL_Texture* texture;
	int height = 0;
	int width = 0;
};