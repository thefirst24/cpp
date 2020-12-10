#pragma once
class MCell {

public:
    bool right() const;
    bool down() const;
    void set_right(bool boolean);
    void set_down(bool boolean);
    friend class Maze;

private:
    bool m_down = false;
    bool m_right = false;
    MCell() {};

};