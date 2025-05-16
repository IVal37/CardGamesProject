#ifndef POKER_H
#define POKER_H

#include "Deck.h"
#include "Player.h"
#include "Util.h"

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

class PokerGame {
    public:
        // Constructors
        PokerGame(int sb, int bb);

        // Setters
        void SetDeck(const Deck& in);

        // Getters
        const Deck& GetDeck() const;

        // Utility
        void ResetRound();
        void ResetStreet();
        vector<Action> GetPossibleActions(Player p);
        int NumPlayersIn();
        void PrintPlayersInfo(bool handStackMode);
        pair<int, HandStrength> DetermineWinningHand(vector<Card> board, int p1Idx, vector<Card> p1Hand, int p2Idx, vector<Card> p2Hand);
        HandStrength GetBestHand(vector<Card> board, vector<Card> hand);
        void DealStreet(int cardsToDeal);
        int NumToDeal();

        // Game Funcs
        void StartGame();
        void StartRound();
        void StartStreet();
        void RoundAction(Street s);
        void BettingRound();
        int NextPlayerToAct(int playerToAct);
        void ProcessDecision(int playerIdx, Decision d);

        // Street Funcs
        void PreRound(int handNum);
        void Preflop();
        void BettingStreet();
        void Showdown();

        // Destructors
        ~PokerGame() = default;
    private:
        // Game Vars
        vector<Player> players;
        vector<Position> positions;
        int sb;
        int bb;
        int handsPlayed;

        // Round Vars
        Deck deck;
        Street street;
        vector<Card> board;

        // Betting Vars
        int betToMatch;
        int prevBet;
        int pot;
        int lastRaiserIdx;
};

#endif