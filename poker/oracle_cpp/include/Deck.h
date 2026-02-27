#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "Util.h"
#include <vector>
#include <random>
#include <unordered_map>

using namespace std;

extern char symbols[];
extern char suits[];

class Deck {
    public:
        // Constructors
        Deck();
        Deck(bool stacked);

        // Utility
        void Print();

        // Dealing
        Card PullCard();
        Card PullRandomCard();
        vector<Card> DealHand(int numCards);

        // Shuffling
        void CasinoWash();
        void RiffleShuffle();
        void Cut();

        // Destructors
        ~Deck() = default;
    
    private:
        vector<Card> deck;
};

#endif