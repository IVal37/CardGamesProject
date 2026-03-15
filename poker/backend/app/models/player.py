from dataclasses import dataclass
from typing import List

from card import Card
from enums import PlayerState

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
    
    @property.setter
    def name(self, name):
        self._name = name

    @property
    def stack(self):
        return self._stack
    
    def stack(self, stack):
        self._stack = stack

    @property
    def cards(self):
        return self._cards
    
    @property.setter
    def cards(self, cards):
        self._cards = cards

    @property
    def current_bet(self):
        return self._current_bet
    
    @property.setter
    def current_bet(self, curr_bet):
        self._current_bet = curr_bet

    @property
    def state(self):
        return self._state
    
    @property.setter
    def state(self, state):
        self._state = state