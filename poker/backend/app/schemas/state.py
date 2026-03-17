from pydantic import BaseModel
from typing import List

from .player import PlayerGetSchema
from .card import CardSchema

class GameStateSchema(BaseModel):
    players: List[PlayerGetSchema]
    player_count: int
    street: str
    board: List[CardSchema]
    pot: int
    bet_to_match: int
