from dataclasses import dataclass
from typing import List, Dict

from .player import Player
from .card import Card, Deck
from ..core.enums import Street, PlayerState

from ..core.config import MIN_PLAYER_COUNT, MAX_PLAYER_COUNT 

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
    _previous_bet_to_match: int
    _current_bet_to_match: int
    _current_player_index: int
    
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
    def current_player_index(self):
        return self._current_player_index
    
    @current_player_index.setter
    def current_player_index(self, idx):
        self._current_player_index = idx

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
    def previous_bet_to_match(self):
        return self._previous_bet_to_match
    
    @previous_bet_to_match.setter
    def previous_bet_to_match(self, bet):
        self._previous_bet_to_match = bet
    
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
        self.previous_bet_to_match = 0
        self.current_bet_to_match = 0
        self.current_player_index = 2

    # Player Funcs
    def add_player(self, player: Player) -> None:
        if self.num_players >= MAX_PLAYER_COUNT:
            return      #TODO throw error

        #TODO no unusable names

        for iter_player in self.players:
            if player.name == iter_player.name:
                return    #TODO throw error

        self.players.append(player)
        self.num_players += 1
    
    def remove_player(self, name: str) -> bool:
        for index, player in enumerate(self.players):
            # find player to remove
            if player.name == name:
                # active player count logic
                if self.players[index].state == PlayerState.ACTIVE:
                    self.active_player_count -= 1
                    # pause game if not enough players to continue
                    if self.active_player_count < MIN_PLAYER_COUNT:
                        self.toggle_pause()
                
                self.num_players -= 1
                self.players.pop(index)

                return True
        # failed to find player to remove
        return False

    # Round Funcs
    def reset_deck(self) -> None:
        self.deck = Deck()
        self.deck.shuffle()

    # Util funcs
    def toggle_pause(self) -> None:
        self.currently_dealing = not self.currently_dealing

    def next_street(self) -> None:
        order = [
            Street.PRE_FLOP,
            Street.FLOP,
            Street.TURN,
            Street.RIVER,
            Street.SHOWDOWN,
        ]
        self.street = order[(order.index(self.street) + 1) % len(order)]

    def increment_player_index(self) -> None:
        if self.current_player_index == (self.num_players - 1):
                    self.current_player_index = 0
        else:
            self.current_player_index += 1