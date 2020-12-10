#include "MCell.h"
bool MCell::right() const { return m_right; }
bool MCell::down() const { return m_down; }
void MCell::set_right(bool boolean) { m_right = boolean; }
void MCell::set_down(bool boolean) { m_down = boolean; }