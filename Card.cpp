#include "Card.h"

#include <cstdlib>
#include <iostream>

using namespace std;

Card::Card() {}

Card::Card(char sym, char userSuit) : symbol(sym) {
    switch(userSuit) {
        case 's':  suit = u8"♠"; break;
        case 'h':  suit = u8"♥"; break;
        case 'd':  suit = u8"♦"; break;
        case 'c':  suit = u8"♣"; break;
        default:   exit(-1);
    }
}

int Card::GetRank() const {
    if(symbol >= '1' && symbol <= '9') {
        return symbol - '0';
    }
    switch(symbol) {
        case('T'):
            return 10;
            break;
        case('J'):
            return 11;
            break;
        case('Q'):
            return 12;
            break;
        case('K'):
            return 13;
            break;
        case('A'):
            return 14;
            break;
        default:
            exit(-6);
    }

}

string Card::GetSuit() const {
    return suit;
}

void Card::Print() {
    cout << symbol << suit;
}