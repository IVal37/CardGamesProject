from pydantic import BaseModel
from typing import List

from .card import CardSchema

class PlayerSchema(BaseModel):
    name: str
    stack: int
    cards: List[CardSchema]
    current_bet: int
    state: str