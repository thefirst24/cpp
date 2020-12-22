#include "Maze.h"
#include "MCell.h"
#include <iostream>

using namespace std;

Maze::Maze(int n, int m) {
	m_field = new MCell[n * m];
	this->rows = n;
	this->columns = m;
}

MCell& Maze::cell(int i, int j) const {
	if (i > rows - 1 || i < 0 || j > columns - 1 || j < 0) return *(new MCell);
	return m_field[i * rows + j];
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
	auto cell2 = &(this->cell(i2, j2));
	if (i1 + j1 > i2 + j2) {
		if (i2 + 1 == i1) {
			cell2->set_down(true);
		}
		else
			cell2->set_right(true);
	}
	else {
		if (i1 + 1 == i2) {
			cell1->set_down(true);
		}
		else
			cell1->set_right(true);
	}
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
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j <columns; j++) {
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
						if (fromLeft && toDown && fromAbove) //┤
							cout << char(180);
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
										if (fromLeft && fromAbove) { //  ┘
											cout << char(217);
										}
										else {
											if (toRight && toDown) //┌
												cout << char(218);
											else {
												if (fromAbove)  //  │
													cout << char(179);
												else {
													if (toRight && fromLeft)
														cout << char(196);
													else {
														if (fromLeft && toRight) // ─
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

				}
				
			}
		}
		cout << endl;
	}
}