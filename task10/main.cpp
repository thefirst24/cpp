#include "Maze.h"
#include "MCell.h"
#include "MTreeNode.h"
#include <iostream>
#include <random>
#include <vector>
#include <tuple>
#include <algorithm>
#include <string>

using namespace std;

void buildFullMaze(Maze& iMaze, MTreeNode& tree) {
	int max = 0, average = 0;
	auto distances = new int*[iMaze.rows + 1];
	for (int z = 0; z < iMaze.rows + 1; z++) {
		distances[z] = new int[iMaze.rows + 1];
	}
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
		int attempts = 0;
		while (true) {
			if (attempts > 40) {
				if (stuck == 1500 || indexroot >= stack.size())
					break;
				i = stack[indexroot]->i();
				j = stack[indexroot]->j();
				root = *stack[indexroot];
				attempts = 0;
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
				attempts++;
			}			
		}
		if (stuck == 1500 || indexroot >= stack.size()) break;
		iMaze.makeConnection(i,j,i + randX, j + randY);
		i = i + randX;
		j = j + randY;
		root.addChild(i, j);
		distances[i][j] = root.distance();
		if (root.distance() > max)
			max = root.distance();
		average += root.distance();
		stack.push_back(root.hasChild(i, j));
		root = *root.hasChild(i, j);	
	}


	for (auto i = 0; i < iMaze.rows; i++)
	{
		for (auto k = 0; k < iMaze.rows; k++)
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
	cout << "\n\n\n" << endl;
	cout << "max weight is: " << max << endl;
	cout << "average weight is:  " << average / (iMaze.rows * iMaze.rows + 0.0f) << endl;
	cout << "\n\n\n" << endl;
}

int main()
{
	string read;
	int size;
	cout << "Enter size of labyrinth: ";
	cin >> read ;
	while (true) {
		try {
			size = stoi(read);
			break;
		}
		catch(invalid_argument arg) {
			cout << "Wrong input, try again" << endl;
			cin >> read;
		}
	}
	Maze maze(size, size);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, size);
	int i = uni(rng);
	int j = uni(rng);
	while (j != 0 && j != size && i != 0 && i != size)
	{
		i = uni(rng);
		j = uni(rng);
	}
	MTreeNode* tree = MTreeNode::beginTree(i,j);
	cout << "\n\n\n";
	buildFullMaze(maze, *tree);
	maze.printMaze();
}


