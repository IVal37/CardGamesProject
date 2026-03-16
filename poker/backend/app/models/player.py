from dataclasses import dataclass
from typing import List

from .card import Card
from .enums import PlayerState

@dataclass
class Player:
    _name: str
    _stack: int
    _cards: List[Card]
    _current_bet: int
    _state: PlayerState

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