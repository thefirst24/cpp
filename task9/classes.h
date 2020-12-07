#pragma once
class Maze;
class MCell {
    bool m_down = false;
    bool m_right = false;
    MCell() {};
public:
    bool right() const { return m_right; }
    bool down() const { return m_down; }
    void set_right(bool boolean) { m_right = boolean; }
    void set_down(bool boolean) { m_down = boolean; }
    friend class Maze;

};

class Maze {
    MCell* m_field;
public:
    void printMaze() const;
    Maze(int n, int m);
    int width;
    int height;
    MCell& cell(int i, int j) const;
    bool hasConnection(int i1, int j1, int i2, int j2) const;
    bool makeConnection(int i1, int j1, int i2, int j2);
    bool removeConnection(int i1, int j1, int i2, int j2);
};
class MTreeNode {
    int m_i;
    int m_j;
    MTreeNode* m_parent;
    MTreeNode* m_children[2];
    int m_distance;
    MTreeNode(MTreeNode* parent) { m_parent = parent; }
public:
    int i() const { return m_i; }
    int j() const { return m_j; }
    const MTreeNode* parent() const { return m_parent; }
    const MTreeNode* child(int i) const { return m_children[i]; }
    int distance() const { return m_distance; }
    int childCount() const;
    bool addChild(int i, int j);
    MTreeNode* hasChild(int i, int j);
    static MTreeNode* beginTree(int i, int j);
};