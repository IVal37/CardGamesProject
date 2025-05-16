#ifndef UTIL_H
#define UTIL_H

#include "Card.h"

#include <string>
#include <iostream>
#include <limits>
#include <vector>

#if defined(_WIN32)
  #include <windows.h>
#else
  #include <sys/ioctl.h>
  #include <unistd.h>
#endif

using namespace std;

// Street enum

enum class Street {
  PREROUND,
  PREFLOP,
  FLOP,
  TURN,
  RIVER,
  SHOWDOWN,
  ROUND_END
};

string StreetToString(Street s);
Street NextStreet(Street s);

// Aciton enum

enum class Action {
    FOLD,
    CHECK,
    CALL,
    BET,
    RAISE,
    ALL_IN
};

string ActionToString(Action a);

// Decision struct

struct Decision {
    Action action;
    int amount;

    Decision(Action inputAction, int inputAmount): action(inputAction), amount(inputAmount) {}
};

// HandType enum

enum class HandType {
  HIGH_CARD = 0,
  PAIR = 1,
  TWO_PAIR = 2,
  TRIPS = 3,
  STRAIGHT = 4,
  FLUSH = 5,
  FULL_HOUSE = 6,
  QUADS = 7,
  STRAIGHT_FLUSH = 8,
  ROYAL_FLUSH = 9
};

string HandTypeToString(HandType h);

inline bool operator<(Action a, Action b) {
  return static_cast<int>(a) < static_cast<int>(b);
}

inline bool operator>(Action a, Action b) {
  return static_cast<int>(a) > static_cast<int>(b);
}

// HandStrength struct

struct HandStrength {
  HandType type = HandType::HIGH_CARD;
  vector<int> kickers;

  // Constructors
  HandStrength() {}
  HandStrength(HandType inputType, vector<int> inputKickers): type(inputType), kickers(inputKickers) {}

  // operator overloading
  bool operator<(HandStrength const &other) {
    if(type != other.type) {
      return type < other.type;
    }
    return kickers < other.kickers;
  }

  bool operator==(HandStrength const &other) {
    return type == other.type && kickers == other.kickers;
  }

  bool operator!=(HandStrength const &other) {
    return !(*this == other);
  }
};

enum class Position {
  SMALL_BLIND = 0,
  BIG_BLIND = 1,
  UTG = 2,
  UTG_PLUS_ONE = 3,
  MIDDLE_POSITION = 4,
  LOJACK = 5,
  HIJACK = 6,
  CUTOFF = 7,
  BUTTON = 8,
};

string PositionToString(Position p);
Position NextPosition(Position p);

// General util
void ClearScreen();
void UserPauseClear();
void PrintBreakLine();
void PrintBoardPot(vector<Card> currBoard, int currPot);

#endif