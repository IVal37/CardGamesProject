from dataclasses import dataclass

from enums import Action

@dataclass
class GameAction:
    _action: Action
    _bet: int

    @property
    def action(self):
        return self._action
    
    @property
    def bet(self):
        return self._bet