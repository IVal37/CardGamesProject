#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "Util.h"

#include <vector>

using namespace std;

class Player {
    public:
        // Constructors
        Player(string name);

        // Utility
        void ResetNextStreet();
        void ResetNextRound();
        bool CanAct();

        // Game funcs
        void DealHand(Deck& currDeck, int numCards);
        void PrintHand();
        int GetBetRaiseSize(int minBet, int increment);
        Decision GetUserDecision(vector<Action> possibleActions, int minBet, int incr, int currBet, int lastBet, vector<Card> currBoard, int currPot);

        // Setters
        void SetName(const string& in);
        void SetPosition(Position p);
        void SetStackSize(int amount);
        void SetCurrentBet(int bet);
        void SetIsActive(bool status);
        void SetIsAllIn(bool status);

        // Getters
        const string& GetName() const;
        vector<Card> GetHand() const;
        Position GetPosition() const;
        int GetStackSize() const;
        int GetCurrentBet() const;
        bool GetIsActive() const;
        bool GetIsAllIn() const;

        // Destructors
        ~Player() = default;

    private:
        string name;
        vector<Card> hand;
        Position position;
        int handSize;
        int stackSize;
        int currentBet;
        bool isActive;
        bool isAllIn;
};

#endif