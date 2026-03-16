from enum import Enum, auto

class Rank(Enum):
    ACE = auto()
    TWO = auto()
    THREE = auto()
    FOUR = auto()
    FIVE = auto()
    SIX = auto()
    SEVEN = auto()
    EIGHT = auto()
    NINE = auto()
    TEN = auto()
    JACK = auto()
    QUEEN = auto()
    KING = auto()

class Suit(Enum):
    SPADES = auto()
    CLUBS = auto()
    HEARTS = auto()
    DIAMONDS = auto()

class Action(Enum):
    ALL_IN = auto()
    RAISE = auto()
    CALL = auto()
    CHECK = auto()
    FOLD = auto()

class PlayerState(Enum):
    ALL_IN = auto()
    FOLDED = auto()
    ACTIVE = auto()
    AWAY = auto()

class Street(Enum):
    PRE_FLOP = auto()
    FLOP = auto()
    TURN = auto()
    RIVER = auto()
    SHOWDOWN = auto()