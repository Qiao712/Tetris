#pragma once
#include<vector>
#include "BlockFactory.h"
#include "CombinationFactory.h"
using namespace std;

class Block;
class BlockFactory;
class CombinationFactory;

class Game
{
public:
	//游戏属性

	static const int height = 32*20;					//游戏主场景高度
	static const int width = 32*13;						//游戏主场景宽度
	static const int length_block = 32;					//一定要为偶数，不然除法时会丢失位					

	Game();
	~Game();

	void loadRes();		//加载资源
	void render();		//渲染

	
	void logic();		//游戏内部逻辑处理,该函数集合一些函数
	void blockShowup();	//方块出现
	void blockMove();	//方块移动
	void blockRemove();	//方块消失
	void deathJudge();	//死亡判断
	
	//控制
	enum{NONE , MOVE_LEFT,MOVE_RIGHT, MOVE_DOWN, TRANSLATE};
	void control(int command);

	void createBlock(int type_id, int tex_id);		//创建方块
	Block* getBlockAt(int x, int y);	//返回某一点上的方块
private:
	BlockFactory blockFactory;	//block工厂，创建Block对象
	CombinationFactory combinationFactory;	//combination工厂
	

	//当前存在的方块
	vector<Block*> blocks;

	//贴纸
	vector<Block*> stickers;

	//游戏状态
	enum{ BLOCK_SHOWUP, BLOCK_MOVE1, BLOCK_REMOVE, BLOCK_MOVE2, GAME_OVER};
	int state = BLOCK_SHOWUP;						//当前游戏状态（阶段）
	unsigned long long time_interval = 0;

};

