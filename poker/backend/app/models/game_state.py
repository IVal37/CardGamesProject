from dataclasses import dataclass
from typing import List

from player import Player
from card import Card, Deck
from enums import Street

from ..core.config import MAX_PLAYER_COUNT 
@dataclass
class GameState:
    # Attributes
    _players: List[Player]
    _active_player_count: int
    _deck: Deck
    _board: List[Card]
    _street: Street
    _current_bet_to_match: int
    
    # Getters and Setters
    @property
    def players(self):
        return self._players

    @property
    def active_player_count(self):
        return self._active_player_count
    
    @property
    def deck(self):
        return self._deck
    
    @property
    def board(self):
        return self._board
    
    @property
    def street(self):
        return self._street
    
    @property.setter
    def street(self, street):
        self._street = street
    
    @property
    def current_bet_to_match(self):
        return self._current_bet_to_match

    @property.setter
    def current_bet_to_match(self, curr_bet: int):
        self._current_bet_to_match = curr_bet

    # Constructor
    def __init__(self):
        self.players = list[Player]
        self.active_player_count = 0
        self.deck = Deck()
        self.board = list[Card]

    # Util Funcs
    def AddPlayer(self, player: Player) -> None:
        if len(self.players) >= MAX_PLAYER_COUNT:
            return      #TODO throw error

        proposed_name = player.name

        #TODO no unusable names

        for iter_player in self.players:
            if proposed_name == iter_player.name:
                return    #TODO throw error

        self.players.append(player)
        self.active_player_count += 1
    
    def RemovePlayer(self, name: str) -> None:
        # assuming it can only be called if name exists since only called by person removing themselves
        self.players.remove(name)
        self.active_player_count -= 1

    def ResetDeck(self) -> None:
        self.deck = Deck()
        self.deck.shuffle()