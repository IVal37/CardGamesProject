#include "Deck.h"

#include <iostream>
#include <algorithm>

using namespace std;

char symbols[] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char suits[] = {'d', 'c', 'h', 's'};

Deck::Deck() {
    for(auto const& suit : suits) {
        for(auto const& symbol : symbols) {
            deck.push_back(Card(symbol, suit));
        }
    }
}

Deck::Deck(bool stacked) {
    ClearScreen();

    if(!stacked) {
        exit(15);
    }

    int numHandsToStack;
    cout << "How many hands would you like to stack?" << endl << "> ";
    cin >> numHandsToStack;

    vector<vector<Card>> hands;

    for(int i = 1; i <= numHandsToStack; i++) {
        cout << "Enter hand " << i << ": " << endl;
        vector<Card> tempHand;

        for(int j = 1; j <= 2; j++) {
            cout << "\tCard " << j << ":" << endl;

            char tempSymbol;
            cout << "\t\tSymbol:" << endl << "\t\t> ";
            cin >> tempSymbol;
            
            char tempSuit;
            cout << "\t\tSuit:" << endl << "\t\t> ";
            cin >> tempSuit;
    
            tempHand.push_back(Card(tempSymbol, tempSuit));
        }

        hands.push_back(tempHand);
    }

    vector<Card> seen;
    for(auto const& hand : hands) {
        for(int i = 0; i < 2; i++) {
            seen.push_back(hand[i]);
        }
    }

    for(auto const& suit : suits) {
        for(auto const& symbol : symbols) {
            Card tempCard = Card(symbol, suit);
            if(find(seen.begin(), seen.end(), tempCard) == seen.end()) {
                deck.push_back(Card(symbol, suit));
            }
        }
    }

    CasinoWash();

    for(auto const& hand : hands) {
        for(int i = 0; i < 2; i++) {
            deck.push_back(hand[i]);
        }
    }
}

void Deck::Print() {
    for(size_t i = 0; i < deck.size(); i++) {
        deck[(int)i].Print();
    }
    cout << endl;
}

Card Deck::PullCard() {
    Card c = deck.back();
    deck.pop_back();
    return c;
}

Card Deck::PullRandomCard() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, (int)deck.size() - 1);

    int indexToPull = dist(gen);

    Card retCard = deck[indexToPull];
    deck.erase(deck.begin() + indexToPull);

    return retCard;
}

vector<Card> Deck::DealHand(int numCards) {
    vector<Card> retVec;

    for(int i = 0; i < numCards; i++) {
        retVec.push_back(PullCard());
    }

    return retVec;
}

void Deck::CasinoWash() {
    random_device rd;
    mt19937 gen(rd());

    for(int i = (int)deck.size() - 1; i > 0; i--) {
        uniform_int_distribution<> dist(0, i);
        int swapNum = dist(gen);

        swap(deck[i], deck[swapNum]);
    }
}

void Deck::RiffleShuffle() {
    //TODO
}

void Deck::Cut() {
    //TODO
}
