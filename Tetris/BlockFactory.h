#pragma once
#include<vector>
using namespace std;

class Block;
class Texture;
/*
*����Ĺ�����
* 
* ���༯�����п����õ�������
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
	static vector<Texture*> textures_block;		//�����������
	static vector<Texture*> textures_sticker;	//��ֽ��������
};

