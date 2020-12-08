#include "Maze.h"
#include "MCell.h"
#include "MTreeNode.h"
#include <iostream>

using namespace std;

Maze::Maze(int n, int m) {
	m_field = new MCell[n * m];
	this->width = n;
	this->height = m;
}

MCell& Maze::cell(int i, int j) const {
	if (i > width - 1 || i < 0 || j > height - 1 || j < 0) return *(new MCell);
	return m_field[i * width + j];
};

bool Maze::hasConnection(int i1, int j1, int i2, int j2) const {
	auto cell1 = cell(i1, j1);
	if (cell1.down() && i1 + 1 == i2 && j1 == j2)
		return true;
	if (cell1.right() && j1 + 1 == j2 && i1 == i2)
		return true;
	return false;
}

bool Maze::makeConnection(int i1, int j1, int i2, int j2) {
	if (i1 + 1 + j1 != i2 + j2 && i1 + j1 != i2 + j2 + 1) return false;
	auto cell1 = &(this->cell(i1, j1));
	if (i1 + 1 == i2) {
		cell1->set_down(true);
	}
	else
		cell1->set_right(true);
	return true;
}

bool Maze::removeConnection(int i1, int j1, int i2, int j2) {
	if (i1 + 1 + j1 != i2 + j2 && i1 + j1 != i2 + j2 + 1) return false;
	auto cell1 = &(this->cell(i1, j1));
	if (i1 + 1 == i2) {
		cell1->set_down(false);
	}
	else
		cell1->set_right(false);
	return true;
}



void Maze::printMaze() const {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if ((i == width - 1 || j == height - 1) && i != width - 2) {
				cout << '0'; continue;
			};
			auto fromLeft = hasConnection(i, j - 1, i, j);
			auto fromAbove = hasConnection(i - 1, j, i, j);
			auto toRight = hasConnection(i, j, i, j + 1);
			auto toDown = hasConnection(i, j, i + 1, j);
			if (fromLeft && fromAbove && toRight && toDown) // ┼
				cout << char(197);
			else {
				if (fromLeft && toRight && toDown) // ┬
					cout << char(194);
				else {
					if (fromAbove && toDown && toRight) // ├
						cout << char(195);
					else {
						if (fromLeft && fromAbove && toRight) // ┴
							cout << char(193);
						else {
							if (fromAbove && toRight)   //└
								cout << char(192);
							else {
								if (fromLeft && toDown) //┐
									cout << char(191);
								else {
									if (toRight && toDown)
										cout << char(218);
									else {
										if (fromAbove)  //  │
											cout << char(179);
										else {
											if (fromLeft) // ─
												cout << char(196);
											else cout << '0';
										}
									}
								}
							}
						}
					}
				}
			}
		}
		cout << endl;
	}
}

MTreeNode* MTreeNode::beginTree(int i, int j) {
	auto tree = new MTreeNode(nullptr);
	tree->m_i = i;
	tree->m_j = j;
	tree->m_distance = 0;
	return tree;
}

bool MTreeNode::addChild(int i, int j) {
	if (this->hasChild(i,j) == nullptr && this->i() + this->j() + 1 == i + j) {
		auto node = new MTreeNode(this);
		node->m_i = i;
		node->m_j = j;
		node->m_distance = this->distance() + 1;
		this->m_children[this->childCount()] = node;
		return true;
	}
	return false;
	
}

MTreeNode* MTreeNode::hasChild(int i, int j) {
	for (int x = 0; x < 2; x++) {
		if (this->m_children[x] != NULL) {
			auto m_i = m_children[x]->m_i;
			auto m_j = m_children[x]->m_j;
			if (m_i == i && m_j == j)
				return m_children[x];
		}
	}
	return nullptr;
}

int MTreeNode::childCount() const {
	int count = 0;
	for (int i = 0; i < 2; i++) {
		if (this->m_children[i] != NULL)
			count++;
	}
	return count;
}