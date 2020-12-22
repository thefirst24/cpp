#include "Maze.h"
#include "MCell.h"
#include "MTreeNode.h"
#include <iostream>
#include <random>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

void buildFullMaze(Maze& iMaze, MTreeNode& tree) {
	const  int size = 31;
	int distances[size][size];
	vector<MTreeNode*> stack;
	std::random_device rd;     
	std::mt19937 rng(rd());    
	std::uniform_int_distribution<int> uni(-1, 1);
	int i = tree.i();
	int j = tree.j();
	stack.push_back(&tree);
	distances[i][j] = 0;
	int randX = uni(rng);
	int randY = uni(rng);
	auto indexroot = 0;
	MTreeNode& root = tree;
	auto stuck = 0;
	while (true) {
		int tries = 0;
		while (true) {
			if (tries > 40) {
				if (stuck == 1500 || indexroot >= stack.size())
					break;
				i = stack[indexroot]->i();
				j = stack[indexroot]->j();
				root = *stack[indexroot];
				tries = 0;
				indexroot++;
				stuck++;
				
			}
			randX = uni(rng);
			randY = uni(rng);
			if (randX + randY == 1 || randX + randY == -1) {
				if (randX + i >= 0 && randY + j >= 0 && randX + i < iMaze.rows && randY + j < iMaze.columns)
				{
					auto finded = false;
					for (auto elem : stack) {
						if (elem->i() == randX + i && elem->j() == randY + j) {
							finded = true;
							break;
						}
					}
					if (!finded)
						break;
				}
				tries++;
			}			
		}
		if (stuck == 1500 || indexroot >= stack.size()) break;
		iMaze.makeConnection(i,j,i + randX, j + randY);
		i = i + randX;
		j = j + randY;
		root.addChild(i, j);
		distances[i][j] = root.distance();
		stack.push_back(root.hasChild(i, j));
		root = *root.hasChild(i, j);	
	}


	for (auto i = 0; i < 30; i++)
	{
		for (auto k = 0; k < 30; k++)
		{
			if (distances[i][k] < 10)
				cout << distances[i][k] << "   ";
			else {
				if (distances[i][k] > 99)
					cout << distances[i][k] << " ";
				else
					cout << distances[i][k] << "  ";
			}
		}
		cout << endl;
	}
}

int main()
{
	const int rows = 30;
	const int columns = 30;
	Maze maze(rows,columns);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(-1, 1);
	std::uniform_int_distribution<int> i_uni(0, rows);
	std::uniform_int_distribution<int> j_uni(0, columns);
	int i = i_uni(rng);
	int j = j_uni(rng);
	while (j != 0 && j != columns && i != 0 && i != rows)
	{
		i = i_uni(rng);
		j = j_uni(rng);
	}
	MTreeNode* tree = MTreeNode::beginTree(i,j);
	buildFullMaze(maze, *tree);
	maze.printMaze();
}


