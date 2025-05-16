#include "Poker.h"

PokerGame::PokerGame(int sb, int bb) : sb(sb), bb(bb), handsPlayed(0) {  
    string testNames[] = {"Izaak", "Ethan", "Andrew", "Adam", "Joon", "Jaxon"};
    //numPlayers = 26;
    //string testNames[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    //numPlayers = 2;
    //string testNames[] = {"Izaak", "Michelle"};
    /*
    cout << "How many players?" << endl;
    int tempNum;
    cin >> tempNum;
    numPlayers = tempNum;
    cout << "Fill in the player names." << endl;
    string tempStr;
    cout << numPlayers << endl;
    for(int i = 1; i <= numPlayers; i++) {
        cout << "Name of player " << i << ": ";
        cin >> tempStr;
        players.push_back(Player(tempStr));
    }
    */

    for(const auto& name : testNames) {
        players.push_back(Player(name));
    }

    int numPlayers = (int)players.size();

    positions.reserve(numPlayers);

    positions.push_back(Position::SMALL_BLIND);
    positions.push_back(Position::BIG_BLIND);
    if(numPlayers >= 3) {positions.push_back(Position::UTG);}
    if(numPlayers >= 9) {positions.push_back(Position::UTG_PLUS_ONE);}
    if(numPlayers >= 6) {positions.push_back(Position::MIDDLE_POSITION);}
    if(numPlayers >= 8) {positions.push_back(Position::LOJACK);}
    if(numPlayers >= 7) {positions.push_back(Position::HIJACK);}
    if(numPlayers >= 5) {positions.push_back(Position::CUTOFF);}
    if(numPlayers >= 4) {positions.push_back(Position::BUTTON);}
    
    for(int i = 0; i < numPlayers; i++) {
        players[i].SetPosition(positions[i]);
    }
}

// Getters

void PokerGame::SetDeck(const Deck& in) {
    deck = in;
}

// Setters

const Deck& PokerGame::GetDeck() const {
    return deck;
}

// Utility

void PokerGame::ResetRound() {
    ResetStreet();

    for(auto& p : players) {
        p.ResetNextRound();
    }

    board.clear();
    pot = 0;

    deck = Deck();
    deck.CasinoWash();
}

void PokerGame::ResetStreet() {
    betToMatch = 0;
    prevBet = 0;
    lastRaiserIdx = -1;

    for(auto& p : players) {
        p.ResetNextStreet();
    }
}

vector<Action> PokerGame::GetPossibleActions(Player p) {
    int haveIn = p.GetCurrentBet();
    int stack = p.GetStackSize();
    int toCall = betToMatch - haveIn;
    int minBet = bb;
    int minRaise = (betToMatch != 0) ? betToMatch - prevBet : betToMatch;

    if(toCall >= stack) {
        return {Action::FOLD, Action::ALL_IN};
    }

    if(toCall == 0 && stack <= minBet) {
        return {Action::FOLD, Action::CHECK, Action::ALL_IN};
    }

    if(betToMatch == haveIn) {
        return {Action::FOLD, Action::CHECK, Action::BET};
    }

    if(stack > toCall) {
        int surplus = stack - toCall;

        if(surplus >= minRaise) {
            return {Action::FOLD, Action::CALL, Action::RAISE};
        }
        else {
            return {Action::FOLD, Action::CALL, Action::ALL_IN};
        }
    }

    assert(false && "GetPossibleActions: unhandled state");
    return { Action::FOLD }; 
}

int PokerGame::NumPlayersIn() {
    int retNum = 0;
    for(const auto& player : players) {
        if(player.GetIsActive()) {
            retNum++;
        }
    }
    return retNum;
}

void PokerGame::PrintPlayersInfo(bool handStackMode) {
    int longestName = -1;
    for(const auto& player : players) {
        if((int)player.GetName().length() > longestName) {
            longestName = player.GetName().length();
        }
    }

    int longestPosition = (int)players.size() <= 2 ? 2 : 3;
    int longestLen = longestName;
    if(handStackMode) {
        longestLen += longestPosition;
    } 

    for(int i = 0; i < (int)players.size(); i++) {
        if(players[i].GetIsActive() || !handStackMode) {
            // name
            cout << players[i].GetName();
            // (position)
            if(handStackMode) {
                cout << "(" << PositionToString(players[i].GetPosition()) << ")";
            }
            // :
            cout << ":";
            // whitespace padding
            int toPad = (int)players[i].GetName().length();
            if(handStackMode) {
                toPad += (int)PositionToString(players[i].GetPosition()).length();
            }

            for(int j = 0; j <= longestLen - toPad; j++) {
                cout << " ";
            }
            // (hand)
            if(handStackMode) {
                cout << "{";
                players[i].PrintHand();
                cout << "} ";
            }
            
            cout << "[" << players[i].GetStackSize() << "]" << endl;
        }
    }
}

