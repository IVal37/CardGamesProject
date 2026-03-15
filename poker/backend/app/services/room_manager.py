from dataclasses import dataclass
from typing import Dict

from game_engine import GameState
from models.enums import Action
from models.game_action import GameAction
from models.player import Player

@dataclass
class RoomManager:
    # Attributes
    _next_room_id: int = 1
    _room_dict: Dict[int, GameState]

    # Getters and Setters
    @property
    def next_room_id(self):
        return self._next_room_id
    
    @property
    def room_dict(self):
        return self._room_dict
    
    @property.setter
    def room_dict(self, dict: Dict[int, GameState]):
        self._room_dict = dict

    # Util Funcs
    def create_room(self) -> GameState:
        self.room_dict[self.next_room_id] = GameState()
        self.next_room_id += 1

    def add_player(self, room_id: int, player: Player):
        pass

    def delete_room(self, room_id: int) -> None:
        self.room_dict.pop(room_id)

    def get_room(self, room_id: int) -> GameState:
        return self.room_dict[room_id]

    # Action Funcs
    def apply_action(self, room_id: int, game_action: GameAction) -> None:
        action = game_action.action
        
        if action == 'All-In':
            pass
        elif action == 'Raise':
            pass
        elif action == 'Call':
            pass
        elif action == 'Check':
            pass
        elif action == 'Fold':
            pass
        else:
            pass