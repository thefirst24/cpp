#pragma once
constexpr int array_size = 2;
class MTreeNode {

public:
    int i() const;
    int j() const;
    const MTreeNode* parent() const;
    const MTreeNode* child(int i) const;
    int distance() const;
    int childCount() const;
    bool addChild(int i, int j);
    MTreeNode* hasChild(int i, int j);
    static MTreeNode* beginTree(int i, int j);

private:
    int m_i;
    int m_j;
    MTreeNode* m_parent;
    MTreeNode* m_children[array_size];
    int m_distance;
    MTreeNode(MTreeNode* parent);

};