from pydantic import BaseModel
from typing import List

from .player import PlayerSchema
from .card import CardSchema

class GameStateSchema(BaseModel):
    players: List[PlayerSchema]
    player_count: int
    board: List[CardSchema]
    street: str
    pot: int
    bet_to_match: int
