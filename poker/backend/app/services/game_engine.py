

from ..models.game_state import GameState
from ..models.enums import PlayerState

def start_game(state: GameState) -> None:
    state.currently_dealing = True
    start_round(state)

def start_round(state: GameState) -> None:
    deal_hands(state)
    post_blinds(state)

def deal_hands(state: GameState) -> None:
    for player in state.players:
        if player.state == PlayerState.ACTIVE:
            player.cards = state.deck.deal_hand(2)

def post_blinds(state: GameState) -> None:
    state.make_bet(0, 5)
    state.make_bet(1, 10)

def toggle_pause(state: GameState) -> None:
    state.currently_dealing = not state.currently_dealing