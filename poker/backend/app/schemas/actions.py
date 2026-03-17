from pydantic import BaseModel
from typing import Optional

from .player import PlayerSchema
from .card import CardSchema

class ActionSchema(BaseModel):
    player_name: str
    action: str
    bet: Optional[int]