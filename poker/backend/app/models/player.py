from dataclasses import dataclass
from typing import List

from .card import Card
from ..core.enums import PlayerState

@dataclass
class Player:
    # Attributes
    _name: str
    _stack: int
    _cards: List[Card]
    _current_bet: int
    _state: PlayerState
    _has_acted: bool

    # Getters and Setters
    @property
    def name(self):
        return self._name
    
    @name.setter
    def name(self, name):
        self._name = name

    @property
    def stack(self):
        return self._stack
    
    @stack.setter
    def stack(self, stack):
        self._stack = stack

    @property
    def cards(self):
        return self._cards
    
    @cards.setter
    def cards(self, cards):
        self._cards = cards

    @property
    def current_bet(self):
        return self._current_bet
    
    @current_bet.setter
    def current_bet(self, curr_bet):
        self._current_bet = curr_bet

    @property
    def state(self):
        return self._state
    
    @state.setter
    def state(self, state):
        self._state = state

    @property
    def has_acted(self):
        return self._has_acted
    
    @has_acted.setter
    def has_acted(self, has_acted):
        self._has_acted = has_acted

    # Constructors
    def __init__(self, name: str, stack: int):
        self.name = name
        self.stack = stack
        self.cards = []
        self.current_bet = 0
        self.state = PlayerState.ACTIVE
        self.has_acted = False