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

//
// includes
//
#include <list>
#include <algorithm>
#include "main.h"
#include "game.h"
#include "gamestate.h"
#include "debug.h"
#include "ai.h"

AI *ai = new AI();

/**
 * @brief Game::deal gives random cards to players
 * @param gs current state of the game
 */
void Game::deal( GameState &gs ) {
    int y, k;
    std::vector<int> cardIndexes;

    // generate and shuffle a list of card indexes
    for ( y = 0; y < Zole::NumCards; y++ )
        cardIndexes.push_back( y );
    std::random_shuffle( cardIndexes.begin(), cardIndexes.end());

    // clear player cards and randomly give 8
    for ( y = 0; y < Zole::Players; y++ )
        gs.player[y].clear();

    for ( y = 0; y < Zole::Players; y++ ) {
        for ( k = 0; k < Zole::PlayerCards; k++ ) {
            gs.player[y].push_back( cardIndexes.back());
            cardIndexes.pop_back();
        }
    }

    // put the remaining cards on the table
    for ( y = 0; y < Zole::Table; y++ ) {
        gs.table.push_back( cardIndexes.back());
        cardIndexes.pop_back();
    }

    // clear stacks
    gs.stack[Zole::Big].clear();
    gs.stack[Zole::Small].clear();

    // reset counters
    gs.round = 0;
    gs.offset = 0;
}

/**
 * @brief Game::assignRoles assingns either the role of the BIG or the SMALL to each of the players
 * @param gs current state of the game
 */
void Game::assignRoles( GameState &gs ) {
    int y;
    int bigIndex = -1;
    Zole::Roles state[Zole::Players][Zole::Players] = {{ Zole::Big, Zole::Small, Zole::Small }, { Zole::Small, Zole::Big, Zole::Small }, { Zole::Small, Zole::Small, Zole::Big }};
    int rand;

    rand = Game::irand( Zole::Players - 1 );
    for ( y = 0; y < Zole::Players; y++ ) {
        gs.role.push_back( state[rand][y] );

        if ( state[rand][y] ) {
            bigIndex = y;
            ai->playerIndex = bigIndex;
            std::cout << "ai assigned index " << ai->playerIndex << std::endl;
        }
    }

    if ( bigIndex == -1 )
        return; /* internal error */

    // for now give the table to a random player (who assumes role of the Big)
    // ai, however, should choose a strategy
    if ( !gs.table.size())
        return; /* internal error */


    // put the remaining cards on the table
    for ( y = 0; y < Zole::Table; y++ ) {
        gs.player[bigIndex].push_back( gs.table.back());
        gs.table.pop_back();
    }

    // now choose a random card and put it in the big stack
    std::random_shuffle( gs.player[bigIndex].begin(), gs.player[bigIndex].end());
    for ( y = 0; y < Zole::Table; y++ ) {
        gs.stack[Zole::Big].push_back( gs.player[bigIndex].back());
        gs.player[bigIndex].pop_back();
    }
}

/**
 * @brief Game::hasSuit checks whether a player has a specific card suit
 * @param gs current state of the game
 * @param playerIndex index of the player to be tested
 * @param suit suit of the card to be matched
 * @return success or failure
 */
bool Game::hasSuit( GameState &gs, int playerIndex, Zole::Suits suit ) {
    for ( auto cardIndex : gs.player[playerIndex] ) {
        if ( Zole::suit( cardIndex ) == suit )
            return true;
    }

    return false;
}

/**
 * @brief Game::tryCard tests whether a given card makes a legal move
 * @param gs current state of the game
 * @param playerIndex index of the player that has given the card
 * @param cardIndex
 * @return success or failure
 */
bool Game::tryCard( GameState &gs, int playerIndex, int cardIndex ) {
    if ( !gs.trick.empty()) {
        if ( Zole::suit( gs.trick.front()) != Zole::suit( cardIndex )) {
            if ( Game::hasSuit( gs, playerIndex, Zole::suit( gs.trick.front())))
                return false;
        }
    }
    return true;
}

/**
 * @brief Game::strongestCard determines the strongest card in the trick
 * @param gs current state of the game
 * @return card index in the trick stack
 */
short Game::strongestCard( GameState &gs ) {
    int counter = 0, min = INT_MAX;

    // get the minimum (the most powerful card)
    for ( auto cardIndex : gs.trick )
        min = std::min( min, Zole::strength( cardIndex ));

    // find it
    for ( auto cardIndex : gs.trick ) {
        if ( min == Zole::strength( cardIndex ))
            break;

        counter++;
    }

    // return it
    return counter;
}

