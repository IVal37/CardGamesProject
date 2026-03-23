from dataclasses import dataclass

from ..core.enums import Action

@dataclass
class GameAction:
    _action: Action
    _bet: int

    @property
    def action(self):
        return self._action
    
    @action.setter
    def action(self, action):
        self._action = action
    
    @property
    def bet(self):
        return self._bet
    
    @bet.setter
    def bet(self, bet):
        self._bet = bet

    def __init__(self, action: Action, bet: int):
        self.action = action
        self.bet = bet