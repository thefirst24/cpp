#pragma once
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