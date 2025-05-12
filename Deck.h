#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>

using namespace std;

extern char symbols[];
extern char suits[];

class Deck {
    public:
        // Constructors
        Deck();

        // Utility
        void Print();

        // Dealing
        Card PullCard();
        vector<Card> DealHand(int numCards);

        // Shuffling
        void RandomShuffle();
        void RiffleShuffle();
        void Cut();

        // Destructors
        ~Deck() = default;
    
    private:
        vector<Card> deck;
        int deckSize;
};

#endif