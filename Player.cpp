#include "Player.h"

#include <iostream>

using namespace std;

// Constructors

Player::Player(string name): name(name), handSize(0), stackSize(400), currentBet(0){}

// Utility
void Player::ResetNextStreet() {
    currentBet = 0;
}

void Player::ResetNextRound() {
    ResetNextStreet();

    hand.clear();
}

bool Player::CanAct() {
    return isActive && !isAllIn;
}

// Game Funcs
void Player::DealHand(Deck& currDeck, int numCards) {
    for(int i = 0; i < numCards; i++) {
        hand.push_back(currDeck.PullCard());
    }

    handSize += numCards;
}

void Player::PrintHand() {
    for(size_t i = 0; i < hand.size(); i++) {
        hand[i].Print();
        if(i != hand.size() - 1) {
            cout << ",";
        }
    }
}

int Player::GetBetRaiseSize(int minBet, int increment) {
    PrintBreakLine();

    int bet;
    bool firstPass = true;
    string line;
    do {
        cout << "Please enter a value between " << minBet << " and " << stackSize << ":";
        if(!firstPass) {
            cout << "  [Invalid entry]";
        }
        firstPass = false;
        cout << endl;

        cout << "> ";
        getline(cin, line);

        try {
            bet = stoi(line);
        }
        catch(const invalid_argument& e) {continue;}
        catch(const out_of_range& e) {continue;}
    } while(!(bet >= minBet && bet <= stackSize));

    return ((bet/increment) * increment);   // returns bet in increments of bb
}

Decision Player::GetUserDecision(vector<Action> possibleActions, int minBet, int incr, int currBet, int lastBet, vector<Card> currBoard, int currPot) {
    string line;
    bool firstPass = true;

    do {
        ClearScreen();
        // { board }  [ pot ] 
        PrintBoardPot(currBoard, currPot);
        // ------
        PrintBreakLine();
        // Name(hand)
        cout << GetName() << "(";
        PrintHand();
        cout << ")  [" << currentBet << "]";
        // retry input
        if(!firstPass) {
            cout << "  Invalid entry - please enter 1, 2, or 3.";
        }
        firstPass = false;
        cout << endl;
        // ------
        PrintBreakLine();
        // (x): Action
        for(int i = 0; i < 3; i++) {
            cout << "(" << i + 1 << "): "
                 << ActionToString(possibleActions[i]);
                if(possibleActions[i] == Action::CALL) {
                    cout << " [" << currBet - currentBet << "]";
                }
                if(possibleActions[i] == Action::BET) {
                    cout << " [" << minBet << " - " << stackSize << "]";
                }
                if(possibleActions[i] == Action::RAISE) {
                    cout << " [" << min(currBet + lastBet, stackSize) << " - " << stackSize << "]";
                }
            cout << endl;
        }
        // ------
        PrintBreakLine();
        // > (user input)
        cout << "> ";
        getline(cin, line);
    } while(!(line.size() == 1 && line[0] >= '1' && line[0] <= '3'));

    int actionIndex = line[0] - '1';
    Action chosenAction = possibleActions[actionIndex];
    
    int decisionAmount;
    switch(chosenAction) {
        case(Action::FOLD):
        case(Action::CHECK):
            decisionAmount = 0;
            break;
        case(Action::CALL):
            decisionAmount = currBet;
            break;
        case(Action::BET):
            decisionAmount = GetBetRaiseSize(minBet, incr);
            break;
        case(Action::RAISE):
            decisionAmount = GetBetRaiseSize(currBet + lastBet, incr);
            break;
        default:
            exit(-1);
    }

    return Decision(chosenAction, decisionAmount);
}

void Player::PerformAction(Decision userDecision) {
    if(userDecision.action == Action::FOLD) {
        SetIsActive(false);
    }
    else {
        currentBet += userDecision.amount;
        stackSize -= userDecision.amount;
    }
}

// Setters

void Player::SetName(const string& in) {
    name = in;
}

void Player::SetStackSize(int amount) {
    stackSize = amount;
}

void Player::SetCurrentBet(int bet) {
    currentBet = bet;
}

void Player::SetIsActive(bool status) {
    isActive = status;
}

// Getters

const string& Player::GetName() const {
    return name;
}

vector<Card> Player::GetHand() const {
    return hand;
}

int Player::GetStackSize() const {
    return stackSize;
}

int Player::GetCurrentBet() const {
    return currentBet;
}

bool Player::GetIsActive() const {
    return isActive;
}