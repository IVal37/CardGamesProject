from dataclasses import dataclass
from typing import Dict

from ..models.game_state import GameState
from ..models.game_action import GameAction
from ..models.player import Player

@dataclass
class RoomManager:
    # Attributes
    _room_dict: Dict[int, GameState]
    _next_room_id: int

    # Getters and Setters
    @property
    def room_dict(self):
        return self._room_dict
    
    @room_dict.setter
    def room_dict(self, dict):
        self._room_dict = dict
    
    @property
    def next_room_id(self):
        return self._next_room_id

    @next_room_id.setter
    def next_room_id(self, id):
        self._next_room_id = id
    
    # Constructors
    def __init__(self):
        self.room_dict = {}
        self.next_room_id = 1

    # Room Funcs
    def create_room(self) -> str:
        room_id = self.next_room_id
        self.room_dict[room_id] = GameState()
        self.next_room_id += 1

        return str(room_id)

    def get_room(self, room_id: int) -> GameState:
        return self.room_dict[room_id]

    def delete_room(self, room_id: int) -> None:
        self.room_dict.pop(room_id)
    
    def add_player(self, room_id: int, player: Player):
        pass

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

room_manager = RoomManager()