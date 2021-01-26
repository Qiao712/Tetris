#pragma once
#include<vector>
#include"Block.h"
using namespace std;
/*
* 多个block的集合，其x，y为第一个被加入的block的x,y
* 其中的block使用在这个Combination中的局部坐标
*/
class Combination : public Block
{
	friend class CombinationFactory;
public:
	Combination();
	~Combination();

	//碰撞检测，并返回修正值
	bool collisionDetect(const Block& block, int& l, int& r, int& b, int& t) override;
	bool collisionDetect(const Block& block) override;

	//逆时针旋转
	void rotate_anticlockwise() override;
	void rotate_clockwise() override;

	//将一个block从combination中弹出,弹出时会将其坐标转换为在屏幕上的坐标
	Block* pop();
	void addBlock(Block* block);							//block的x，y为在这个combination中的局部坐标
	void addBlock(Block* block, int x, int y);				//x，y为在这个combination中的局部坐标

	void render() override;

private:
	vector<Block*> blocks;
};