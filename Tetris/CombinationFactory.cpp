#include"Game.h"
#include "CombinationFactory.h"
#include "Combination.h"
#include "Block.h"
#include "BlockFactory.h"

#include<iostream>
// vector<Combination*> CombinationFactory::combinations;

int CombinationFactory::num_of_block_type = 6;

CombinationFactory::CombinationFactory()
{
	static bool isExist = 0;
	if (isExist) return;
	isExist = 1;

	loadPatterns();
}

Combination* CombinationFactory::createCombination(int type_id, int block_id,int x_, int y_)
{
	Combination* cmb = new Combination;
	cmb->x = x_;
	cmb->y = y_;

	//Ó²±àÂë
	switch (type_id) {
	case 0: 
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block*2, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block*3, 0));
		break;
	case 1:
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block , 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block , Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block , Game::length_block*2));
		break;
	case 2:
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, Game::length_block*2));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, Game::length_block*2));
		break;
	case 3:
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block,0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block*2, Game::length_block));
		break;
	case 4:
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block*2, 0));
		break;
	case 5:
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, 0, Game::length_block));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, 0));
		cmb->addBlock(BlockFactory::CreateBlock(block_id, Game::length_block, Game::length_block));
		break;
	}
	
	return cmb;
}

void CombinationFactory::loadPatterns()
{
}
