from fastapi import APIRouter

from ...services.room_manager import room_manager
from ...models.game_state import GameState
from ...models.game_action import GameAction
from ...models.player import Player
from ...services.game_engine import start_game, make_action
from ...core.enums import Action
router = APIRouter()

@router.post("/debug/start")
def testing_start():
    room_manager.create_room()
    state: GameState = room_manager.get_room(1)

    player_1: Player = Player(
        name='Izaak',
        stack=400,
    )

    player_2: Player = Player(
        name='Kei',
        stack=400,
    )

    player_3: Player = Player(
        name='Colby',
        stack=400,
    )

    state.add_player(player_1)
    state.add_player(player_2)
    state.add_player(player_3)

    start_game(state)

    make_action(state, 2, GameAction(Action.CALL, 2))
    make_action(state, 0, GameAction(Action.CALL, 1))
    make_action(state, 1, GameAction(Action.CHECK, 0))

    return {"message": f"succesfully started debug test game"}