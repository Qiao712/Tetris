#pragma once
#include<vector>
#include "Game.h"
using namespace std;

class Texture;

/*
*基础的方块类
* 也作为在屏幕上显示的普通图片-贴纸
* 对象由BlockFactory创建
*/
class Block
{
	friend class Game;
	friend class Combination;
public:
	Block() = default;
	Block(Texture* tex, int x_ = 0, int y_ = 0);

	void position(int x, int y);
	void move(int x, int y);		//移动,相对于原位置
	void move_down(int time, double velocity);		//使用速度的移动,(速度，单位 像素/毫秒)
	void move_down(int time);
	void remove();					//移除
	void setVelocity(double v_);	//设置速度
	
	//l用于返回一个修正值，说明该对象如何移动，才能使其左（left）与检测对象的右边（right）恰好接触，r,b,t也如此（right，bottom,top)
	virtual bool collisionDetect(const Block& block, int& l, int& r, int& b, int& t);	//碰撞检测
	virtual bool collisionDetect(const Block& block);	//碰撞检测

	//旋转，接口
	virtual void rotate_anticlockwise();
	virtual void rotate_clockwise();

	virtual void render();
	virtual void render(int x_, int y_);

	int getX() { return x; }
	int getY() { return y; }
	int getHeight() { return height; }
	int getWidth() {return width;}

	void setHeight(int h) { height = h; }
	void setWidth(int w) { width = w; }
protected:
	int x = 0;
	int y = 0;
	int height = Game::length_block;			//如果设为0，则使用纹理的大小
	int width = Game::length_block;			//如果设为0，则使用纹理的大小
	double velocity = 0;

	Texture* texture = nullptr;
};