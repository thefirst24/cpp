#pragma once
#include "MCell.h"
class Maze {

public:
    void printMaze() const;
    Maze(int n, int m);
    int width;
    int height;
    MCell& cell(int i, int j) const;
    bool hasConnection(int i1, int j1, int i2, int j2) const;
    bool makeConnection(int i1, int j1, int i2, int j2);
    bool removeConnection(int i1, int j1, int i2, int j2);

private:
    MCell* m_field;
};