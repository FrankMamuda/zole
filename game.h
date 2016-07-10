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

#ifndef GAME_H
#define GAME_H

//
// includes
//
#include "main.h"
#include "gamestate.h"

//
// classes
//
class GameState;

/**
 * @brief The Game class holds static functions for GameState manipulation
 */
class Game {
public:
    /**
     * @brief irand generates a random number between 0 and max
     * @param max top boundary
     * @return a randomly generated number
     */
    static short irand( short max ) { return ( rand() % ( short )( max + 1 )); }
    static void deal( GameState &gs );
    static void assignRoles( GameState &gs );
    static bool hasSuit( GameState &gs, int playerIndex, Zole::Suits suit );
    static bool tryCard( GameState &gs, int playerIndex, int cardIndex );
    static short strongestCard( GameState &gs );
    static void getLegalMoves( GameState &gs, int playerIndex, std::vector<short> &legalMoves );
    static void singleMove(GameState &gs, int playerIndex, short forcedIndex = -1 );
    static void move( GameState &gs );
    static void calculate( GameState &gs );
    static void play( GameState &gs );
    /**
     * @brief points returns points in a stack
     * @param gs current state of the game
     * @param stack stack index, either BIG or SMALL
     * @return points
     */
    static short points( GameState &gs, Zole::Roles stack ) {
        int points = 0;

        for ( auto cardIndex : gs.stack[stack] )
             points += Zole::points( cardIndex );

        return points;
    }
};


#endif // GAME_H
