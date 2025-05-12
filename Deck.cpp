#include "Deck.h"

#include <iostream>

using namespace std;

char symbols[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char suits[] = {'d', 'c', 'h', 's'};

Deck::Deck(): deckSize(52) {
    for(auto const& suit : suits) {
        for(auto const& symbol : symbols) {
            deck.push_back(Card(symbol, suit));
        }
    }
}

void Deck::Print() {
    for(int i = 0; i < deckSize; i++) {
        deck[i].Print();
    }
    cout << endl;
}

Card Deck::PullCard() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, deckSize - 1);

    int indexToPull = dist(gen);

    Card retCard = deck[indexToPull];
    deck.erase(deck.begin() + indexToPull);
    deckSize--;

    return retCard;
}

vector<Card> Deck::DealHand(int numCards) {
    vector<Card> retVec;

    for(int i = 0; i < numCards; i++) {
        retVec.push_back(PullCard());
    }

    return retVec;
}

void Deck::RandomShuffle() {
    random_device rd;
    mt19937 gen(rd());

    for(int i = deckSize - 1; i > 0; i--) {
        uniform_int_distribution<> dist(0, i);
        int swapNum = dist(gen);

        swap(deck[i], deck[swapNum]);
    }
}

void Deck::RiffleShuffle() {
    
}

void Deck::Cut() {

}