pair<int, HandStrength> PokerGame::DetermineWinningHand(vector<Card> board, int p1Idx, vector<Card> p1Hand, int p2Idx, vector<Card> p2Hand) {
    HandStrength p1Best = GetBestHand(board, p1Hand);
    HandStrength p2Best = GetBestHand(board, p2Hand);

    // p1 hand > p2 hand
    if(static_cast<int>(p1Best.type) > static_cast<int>(p2Best.type)) {
        return pair<int, HandStrength>(p1Idx, p1Best);
    }
    // p1 hand < p2 hand
    else if(static_cast<int>(p1Best.type) < static_cast<int>(p2Best.type)) {
        return pair<int, HandStrength>(p2Idx, p2Best);
    }
    // p1 hand = p2 hand
    else {
        // check kickers for one winner or two
        if(p1Best.kickers > p2Best.kickers) {
            return pair<int, HandStrength>(p1Idx, p1Best);
        }
        return pair<int, HandStrength>(p2Idx, p2Best);
    }
    
}

HandStrength PokerGame::GetBestHand(vector<Card> board, vector<Card> hand) {
    if(board.empty()) {
        int firstCardRank = hand[0].GetRank();
        int secondCardRank = hand[1].GetRank();
        
        vector<int> rankRetVec = {firstCardRank, secondCardRank};

        if(firstCardRank == secondCardRank) {
            return HandStrength(HandType::PAIR, rankRetVec);
        }
        return HandStrength(HandType::HIGH_CARD, rankRetVec);
    }

    // cards -> vec size 7 with hand + board cards
    vector<Card> cards;
    cards.reserve(board.size() + hand.size());
    cards.insert(cards.end(), hand.begin(), hand.end());
    cards.insert(cards.end(), board.begin(), board.end());
    sort(cards.begin(), cards.end(), [](const Card &a, const Card &b) {
        return a.GetRank() > b.GetRank();
    });

    // rankCount -> map with instances of each rank
    // suitCount -> map with instances of each suit
    unordered_map<int, int> rankCount;
    unordered_map<string, int> suitCount;

    // populate maps and vec
    for(auto& card : cards) {
        rankCount[card.GetRank()]++;
        suitCount[card.GetSuit()]++;
    }
    
    // check for flush
    string flushSuit = "";
    for(const auto& kv : suitCount) {
        if(kv.second >= 5) {
            flushSuit = kv.first;
            break;
        }
    }

    // check for straight
    bool rankExists[15] = {false};
    for(auto& val : rankCount) {
        rankExists[val.first] = true;
    }
    if(rankExists[14]) {rankExists[1] = true;}

    int bestStraightHighCard = 0;
    for (int start = 10; start >= 1; --start) {
        bool isSeq = true;
        for (int offset = 0; offset < 5; ++offset) {
            if (!rankExists[start + offset]) {
                isSeq = false;
                break;
            }
        }
        if (isSeq) {
            bestStraightHighCard = start + 4;
            break;
        }
    }

    // check for pairs, trips, quads
    vector<int> pairs;
    vector<int> trips;
    int quads = 0;

    for(const auto& kv : rankCount) {
        switch(kv.second) {
            case(4):
                quads = kv.first;
                break;
            case(3):
                trips.push_back(kv.first);
                break;
            case(2):
                pairs.push_back(kv.first);
                break;
        }
    }
    sort(trips.begin(), trips.end(), greater<int>());
    sort(pairs.begin(), pairs.end(), greater<int>());

    // return vals to be filled
    HandType retType;
    vector<int> kickerRetVec;

    // Straight Flush
    if(flushSuit != "" && bestStraightHighCard) {
        retType = HandType::STRAIGHT_FLUSH;

        // kickers
    }
    // Quads
    else if(quads) {
        retType = HandType::QUADS;

        for(int i = 0; i < 4; i++) {
            kickerRetVec.push_back(quads);
        }
        for(size_t i = 0; i < cards.size() - 1; i++) {
            if(cards[i].GetRank() != quads) {
                kickerRetVec.push_back(cards[i].GetRank());
                break;
            }
        }
    }
    // Full House
    else if(!trips.empty() && !pairs.empty()) {
        retType = HandType::FULL_HOUSE;
        
        int usedTrips = trips[0];
        int usedPair = pairs[0]; 

        for(int i = 0; i < 3; i++) {
            kickerRetVec.push_back(usedTrips);
        }
        for(int i = 0; i < 2; i++) {
            kickerRetVec.push_back(usedPair);
        }
    }
    //Flush
    else if(flushSuit != "") {
        retType = HandType::FLUSH;

        for(auto& c : cards) {
            if(c.GetSuit() == flushSuit) {
                kickerRetVec.push_back(c.GetRank());
            }
        }
                
        while(kickerRetVec.size() > 5) {
            kickerRetVec.pop_back();
        }
    }
    //Straight
    else if(bestStraightHighCard) {
        retType = HandType::STRAIGHT;

        for(int i = bestStraightHighCard; i > bestStraightHighCard - 5; i--) {
            kickerRetVec.push_back(i);
        }
    }
    // Trips
    else if(!trips.empty()) {
        retType = HandType::TRIPS;

        int usedTrips = trips[0];

        for(int i = 0; i < 3; i++) {
            kickerRetVec.push_back(usedTrips);
        }

        for(size_t i = 0; i < cards.size() - 1; i++) {
            if(cards[i].GetRank() != usedTrips) {
                kickerRetVec.push_back(cards[i].GetRank());
                if(kickerRetVec.size() == 5) {break;}
            }
        }
    }
    // Two Pair
    else if(pairs.size() >= 2) {
        retType = HandType::TWO_PAIR;

        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                kickerRetVec.push_back(pairs[i]);
            }
        }

        for(size_t i = 0; i < cards.size() - 1; i++) {
            if(cards[i].GetRank() != pairs[0] && cards[i].GetRank() != pairs[1]) {
                kickerRetVec.push_back(cards[i].GetRank());
                break;
            }
        }
    }
    // Pair
    else if(pairs.size() == 1) {
        retType = HandType::PAIR;

        for(int i = 0; i < 2; i++) {
            kickerRetVec.push_back(pairs[0]);
        }

        for(size_t i = 0; i < cards.size() - 1; i++) {
            if(cards[i].GetRank() != pairs[0]) {
                kickerRetVec.push_back(cards[i].GetRank());
                if(kickerRetVec.size() >= 5) {break;}
            }
        }
    }
    // High Card
    else {
        retType = HandType::HIGH_CARD;

        for(int i = 0; i < 5; i++) {
                kickerRetVec.push_back(cards[i].GetRank());
        }
    }


    return(HandStrength(retType, kickerRetVec));
}

