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

#ifndef MAIN_H
#define MAIN_H

//
// includes
//
#include <iostream>
#include <vector>

//
// defines
//
//#define FORCE_DEBUG

//
// namespace: Zole
//
namespace Zole {

/**
 * @brief Cards total amount of cards in the game
 */
const static unsigned short NumCards = 26;

/**
 * @brief Table maximum cards on the table
 */
const static unsigned short Table = 2;

/**
 * @brief PlayerCards starting amount of cards per player
 */
const static unsigned short PlayerCards = 8;


/**
 * @brief Players maximum players
 */
const static unsigned short Players = 3;

/**
 * @brief OpposingTeams number of opposing teams - BIG vs SMALL
 */
const static unsigned short OpposingTeams = 2;


/**
 * @brief The Suits enum card suits
 */
enum Suits {
    NoSuit = -1,
    Clubs = 0,
    Spades,
    Hearts,
    Thrumps
};

/**
 * @brief The Faces enum card faces
 */
enum Faces {
    NoFace = -1,
    Queen = 0,
    Jack,
    King,
    Ace,
    Ten,
    Nine,
    Eight,
    Seven
};

/**
 * @brief The CardTable struct general structure of a card entry
 */
struct CardTable {
    Zole::Faces face;
    Zole::Suits suit;
    int strength;
    int points;
    const char *symbol;
};

/**
 * @brief The Roles enum player roles, either BIG or SMALL
 */
enum Roles {
    Small,
    Big = 1
};

static const CardTable Cards[Zole::NumCards] = {
    // thrumps
    { Zole::Queen,  Zole::Thrumps,  0,   3,  "CQ" },
    { Zole::Queen,  Zole::Thrumps,  1,   3,  "SQ" },
    { Zole::Queen,  Zole::Thrumps,  2,   3,  "HQ" },
    { Zole::Queen,  Zole::Thrumps,  3,   3,  "DQ" },
    { Zole::Jack,   Zole::Thrumps,  4,   2,  "CJ" },
    { Zole::Jack,   Zole::Thrumps,  5,   2,  "SJ" },
    { Zole::Jack,   Zole::Thrumps,  6,   2,  "HJ" },
    { Zole::Jack,   Zole::Thrumps,  7,   2,  "DJ" },
    { Zole::Ace,    Zole::Thrumps,  8,   11, "DA" },
    { Zole::Ten,    Zole::Thrumps,  9,   10, "DT" },
    { Zole::King,   Zole::Thrumps,  10,  4,  "DK" },
    { Zole::Nine,   Zole::Thrumps,  11,  0,  "D9" },
    { Zole::Eight,  Zole::Thrumps,  12,  0,  "D8" },
    { Zole::Seven,  Zole::Thrumps,  13,  0,  "D7" },

    // leftovers
    { Zole::Ace,    Zole::Clubs,    14,  11, "CA" },
    { Zole::Ten,    Zole::Clubs,    15,  10, "CT" },
    { Zole::King,   Zole::Clubs,    16,  4,  "CK" },
    { Zole::Nine,   Zole::Clubs,    17,  0,  "C9" },
    { Zole::Ace,    Zole::Spades,   14,  11, "SA" },
    { Zole::Ten,    Zole::Spades,   15,  10, "ST" },
    { Zole::King,   Zole::Spades,   16,  4,  "SK" },
    { Zole::Nine,   Zole::Spades,   17,  0,  "S9" },
    { Zole::Ace,    Zole::Hearts,   14,  11, "HA" },
    { Zole::Ten,    Zole::Hearts,   15,  10, "HT" },
    { Zole::King,   Zole::Hearts,   16,  4,  "HK" },
    { Zole::Nine,   Zole::Hearts,   17,  0,  "H9" },
};

/**
 * @brief symbol returns the corresponding ASCII symbol of the card
 * @param index card index in the cardTable
 * @return corresponding symbol
 */
static const char *symbol( int index ) { return Zole::Cards[index].symbol; }

/**
 * @brief suit
 * @param index card index in the cardTable
 * @return corresponding suit
 */
static Suits suit( int index ) { return Zole::Cards[index].suit; }

/**
 * @brief strength
 * @param index card index in the cardTable
 * @return corresponding strength
 */
static int strength( int index ) { return Zole::Cards[index].strength; }

/**
 * @brief points
 * @param index card index in the cardTable
 * @return corresponding points
 */
static int points( int index ) { return Zole::Cards[index].points; }
}

#endif // MAIN_H
