#pragma once
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