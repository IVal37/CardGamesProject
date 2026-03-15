from enum import Enum

class Rank(Enum):
    'A' = 1
    '2' = 2
    '3' = 3
    '4' = 4
    '5' = 5
    '6' = 6
    '7' = 7
    '8' = 8
    '9' = 9
    'T' = 10
    'J' = 11
    'Q' = 12
    'K' = 13

class Suit(Enum):
    's'
    'c'
    'h'
    'd'

class Action(Enum):
    'All-In'
    'Raise'
    'Call'
    'Check'
    'Fold'