#include "Util.h"

// Street enum funcs

string StreetToString(Street s) {
    switch(s) {
        case Street::PREROUND:
            return "PREROUND";
        case Street::PREFLOP:
            return "PREFLOP";
        case Street::FLOP:
            return "FLOP";
        case Street::TURN:
            return "TURN";
        case Street::RIVER:
            return "RIVER";
        case Street::SHOWDOWN:
            return "SHOWDOWN";
        default:
            exit(-1);
        }
}

Street NextStreet(Street s) {
    switch(s) {
        case Street::PREROUND:
            return Street::PREFLOP;
        case Street::PREFLOP:
            return Street::FLOP;
        case Street::FLOP:
            return Street::TURN;
        case Street::TURN:
            return Street::RIVER;
        case Street::RIVER:
            return Street::SHOWDOWN;
        case Street::SHOWDOWN:
            return Street::ROUND_END;
        default:
            exit(-2);
        }
}

// Action enum funcs

string ActionToString(Action a) {
    switch(a) {
        case Action::FOLD:
            return "FOLD";
        case Action::CHECK:
            return "CHECK";
        case Action::CALL:
            return "CALL";
        case Action::BET:
            return "BET";
        case Action::RAISE:
            return "RAISE";
        case Action::ALL_IN:
            return "ALL_IN";
        default:
            exit(-1);
    }
}

// HandType enum funcs
string HandTypeToString(HandType h) {
    switch(h) {
        case HandType::HIGH_CARD:
            return "HIGH CARD";
            break;
        case HandType::PAIR:
            return "PAIR";
            break;
        case HandType::TWO_PAIR:
            return "TWO PAIR";
            break;
        case HandType::TRIPS:
            return "TRIPS";
            break;
        case HandType::STRAIGHT:
            return "STRAIGHT";
            break;
        case HandType::FLUSH:
            return "FLUSH";
            break;
        case HandType::FULL_HOUSE:
            return "FULL HOUSE";
            break;
        case HandType::QUADS:
            return "QUADS";
            break;
        case HandType::STRAIGHT_FLUSH:
            return "STRAIGHT FLUSH";
            break;
        default:
            exit(-1);
    }
}

// Position enum funcs
string PositionToString(Position p) {
    switch(p) {
      case Position::SMALL_BLIND:
        return "SB";
      case Position::BIG_BLIND:
        return "BB";
      case Position::UTG:
        return "UTG";
      case Position::UTG_PLUS_ONE:
        return "+1";
        case Position::MIDDLE_POSITION:
        return "MP";
      case Position::LOJACK:
        return "LJ";
        case Position::HIJACK:
        return "HJ";
      case Position::CUTOFF:
        return "CO";
      case Position::BUTTON:
        return "BTN";
      default:
        exit(-9);
    }
  }

// General Util Funcs

void ClearScreen() {
    #if defined(_WIN32) || defined(_WIN64)
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

void UserPauseClear() {
    cout << "Press Enter to continue..." << flush;
    string dummy;
    getline(std::cin, dummy);
    
    ClearScreen();
}

void PrintBreakLine() {
    int screenWidth;

    #if defined(_WIN32)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
            screenWidth = 80;  // fallback
        }
        screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize w;
        if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
            screenWidth = 80; // fallback
        }
        screenWidth = w.ws_col;
    #endif

    std::string line(screenWidth, '-');
    std::cout << line << "\n";
}

void PrintBoardPot(vector<Card> currBoard, int currPot) {
    cout << "{ ";
    for(size_t i = 0; i < 5; i++) {
        if(i < currBoard.size() && !currBoard.empty()) {
            currBoard[i].Print();
            cout << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << "} ";

    if(!(currBoard.empty() && currPot == 0)) {
        cout << " [ " << currPot << " ]";
    }

    cout << endl;
}