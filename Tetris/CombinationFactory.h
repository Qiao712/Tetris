#pragma once
#include<vector>
using namespace std;

class Combination;

/*
* ʹ��Ԥ���Combination��������Combination
*/
class CombinationFactory
{
public:
	CombinationFactory();
	static Combination* createCombination(int type_id, int block_id, int x_, int y_);

	static int num_of_block_type;
private:
	static void loadPatterns();			//Ӳ���뷽�����
	static char patterns[100][4][4];					//���淽�����
};