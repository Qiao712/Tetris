#pragma once
#include<vector>
#include"Block.h"
using namespace std;
/*
* ���block�ļ��ϣ���x��yΪ��һ���������block��x,y
* ���е�blockʹ�������Combination�еľֲ�����
*/
class Combination : public Block
{
	friend class CombinationFactory;
public:
	Combination();
	~Combination();

	//��ײ��⣬����������ֵ
	bool collisionDetect(const Block& block, int& l, int& r, int& b, int& t) override;
	bool collisionDetect(const Block& block) override;

	//��ʱ����ת
	void rotate_anticlockwise() override;
	void rotate_clockwise() override;

	//��һ��block��combination�е���,����ʱ�Ὣ������ת��Ϊ����Ļ�ϵ�����
	Block* pop();
	void addBlock(Block* block);							//block��x��yΪ�����combination�еľֲ�����
	void addBlock(Block* block, int x, int y);				//x��yΪ�����combination�еľֲ�����

	void render() override;

private:
	vector<Block*> blocks;
};