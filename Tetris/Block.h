#pragma once
#include<vector>
#include "Game.h"
using namespace std;

class Texture;

/*
*�����ķ�����
* Ҳ��Ϊ����Ļ����ʾ����ͨͼƬ-��ֽ
* ������BlockFactory����
*/
class Block
{
	friend class Game;
	friend class Combination;
public:
	Block() = default;
	Block(Texture* tex, int x_ = 0, int y_ = 0);

	void position(int x, int y);
	void move(int x, int y);		//�ƶ�,�����ԭλ��
	void move_down(int time, double velocity);		//ʹ���ٶȵ��ƶ�,(�ٶȣ���λ ����/����)
	void move_down(int time);
	void remove();					//�Ƴ�
	void setVelocity(double v_);	//�����ٶ�
	
	//l���ڷ���һ������ֵ��˵���ö�������ƶ�������ʹ����left�����������ұߣ�right��ǡ�ýӴ���r,b,tҲ��ˣ�right��bottom,top)
	virtual bool collisionDetect(const Block& block, int& l, int& r, int& b, int& t);	//��ײ���
	virtual bool collisionDetect(const Block& block);	//��ײ���

	//��ת������ֻ���ӿ�
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
	int height = Game::length_block;			//�����Ϊ0����ʹ������Ĵ�С
	int width = Game::length_block;			//�����Ϊ0����ʹ������Ĵ�С
	double velocity = 0;

	Texture* texture = nullptr;
};