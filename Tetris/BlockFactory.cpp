#include "BlockFactory.h"
#include "Block.h"
#include "Texture.h"
#include<fstream>
#include<iostream>
using namespace std;

vector<Texture*> BlockFactory::textures_block;
vector<Texture*> BlockFactory::textures_sticker;
int BlockFactory::num_of_block_texture = 0;

BlockFactory::BlockFactory()
{
	static bool isExist = 0;
	if (isExist) return;
	isExist = 1;

	Texture* tex;

	//读取记录方块资源列表文件
	char file_name[1024];
	ifstream file_list_block("res\\list_blocks");
	if (!file_list_block.good()) {
		cout << "BlockFactory::BlockFactory: res\\list_blocks can't be open."<<endl;
		return;
	}
	//将资源列表中的文件读取到textures_block中
	while (!file_list_block.eof()) {
		num_of_block_texture++;

		file_list_block >> file_name;

		tex = new Texture(file_name);
		textures_block.push_back(tex);
	}


	//读取记录贴纸资源列表文件----------------
	ifstream file_list_sticker("res\\list_stickers");
	if (!file_list_sticker.good()) {
		cout << "BlockFactory::BlockFactory: res\\list_stickers can't be open." << endl;
		return;
	}
	while (!file_list_sticker.eof()) {
		file_list_sticker >> file_name;

		tex = new Texture(file_name);
		textures_sticker.push_back(tex);
	}
}

BlockFactory::~BlockFactory()
{
	for (auto tex : textures_block) {
		delete tex;
	}
}

Block* BlockFactory::CreateBlock(int texture_id, int x, int y)
{
	return new Block(textures_block[texture_id],x,y);
}

Block* BlockFactory::CreateTransparentBlock(int x, int y)
{
	return new Block(nullptr, x, y);
}

Block* BlockFactory::CreateSticker(int texture_id, int x, int y)
{
	Block* s = new Block(textures_sticker[texture_id], x, y);
	s->setHeight(textures_sticker[texture_id]->getHeight());
	s->setWidth(textures_sticker[texture_id]->getHeight());
	return s;
}
