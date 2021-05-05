#pragma once
#include<vector>
using namespace std;

class Combination;

/*
* 使用预设的Combination复制生成Combination
*/
class CombinationFactory
{
public:
	CombinationFactory();
	static Combination* createCombination(int type_id, int block_id, int x_, int y_);

	static int num_of_block_type;
private:
	static void loadPatterns();			//硬编码方块组合
	static char patterns[100][4][4];					//储存方块组合
};