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

#ifndef GAMESTATE_H
#define GAMESTATE_H

//
// includes
//
#include <vector>

/**
 * @brief The GameState class
 */
class GameState {
    /*
    proposed optimizations:
        bool rl[3] can be replaced with a single unsigned short
        short pt[2] can be stored in trick/big/small stack at the beginning
    */

public:
    GameState() : round( 0 ), offset( 0 ), over( false ) {
    }

    /**
     * @brief stack stack of card indexes for players of the BIG/SMALL role (max 26)
     */
    std::vector<short> stack[Zole::OpposingTeams];

    /**
     * @brief table stack of card indexes on the table at the beginning of the game (max 2)
     */
    std::vector<short> table;

    /**
     * @brief player holds card indexes for all players (max 3x(8+2)=30)
     * amount is increased because AI would store guesses in this area
     */
    std::vector<short> player[Zole::Players];

    /**
     * @brief trick stack for card indexes in the current trick
     */
    std::vector<short> trick;

    /**
     * @brief role player roles, either BIG or small
     */
    std::vector<Zole::Roles> role;

    /**
     * @brief round current round of 8 total
     * DELTE ME. ROUND = numCards!
     */
    short round;

    /**
     * @brief offset next player to begin the round
     */
    short offset;

    /**
     * @brief over indicates whether game has ended
     */
    bool over;
};

#endif // GAMESTATE_H
