#include "Maze.h"
#include "MCell.h"
#include "MTreeNode.h"
#include <iostream>
using namespace std;

int main()
{
	Maze maze(5, 5);
	maze.makeConnection(0, 0, 0, 1);
	for (int i = 0; i < maze.height - 1; i++) {
		for (int j = 0; j < maze.width - 1; j++) {
			if (i == j) {
				for (int k = i; k < maze.height - 1; k++)
					maze.makeConnection(k, j, k + 1, j);
				for (int m = j; m < maze.width - 1; m++)
					maze.makeConnection(i, m, i, m + 1);
				maze.makeConnection(i - 1, j, i, j);
			}
		}
	}
	maze.makeConnection(maze.height - 2, maze.width - 1, maze.height - 1, maze.width - 1);
	maze.printMaze();
	cout << '\n' << '\n' << '\n';
	auto tree = MTreeNode::beginTree(0, 0);
	int distances[6][6];
	auto iterate = tree;
	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			if (i == k) {
				auto prev = iterate;
				distances[i][k] = iterate->distance();
				for (int j = k + 1; j < 6; j++) {
					iterate->addChild(i, j);
					iterate = iterate->hasChild(i, j);
					distances[i][j] = iterate->distance();
				}
				iterate = prev;
				for (int j = i + 1; j < 6; j++) {
					iterate->addChild(j, k);
					iterate = iterate->hasChild(j, k);
					distances[j][k] = iterate->distance();
				}
				iterate = prev;
				iterate = iterate->hasChild(i, k + 1);
				iterate->addChild(i + 1, k + 1);
				distances[i + 1][k + 1] = iterate->distance();
				iterate = iterate->hasChild(i + 1, k + 1);
			}
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int k = 0; k < 5; k++) {
			cout << distances[i][k] << " ";
		}
		cout << endl;
	}

}