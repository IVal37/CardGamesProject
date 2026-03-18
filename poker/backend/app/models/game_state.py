from dataclasses import dataclass
from typing import List, Dict

from .player import Player
from .card import Card, Deck
from .enums import Street

from ..core.config import MAX_PLAYER_COUNT 

@dataclass
class GameState:
    # Attributes
    _players: List[Player]
    _num_players: int
    _currently_dealing: bool
    _deck: Deck
    _street: Street
    _board: List[Card]
    _pot: int
    _current_bet_to_match: int
    
    # Getters and Setters
    @property
    def players(self):
        return self._players
    
    @players.setter
    def players(self, list):
        self._players = list

    @property
    def num_players(self):
        return self._num_players
    
    @num_players.setter
    def num_players(self, num):
        self._num_players = num

    @property
    def currently_dealing(self):
        return self._currently_dealing
    
    @currently_dealing.setter
    def currently_dealing(self, is_dealing):
        self._currently_dealing = is_dealing

    @property
    def deck(self):
        return self._deck
    
    @deck.setter
    def deck(self, deck):
        self._deck = deck

    @property
    def street(self):
        return self._street
    
    @street.setter
    def street(self, street):
        self._street = street

    @property
    def board(self):
        return self._board
    
    @board.setter
    def board(self, board):
        self._board = board

    @property
    def pot(self):
        return self._pot
    
    @pot.setter
    def pot(self, pot):
        self._pot = pot
    
    @property
    def current_bet_to_match(self):
        return self._current_bet_to_match

    @current_bet_to_match.setter
    def current_bet_to_match(self, curr_bet: int):
        self._current_bet_to_match = curr_bet

    # Constructor
    def __init__(self):
        self.players = list()
        self.num_players = 0
        self.active_player_count = 0
        self.currently_dealing = False
        self.deck = Deck()
        self.board = list()
        self.street = Street.PRE_FLOP
        self.pot = 0
        self.current_bet_to_match = 0

    # Player Funcs
    def add_player(self, player: Player) -> None:
        if self.num_players >= MAX_PLAYER_COUNT:
            return      #TODO throw error

        proposed_name = player.name

        #TODO no unusable names

        for iter_player in self.players:
            if proposed_name == iter_player.name:
                return    #TODO throw error

        self.players.append(player)
        self.num_players += 1
    
    def remove_player(self, name: str) -> bool:
        for index, player in enumerate(self.players):
            if player.name == name:
                self.players.pop(index)
                self.num_players -= 1
                return True
        return False

    # Round Funcs
    def reset_deck(self) -> None:
        self.deck = Deck()
        self.deck.shuffle()

    # Actions
    def make_bet(self, player_name: str, amount: int) -> None:
        for index, player in enumerate(self.players):
            if player.name == player_name:
                self.players[index].make_bet(amount)
                if amount > self.current_bet_to_match:
                    self.current_bet_to_match = amount
                return
        
    def make_bet(self, player_index: int, amount: int) -> None:
        if player_index < self.num_players:
            amount_bet: int = self.players[player_index].make_bet(amount)
            if amount_bet > self.current_bet_to_match:
                self.current_bet_to_match = amount_bet
            return
        