void PokerGame::DealStreet(int cardsToDeal) {
    for(int i = 0; i < cardsToDeal; i++) {
        board.push_back(deck.PullCard());
    }
}

int PokerGame::NumToDeal() {
    if(street == Street::FLOP) {
        return 3;
    }
    if(street == Street::TURN || street == Street::RIVER) {
        return 1;
    }

    return 0;
}

// Game Funcs
void PokerGame::StartGame() {
    while(1) {
        ResetRound();
        handsPlayed++;
        StartRound();
    }
    // loop startround
    // reset round
    // check if anyones stack is 0 to rebuy
    // maybe input how many hands to be played
    // or have a default number of hands to ask if want to keep playing after
    // add a ledger
}

void PokerGame::StartRound() {
    for(auto& player : players) {
        player.DealHand(deck, 2);
        player.SetIsActive(true);
    }

    street = Street::PREROUND;
    do {
        ResetStreet();
        StartStreet();
    } while(street != Street::ROUND_END);

    ResetRound();
}

void PokerGame::StartStreet() {
    if(street != Street::PREROUND) {
        ClearScreen();
        if(street != Street::SHOWDOWN) {
            // deal street
            DealStreet(NumToDeal());
            // print street name at top
            cout << StreetToString(street) << "  ";
            // { board }  [ pot ]
            PrintBoardPot(board, pot);
            // ------
            PrintBreakLine();
            // Player (x): (name)(hand)
            PrintPlayersInfo(true);
            // ------
            PrintBreakLine();
            // wait for user to press enter
            UserPauseClear();
        }
    }
    // execute street
    RoundAction(street);
}

void PokerGame::RoundAction(Street s) {
    switch(s) {
        case Street::PREROUND:
            PreRound(handsPlayed);
            break;
        case Street::PREFLOP:
            Preflop();
            break;
        case Street::FLOP:
            BettingStreet();
            break;
        case Street::TURN:
            BettingStreet();
            break;
        case Street::RIVER:
            BettingStreet();
            break;
        case Street::SHOWDOWN:
            Showdown();
            break;
        default:
            exit(-3);
        }
}

