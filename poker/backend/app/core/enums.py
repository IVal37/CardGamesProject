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

def str_to_action(input: str) -> Action:
    str = input.lower()
    if str == 'all in':
        return Action.ALL_IN
    elif str == 'raise':
        return Action.RAISE
    elif str == 'call':
        return Action.CALL
    elif str == 'check':
        return Action.CHECK
    elif str == 'fold':
        return Action.FOLD
    else:
        pass

class PlayerState(Enum):
    ALL_IN = 'All-In'
    FOLDED = 'Folded'
    ACTIVE = 'Active'
    AWAY = 'Away'

    def __str__(self):
        return self.name

class Street(Enum):
    PRE_FLOP = 'Pre-flop'
    FLOP = 'Flop'
    TURN = 'Turn'
    RIVER = 'River'
    SHOWDOWN = 'Showdown'

    def __str__(self):
        return self.name