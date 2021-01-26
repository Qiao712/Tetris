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
	//��Ϸ����

	static const int height = 32*20;					//��Ϸ�������߶�
	static const int width = 32*13;						//��Ϸ���������
	static const int length_block = 32;					//һ��ҪΪż������Ȼ����ʱ�ᶪʧλ					

	Game();
	~Game();

	void loadRes();		//������Դ
	void render();		//��Ⱦ

	
	void logic();		//��Ϸ�ڲ��߼�����,�ú�������һЩ����
	void blockShowup();	//�������
	void blockMove();	//�����ƶ�
	void blockRemove();	//������ʧ
	void deathJudge();	//�����ж�
	
	//����
	enum{NONE , MOVE_LEFT,MOVE_RIGHT, MOVE_DOWN, TRANSLATE};
	void control(int command);

	void createBlock(int type_id, int tex_id);		//��������
	Block* getBlockAt(int x, int y);	//����ĳһ���ϵķ���
private:
	BlockFactory blockFactory;	//block����������Block����
	CombinationFactory combinationFactory;	//combination����
	

	//��ǰ���ڵķ���
	vector<Block*> blocks;

	//��ֽ
	vector<Block*> stickers;

	//��Ϸ״̬
	enum{ BLOCK_SHOWUP, BLOCK_MOVE1, BLOCK_REMOVE, BLOCK_MOVE2, GAME_OVER};
	int state = BLOCK_SHOWUP;						//��ǰ��Ϸ״̬���׶Σ�
	unsigned long long time_interval = 0;

};