void PokerGame::BettingRound() {
    int playerToAct = (street == Street::PREFLOP) ? 2 : 0;
    do {
        if(players[playerToAct].CanAct()) {
            vector<Action> PossibleActions = GetPossibleActions(players[playerToAct]);
            Decision userDecision = players[playerToAct].GetUserDecision(PossibleActions, bb, sb, betToMatch, prevBet, board, pot);
            ProcessDecision(playerToAct, userDecision);
        }

        playerToAct = NextPlayerToAct(playerToAct);
    } while(lastRaiserIdx != playerToAct && NumPlayersIn() > 1);

    if(NumPlayersIn() <= 1) {
        street = Street::SHOWDOWN;
    }
    else {
        street = NextStreet(street);
    }
}

int PokerGame::NextPlayerToAct(int currPlayerNum) {
    if(currPlayerNum == (int)players.size() - 1) {
        return 0;
    }
    else {
        return currPlayerNum + 1;
    }
}

void PokerGame::ProcessDecision(int playerIdx, Decision d) {
    Player &p = players[playerIdx];
    
    if(d.action != Action::FOLD && d.action != Action::CHECK) {
        int modBet = d.amount;
        p.SetCurrentBet(p.GetCurrentBet() + modBet);
        p.SetStackSize(p.GetStackSize() - modBet);
        pot += modBet;
    }

    switch(d.action) {
        case Action::FOLD:
            p.SetIsActive(false);
            break;
        case Action::CHECK:
        case Action::CALL:
            break;
        case Action::BET:
        case Action::RAISE:
            prevBet = (betToMatch != 0) ? betToMatch : d.amount;
            betToMatch = p.GetCurrentBet();

            lastRaiserIdx = playerIdx;
            break;
        case Action::ALL_IN:
            if (p.GetCurrentBet() > betToMatch) {
                prevBet = p.GetCurrentBet() - (betToMatch);
                betToMatch    = p.GetCurrentBet();

                lastRaiserIdx = playerIdx;
            }

            p.SetIsAllIn(true);
            break;
    }
}

// Street Funcs

void PokerGame::PreRound(int handNum) {
    ClearScreen();
    // print street name at top
    cout << "Starting Hand " << handNum << endl;
    street = NextStreet(street);
    // ------
    PrintBreakLine();
    // print players stack size
    PrintPlayersInfo(false);
    // ------
    PrintBreakLine();
    // wait for user to continue
    UserPauseClear();

}

void PokerGame::Preflop() {
    ProcessDecision(0, Decision(Action::BET, sb));
    ProcessDecision(1, Decision(Action::RAISE, bb));
    
    lastRaiserIdx = 2;
    BettingRound();
} 

void PokerGame::BettingStreet() {
    lastRaiserIdx = (street == Street::PREFLOP) ? 2 : 0;
    BettingRound();
}

void PokerGame::Showdown() {
    vector<int> winnerVec;
    HandStrength bestHandStrength;

    if(NumPlayersIn() == 1) {
        for(size_t i = 0; i < players.size(); i++) {
            if(players[i].GetIsActive()) {
                winnerVec.push_back(i);
                bestHandStrength = GetBestHand(board, players[i].GetHand());
                break;
            }
        }
    }
    else {
        bool firstLoop = true;

        for(size_t i = 0; i < players.size(); i++) {
            if(!players[i].GetIsActive()) {
                continue;
            }

            HandStrength tempStrength = GetBestHand(board, players[i].GetHand());

            if(firstLoop) {
                bestHandStrength = tempStrength;
                winnerVec = { (int)i };
                firstLoop = false;
            }
            else if(bestHandStrength < tempStrength) {
                bestHandStrength = tempStrength;
                winnerVec = { (int)i };
            }
            else if(bestHandStrength == tempStrength) {
                winnerVec.push_back((int)i);
            }
            //else
                //leave winnerVec same
        }
    }
    

    if(winnerVec.size() == (int)1) {
        cout << "Winner is: " << players[winnerVec[0]].GetName() << endl;
    }
    else {
        cout << "Winners are: " << endl;
        for(size_t i = 0; i < winnerVec.size(); i++) {
            cout << "\t" << players[winnerVec[i]].GetName() << endl;
        }
    }
    cout << "Hand type: " << HandTypeToString(bestHandStrength.type) << endl;

    int chopPotToWin = pot / (int)winnerVec.size();;
    int chopPotLeftover = pot % (int)winnerVec.size();;
    for(size_t i = 0; i < winnerVec.size(); i++) {
        int toWin = chopPotToWin + ((int)i < chopPotLeftover ? 1 : 0);
        Player &p = players[winnerVec[(int)i]];
        p.SetStackSize(p.GetStackSize() + toWin);
    }

    street = NextStreet(street);

    PrintBreakLine();
    PrintPlayersInfo(false);
    UserPauseClear();
}
