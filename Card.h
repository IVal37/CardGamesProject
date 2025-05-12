#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

class Card {
    public:
        // Constructors
        Card();
        Card(char sym, char userSuit);

        // Utility
        void Print();

        // Getters
        int GetRank() const;
        string GetSuit() const;

        // Destructors
        ~Card() = default;
    
    private:
        char symbol;
        string suit;
};

#endif