/**
 * @brief Game::getLegalMoves generares a list of all legal moves available to player
 * @param gs current state of the game
 * @param playerIndex
 */
void Game::getLegalMoves( GameState &gs, int playerIndex, std::vector<short> &legalMoves ) {
    for ( auto cardIndex : gs.player[playerIndex] ) {
        if ( Game::tryCard( gs, playerIndex, cardIndex ))
            legalMoves.push_back( cardIndex );
    }
}

/**
 * @brief Game::singleMove
 * @param gs current state of the game
 * @param playerIndex
 * @param forcedIndex
 */
void Game::singleMove( GameState &gs, int playerIndex, short forcedIndex ) {
    int cardIndex;

    // for now, choose a card on random until it is a valid one
    std::vector<short> legalMoves;
    Game::getLegalMoves( gs, playerIndex, legalMoves );

    if ( !legalMoves.size())
        return; /* internal error */

    if ( forcedIndex == -1 ) {
        cardIndex = Game::irand( legalMoves.size() - 1 );

        gs.trick.push_back( legalMoves[cardIndex] );
        gs.player[playerIndex].erase( std::remove( gs.player[playerIndex].begin(), gs.player[playerIndex].end(), legalMoves[cardIndex] ), gs.player[playerIndex].end());
    } else {
        cardIndex = forcedIndex;
        gs.trick.push_back( forcedIndex );
        gs.player[playerIndex].erase( std::remove( gs.player[playerIndex].begin(), gs.player[playerIndex].end(), forcedIndex ), gs.player[playerIndex].end());
    }
}

/**
 * @brief Game::move performs a move by all three players, either randomly or by an ai (not implemented)
 * @param gs current state of the game
 */
void Game::move( GameState &gs ) {
    int y, playerIndex;

    // choose cards from players
    for ( y = 0; y < 3; y++ ) {
        playerIndex = ( gs.offset + y ) % ( Zole::Players );

        if ( gs.role.at( playerIndex ) == Zole::Big ) {
            static const short depthPerLevel[8] = { 2, 3, 4, 5, 4, 3, 2, 1 };

            ai->bestChoice = -1;
            ai->baseLevel = depthPerLevel[gs.round];
            ai->minimax( gs, depthPerLevel[gs.round], playerIndex );

            Game::singleMove( gs, playerIndex, ai->bestChoice );
            ai->nodeCount = 0;
        } else {
            Game::singleMove( gs, playerIndex, -1 );
        }
    }
    Debug::trick( gs );
    Game::calculate( gs );
}

/**
 * @brief Game::calculate determine winner and award cards from the trick
 * @param gs current state of the game
 */
void Game::calculate( GameState &gs ) {
    short offsets[3][3] = {{ 0, 1, 2 }, { 1, 2, 0 }, { 2, 0, 1 }};
    int strongest, playerIndex;
    Zole::Roles role;

    // not enough cards for calculation
    if ( gs.trick.size() != 3 )
        return; /* internal error */

    // get best card and player that had it
    strongest = strongestCard( gs );
    playerIndex = offsets[gs.offset % Zole::Players][strongest];

    // award the team with the strongest card
    role = gs.role.at( playerIndex );
    for ( auto cardIndex : gs.trick )
        gs.stack[role].push_back( cardIndex );

  //  std::
    gs.round++;
    gs.offset = playerIndex;

    if ( gs.round == 8 )
        gs.over = true;
}

/**
 * @brief Game::play plays out a match of Zole game
 * @param gs current state of the game
 */
void Game::play( GameState &gs ) {
    std::cout << "New Game" << std::endl;

    gs.offset = Game::irand( Zole::Players - 1 );
    gs.over = false;
    Game::deal( gs );
    Game::assignRoles( gs );
    Debug::all( gs );

    // perform moves in 8 rounds
    for ( int y = 0; y < 8; y++ ) {
        std::cout << "Round " << gs.round + 1 << " by Player " << ( gs.offset % ( Zole::Players )) << std::endl;
        gs.trick.clear();
        Game::move( gs );
        Debug::all( gs );
    }

    std::cout << "Game Over" << std::endl;
    Debug::points( gs );
    std::cout << std::endl;
}
