#pragma once
#include<vector>
using namespace std;

class Block;
class Texture;
/*
*方块的工厂类
* 
* 该类集合所有可能用到的纹理
*/
class BlockFactory
{
public:
	BlockFactory();
	~BlockFactory();
	static Block* CreateBlock(int texture_id, int x = 0, int y = 0);
	static Block* CreateTransparentBlock(int x = 0, int y = 0);
	static Block* CreateSticker(int texture_id, int x = 0, int y = 0);

	static int num_of_block_texture;
private:
	static vector<Texture*> textures_block;		//方块的纹理集合
	static vector<Texture*> textures_sticker;	//贴纸的纹理结合
};

