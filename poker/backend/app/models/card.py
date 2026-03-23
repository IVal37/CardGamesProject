from dataclasses import dataclass
from typing import List
import random

from ..core.enums import Rank, Suit

@dataclass
class Card:
    _rank: Rank
    _suit: Suit

    @property
    def rank(self):
        return self._rank
    
    @rank.setter
    def rank(self, rank):
        self._rank = rank
    
    @property
    def suit(self):
        return self._suit
    
    @suit.setter
    def suit(self, suit):
        self._suit = suit

    def __init__(self, rank, suit):
        self.rank = rank
        self.suit = suit

@dataclass
class Deck:
    _cards: List[Card]

    @property
    def cards(self):
        return self._cards
    
    @cards.setter
    def cards(self, cards):
        self._cards = cards

    def __init__(self):
        self.cards = []
        for suit in Suit:
            for rank in Rank:
                self.cards.append(Card(rank, suit))

    # Util Funcs

    def shuffle(self) -> None:
        random.shuffle(self.cards)

    # Debug Funcs

    #def stack_deck(self) -> None:
        #TODO

    def print(self) -> None:
        for card in self.cards:
            print(f"{card.rank}{card.suit}")

    # Dealing Cards Funcs

    def deal_card(self) -> Card:
        return self.cards.pop()
    