from pydantic import BaseModel

from .card import CardSchema

def PlayerSchema(BaseModel):
    name: str
    stack: int
    cards: list[CardSchema]
    current_bet: int
    state: str