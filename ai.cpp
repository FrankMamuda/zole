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
#include "ai.h"

/**
 * @brief generateSuccessors gets legal moves and corresponding successor states
 * @param gs current state of the game
 * @param playerIndex index of the player
 * @return list of successor states
*/
std::list<Successor> AI::generateSuccessors( GameState &gs, int &index ) {
    std::vector<short> legalMoves;
    std::list<Successor> successors;

    // get legal moves and corresponding successor states
    Game::getLegalMoves( gs, index, legalMoves );

    // iterate over legal moves
    for ( auto cardIndex : legalMoves ) {
        int winner;
        Successor successor;
        GameState newState;

        newState = gs;
        winner = -1;

        // simulate a single move
        Game::singleMove( newState, index, cardIndex );

        // calculate outcome when trick is full
        if ( newState.trick.size() == 3 ) {
            Game::calculate( newState );
            winner = newState.offset;
        }

        // generate a new successor
        successor.state = newState;
        successor.action = cardIndex;

        if ( winner == -1 )
            successor.nextPlayer = index + 1;
        else
            successor.nextPlayer = winner;

        // append successor
        successors.insert( successors.end(), successor );
    }

    return successors;
}

/**
 * @brief AI:minimax
 * @param gs
 * @param depth
 * @param index
 * @return
 */
int AI::minimax(GameState &gs, int depth, int index, int alpha, int beta ) {
    int bestValue, value;
    bool maximizer;

    // terminal node reached
    if ( depth == 0 || gs.over ) {
        int points;

        // terminal state calls for an evaluation
        points = Game::points( gs, Zole::Big ) - Game::points( gs, Zole::Small );
        return points;
    } else {
        // wrap around
        index = index % Zole::Players;
        this->nodeCount++;
    }

    // deterine whether maximixer or minimizer
    if ( index == this->playerIndex ) {
        maximizer = true;
        bestValue = -INT_MAX;
    } else {
        maximizer = false;
        bestValue = INT_MAX;
    }

    // generate successors using legal moves
    std::list<Successor> successors = this->generateSuccessors( gs, index );

    // iterate over successors
    for ( std::list<Successor>::iterator it = successors.begin(); it != successors.end(); it++ ) {
        Successor *successor = &*it;
        GameState *state = &successor->state;
        short nextPlayer = successor->nextPlayer;

        // recurse further
        if ( state->trick.size() == 3 ) {
            state->trick.clear();

            value = this->minimax( *state, depth - 1, nextPlayer );
        } else {
            value = this->minimax( *state, depth, nextPlayer );
        }

        if ( maximizer ) {
            bestValue = std::max( bestValue, value );

            alpha = std::max( alpha, bestValue );
            if ( beta <= alpha )
                break;
        } else {
            bestValue = std::min( bestValue, value );

            beta = std::min( beta, bestValue );
            if ( beta <= alpha )
                break;
        }

        // store best available move
        if ( value == bestValue && state->role[index] == Zole::Big )
            this->bestChoice = successor->action;
    }
    return bestValue;
}
