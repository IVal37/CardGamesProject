from dataclasses import dataclass
from typing import List

from player import Player

@dataclass
class GameState:
    num_seats: int
    players: List[Player]

    


#reset deck
