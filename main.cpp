#include <iostream>

#include "Poker.h"
#include "Deck.h"
#include "Card.h"

using namespace std;

int main(void) {
    setlocale(LC_ALL, "");

    PokerGame game(1, 2);
    game.StartGame();

    return 0;
}