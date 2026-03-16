from pydantic import BaseModel

from .player import PlayerSchema
from .card import CardSchema

def GameStateSchema(BaseModel):
    players: list[PlayerSchema]
    active_player_count: int
    board: list[CardSchema]
    street: str
    pot: int
    bet_to_match: int
