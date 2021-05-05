#include "Game.h"
#include "MySDL.h"
#include "Block.h"
#include "BlockFactory.h"
#include "Combination.h"
#include "CombinationFactory.h"

//BlockFactory Game::blockFactory;
//CombinationFactory Game::combinationFactory;

Game::Game()
{
	state = BLOCK_SHOWUP;
}

Game::~Game()
{
	//释放block
	for (Block* block : blocks) {
		delete block;
	}
}

void Game::render()
{
	for (Block* block : blocks) {
		block->render();
	}
	for (Block* sticker : stickers) {
		sticker->render();
	}
}

void Game::logic()
{
	//获取时间间隔
	time_interval = getTimeInterval();

	//根据状态，执行相应动作
	switch (state) {
		case BLOCK_SHOWUP: {
			blockShowup();
			state = BLOCK_MOVE1;
			break;
		}

		case BLOCK_MOVE1: {
			blockMove();
			break;
		}

		case BLOCK_REMOVE: {
			blockRemove();
			state = BLOCK_MOVE2;
			break;
		}

		case BLOCK_MOVE2: {
			blockMove();
			break;
		}

		case GAME_OVER_MENU: {
			
			break;
		}
	}

}

void Game::blockShowup()
{
	static int combination_type_id, texture_type;
	combination_type_id = getTime() % CombinationFactory::num_of_block_type;
	texture_type = getTime() % BlockFactory::num_of_block_texture;

	createBlock(combination_type_id,texture_type);
}

void Game::blockMove()
{
	bool hasMovingBlock = false;	//是否有移动中的方块

	//方块移动
	for (auto block : blocks) {
		if (block->velocity != 0) {
			block->move_down((int)time_interval);
			hasMovingBlock = true;
		}
	}

	//碰撞检测1，防止移除边界,停止触边的方块移动，并置于边界上
	for(auto block : blocks) {
		if (block->y + block->height > height) {
			block->setVelocity(0);					//移除，停止移动
			block->y = height - block->height;		//复位
		}
	}

	//碰撞检测2，与其他方块
	int l, r, b, t;						//储存修正值
	for (auto block1 : blocks) {
		for (auto block2 : blocks) {
			if (block2 == block1 || block1->velocity == 0) continue;
			if (block1->collisionDetect(*block2, l, r, b, t)) {
				////cout << block1 << " collides with" << block2 << endl;
				block1->setVelocity(0);								//移除，停止移动
				block1->move(0, b);									//修正复位,到该方块上方
				break;
			}

		}
	}

	//将停止移动的combination拆分为多个block
	static vector<Block*> block_from_combination;	//暂存拆分出来的block
	auto i = blocks.begin();
	Block* block,* block_t; 
	Combination* cmb;
	while(i != blocks.end()) {
		block = *i;
		if (block->velocity == 0 && typeid(*block) == typeid(Combination)) {
			cmb = (Combination*)block;
			while ((block_t = cmb->pop()) != nullptr) {
				block_from_combination.push_back(block_t);
			}

			//删除combination
			i = blocks.erase(i);
			delete block;
		}
		else {
			i++;
		}
	}
	while (!block_from_combination.empty()) {	//转移
		blocks.push_back(block_from_combination.back());
		block_from_combination.pop_back();
	}

	//如果没有可移动的方块
	if (!hasMovingBlock) {
		//失败判断
		deathJudge();

		//切换状态
		if (state == BLOCK_MOVE1) state = BLOCK_REMOVE;
		if (state == BLOCK_MOVE2) state = BLOCK_SHOWUP;
	}
}

void Game::blockRemove()
{
	static const int num_need = width / length_block;
	int num_line[30] = { 0 };			//统计每一行的方块的个数
	int line_lowest = -1;				//被消除的最底层的层数

	//计数
	for (auto i : blocks) {
		num_line[i->y / length_block]++;
	}

	//消除
	auto i = blocks.begin();
	while (i != blocks.end()) {
		if (num_line[(*i)->y / length_block] == num_need) {
			line_lowest = max(line_lowest, (*i)->y / length_block);

			delete (*i);
			i = blocks.erase(i);
		}
		else {
			i++;
		}
	}

	//将需要下落的方块合并
	static Combination* cmb[30];
	for (int i = 0; i < 30; i++) cmb[i] = nullptr;
	i = blocks.begin();
	while (i != blocks.end()) {
		int cur_line = (*i)->y / length_block;
		if (cur_line < line_lowest) {
			if (cmb[cur_line] == nullptr) {
				cmb[cur_line] = new Combination;
				cmb[cur_line]->y = (*i)->y;
				cmb[cur_line]->setVelocity(down_velocity);
			}

			(*i)->y = 0;
			cmb[cur_line]->addBlock((*i));

			i = blocks.erase(i);
		}
		else {
			i++;
		}
	}

	for (int i = 0; i < 30; i++) {
		if(cmb[i] != nullptr) blocks.push_back(cmb[i]);
	}
}

void Game::deathJudge()
{
	for (auto i : blocks) {
		if (i->velocity == 0 && i->y <= 0) {
			//cout << "Game over"<<endl;
			Block* s = BlockFactory::CreateSticker(0, 0, 0);
			s->position((width - s->getWidth()) / 2, (height - s->getHeight()) / 2);
			stickers.push_back(s);
			state = GAME_OVER_MENU;
		}
	}
}

void Game::control(int command)
{
	static unsigned long long time_interval_accumulative = 100000;
	time_interval_accumulative += time_interval;

	switch (command) {
		case MOVE_LEFT: {
			for (auto block : blocks) {
				if (block->velocity == 0) continue;
				if (block->x == 0) continue;

				block->move(-length_block, 0);
				
				//判断移动后是否碰撞
				for (auto block2 : blocks) {
					if (block->collisionDetect(*block2) && block != block2) {
						block->move(length_block, 0);	//复位
					}
				}
			}
			break;
		}
		case MOVE_RIGHT: {
			for (auto block : blocks) {
				if (block->velocity == 0) continue;
				if (block->x + block->width == width) continue;

				block->move(length_block, 0);

				//判断移动后是否碰撞
				for (auto block2 : blocks) {
					if (block->collisionDetect(*block2) && block != block2) {
						block->move(-length_block, 0);	//复位
					}
				}
			}
			break;
		}
		case MOVE_DOWN: {
			for (auto block : blocks) {
				if (block->velocity == 0) continue;
				block->setVelocity(0.8);
			}
			break;
		}
		case TRANSLATE: {
			for (auto block : blocks) {
				if (block->velocity == 0) continue;
				block->rotate_clockwise();

				//判断是否出界
				if (block->x + block->width > width || block->x < 0) {
					block->rotate_anticlockwise();
					continue;
				}

				//判断旋转后是否碰撞
				for (auto block2 : blocks) {
					if (block->collisionDetect(*block2) && block != block2) {
						block->rotate_anticlockwise();	//复位
					}
				}
			}
			break;
		}
	}
}

void Game::createBlock(int type_id, int tex_id)
{
	Block* block = CombinationFactory::createCombination(type_id, tex_id, (width / length_block / 2) * length_block,0);
	block->setVelocity(0.20);
	blocks.push_back(block);
}

Block* Game::getBlockAt(int x_, int y_)
{
	for (auto i : blocks) {
		if (i->x <= x_ && i->x + i->width > x_ && i->y <= y_ && i->y + i->height > y_) return i;
	}
	return nullptr;
}