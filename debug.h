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

#ifndef DEBUG_H
#define DEBUG_H

//
// includes
//
#include "main.h"
#include "game.h"
#include "gamestate.h"

//
// classes
//
class GameState;

/**
 * @brief The Debug class used to print info to the console
 */
class Debug {
public:
    /**
     * @brief printPlayers used for debugging purposes, prints out player cards
     * @param gs current state of the game
     * @param full determines whether to print unassigned card slots (-1s)
     */
    static void players( GameState &gs ) {
        int y;
        std::string cards;

        for ( y = 0; y < Zole::Players; y++ ) {
            cards.clear();

            for ( auto cardIndex : gs.player[y] ) {
                cards += "[";
                cards += Zole::symbol( cardIndex );
                cards += "] ";
            }

            if ( gs.player[y].size()) {
                if ( gs.role.at( y ) == Zole::Big )
                    std::cout << "Player " + std::to_string( y ) + " (BG): " + cards << std::endl;
                else
                    std::cout << "Player " + std::to_string( y ) + " (SM): " + cards << std::endl;
            }
        }
    }

    /**
     * @brief printTrick used for debugging purposes, prints out cards in the current trick
     * @param gs current state of the game
     */
    static void trick( GameState &gs ) {
        Zole::Suits required;
        int y;

        if ( gs.trick.size() != 3 )
            return;

        required = Zole::suit( gs.trick.at( 0 ));

        std::cout << "Trick:";
        for ( y = 0; y < Zole::Players; y++ ) {

            if ( y >= 1 && Zole::suit( gs.trick.at( y )) != required )
                std::cout << " #";
            else
                std::cout << " ";

            std::cout << Zole::symbol( gs.trick.at( y ));
        }
        std::cout << std::endl;
    }

    /**
     * @brief printStack used for debugging purposes, prints out cards in the big/small stack
     * @param gs current state of the game
     */
    static void stack( GameState &gs, Zole::Roles stack ) {
        int points = 0;
        std::string cards;

        if ( !gs.stack[stack].size())
            return;

        for ( auto cardIndex : gs.stack[stack] ) {
            cards += "[";
            cards += Zole::symbol( cardIndex );
            cards += "] ";
            points += Zole::points( cardIndex );
        }

        if ( stack == Zole::Big )
            std::cout << "BG: " + cards + std::to_string( points ) + "p" << std::endl;
        else if ( stack == Zole::Small )
            std::cout << "SM: " + cards + std::to_string( points ) + "p" << std::endl;
    }

    /**
     * @brief all print all relevant information
     * @param gs current state of the game
     */
    static void all( GameState &gs ) {
        Debug::players( gs );
        Debug::stack( gs, Zole::Big );
        Debug::stack( gs, Zole::Small );
        std::cout << std::endl;
    }

    /**
     * @brief points prints out best team and points
     * @param gs current state of the game
     */
    static void points( GameState &gs ) {
        int small, big;

        small = Game::points( gs, Zole::Small );
        big = Game::points( gs, Zole::Big );

        if ( small > big )
            std::cout << "SMALL wins over BIG, " + std::to_string( small ) + "p > " + std::to_string( big ) + "p " + std::to_string( big + small ) + "p" << std::endl;
        else
            std::cout << "BIG wins over SMALL, " + std::to_string( big ) + "p > " + std::to_string( small ) + "p " + std::to_string( big + small ) + "p" << std::endl;
    }
};

#endif // DEBUG_H

