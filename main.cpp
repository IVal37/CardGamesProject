#include <iostream>

#include "Poker.h"
#include "Deck.h"
#include "Card.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    PokerGame game(1, 2);
    // add functionality to choose game size
    // maybe have this be PokerGame game() and choose sb, bb in PokerGame constructor
    game.StartGame();

    return 0;
}