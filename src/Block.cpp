#include "Block.h"
#include "Texture.h"

Block::Block(Texture* tex, int x_, int y_):texture(tex),x(x_),y(y_)
{
	//如果设为0，则使用纹理的大小
	if (height == 0) height = texture->getHeight();
	if (width == 0) width = texture->getWidth();
}


void Block::position(int x_, int y_)
{
	x = x_;
	y = y_;
}

void Block::move(int x_, int y_)
{
	x += x_;
	y += y_;
}

void Block::move_down(int time, double velocity_)
{
	move(0, (int)(velocity_ * time));
}

void Block::move_down(int time)
{
	move(0, (int)(velocity * time));
}

void Block::remove()
{
}

void Block::setVelocity(double v_)
{
	velocity = v_;
}

bool Block::collisionDetect(const Block& block, int& l, int& r, int& b, int& t)
{
	bool is = collisionDetect(block);

	l = block.x - (x + width);
	r = (block.x + block.width) - x;
	b = block.y - (y + height);
	t = (block.y + block.height) - y;
	return is;
}

bool Block::collisionDetect(const Block& block)
{
	if (x + width <= block.x) return false;
	if (x >= block.x + block.width) return false;
	if (y + height <= block.y) return false;
	if (y >= block.y + block.height) return false;

	return true;
}

void Block::rotate_anticlockwise()
{
	//Block旋转无意义
}

void Block::rotate_clockwise()
{
	//Block旋转无意义
}


void Block::render()
{
	if(texture != nullptr)
		texture->render(x, y, height, width);
}

void Block::render(int x_, int y_)
{
	if(texture != nullptr)
		texture->render(x_, y_, height, width);
}
