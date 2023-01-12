#ifndef PLAYER_H
#define PLAYER_H

#include "Arena.h"

class Arena;
//Player declaration
class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};


#endif