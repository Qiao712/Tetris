#include "Combination.h"
#include<iostream>

Combination::Combination()
{

}

Combination::~Combination()
{
	for (auto i : blocks) {
		delete i;
	}
}

bool Combination::collisionDetect(const Block& block, int& l, int& r, int& b, int& t)
{
	for (auto i : blocks) {
		if (x + i->x + i->width <= block.x) continue;
		if (x + i->x >= block.x + block.width) continue;
		if (y + i->y + i->height <= block.y) continue;
		if (y + i->y >= block.y + block.height) continue;

		l = block.x - (x + i->x + i->width);
		r = (block.x + block.width) - (x + i->x);
		b = block.y - (y + i->y + i->height);
		t = (block.y + block.height) - (y + i->y);
		
		return true;
	}

	return false;
}

bool Combination::collisionDetect(const Block& block)
{
	for (auto i : blocks) {
		if (x + i->x + i->width <= block.x) continue;
		if (x + i->x >= block.x + block.width) continue;
		if (y + i->y + i->height <= block.y) continue;
		if (y + i->y >= block.y + block.height) continue;

		return true;
	}

	return false;
}

void Combination::rotate_anticlockwise()
{
	int x1_center, y1_center, x2_center, y2_center;
	for (auto i : blocks) {
		//计算出，内含的子block的中心
		x1_center = i->x + i->width / 2;
		y1_center = i->y + i->height / 2;

		//旋转变换中心的坐标
		x2_center = y1_center;
		y2_center = width - x1_center;

		//再由新的中心的坐标得到左上角坐标
		i->x = x2_center - i->width / 2;
		i->y = y2_center - i->height / 2;
	}

	swap(height, width);
}

void Combination::rotate_clockwise()
{
	int x1_center, y1_center, x2_center, y2_center;
	for (auto i : blocks) {
		//计算出，内含的子block的中心
		x1_center = i->x + i->width / 2;
		y1_center = i->y + i->height / 2;

		//旋转变换中心的坐标
		x2_center = height - y1_center;
		y2_center = x1_center;

		//再由新的中心的坐标得到左上角坐标
		i->x = x2_center - i->width / 2;
		i->y = y2_center - i->height / 2;
	}

	swap(height, width);
}

Block* Combination::pop()
{
	if(blocks.empty()) return nullptr;

	Block* b = blocks.back();
	blocks.pop_back();

	//坐标转换
	b->x += x;
	b->y += y;

	return b;
}

void Combination::render()
{
	for (auto i : blocks) {
		i->render(x + i->getX(), y + i->getY());
	}
}

void Combination::addBlock(Block* block)
{
	blocks.push_back(block);

	//计算宽高
	height = max(height, block->getY() + block->getHeight());
	width = max(width, block->getX() + block->getWidth());
}

void Combination::addBlock(Block* block, int x_, int y_)
{
	blocks.push_back(block);

	block->x = x_;
	block->y = y_;

	//计算宽高
	height = max(height, block->getY() + block->getHeight());
	width = max(width, block->getX() + block->getWidth());
}
