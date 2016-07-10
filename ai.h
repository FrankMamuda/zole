/*
===========================================================================
Copyright (C) 2016 Avotu Briezhaudzetava

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see http://www.gnu.org/licenses/.

===========================================================================
*/

#ifndef AI_H
#define AI_H

//
// includes
//
#include "main.h"
#include "gamestate.h"
#include "game.h"
#include <list>
#include <climits>

//
// CURRENTLY IN OPEN-BOX TESTING
// BLACKBOX (unknown opponent card distribution) WILL BE INTRODUCED LATER
//
//

//
// namespace: AIinfo
//
namespace AIinfo {
static const short depthPerLevel[8] = { 2, 2, 2, 2, 2, 2, 3, 3 };
}

struct Successor {
    GameState state;
    short action;
    short nextPlayer;
};

class AI {
public:
    /**
     * @brief AI constructor
     */
    AI() : bestChoice( 0 ), nodeCount( 0 )  {}


    std::list<Successor> generateSuccessors( GameState &gs, int &playerIndex );
    int minimax( GameState &gs, int depth, int index, int alpha = -INT_MAX, int beta = INT_MAX );

public:
    int bestChoice;
    long long nodeCount;
    int playerIndex;
    int baseLevel;
  //  int winnerIndex[8];
};

#endif // AI_H
