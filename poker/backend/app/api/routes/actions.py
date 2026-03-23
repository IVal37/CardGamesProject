from fastapi import APIRouter

from ....app.services.room_manager import room_manager
from ....app.models.game_state import GameState
from ....app.models.game_action import GameAction
from ....app.models.player import Player
from ...core.enums import str_to_action
from ....app.schemas.player import PlayerPostSchema
from ....app.schemas.actions import ActionSchema
from ....app.services.game_engine import start_game, make_action

router = APIRouter()

@router.post("/tables/{table_id}/join")
def join_table(table_id: str, player_schema: PlayerPostSchema):
    state: GameState = room_manager.get_room(int(table_id))
    if state is None:
        return {"message": f"table {table_id} does not exist"}

    player: Player = Player(
        name=player_schema.name,
        stack=player_schema.stack,
    )
    state.add_player(player)

    return {"message": f"player added to table {table_id}"}

@router.post("/tables/{table_id}/leave")
def leave_table(table_id: str, name: str):
    state: GameState = room_manager.get_room(int(table_id))
    if state is None:
        return f"table {table_id} does not exist"
    
    removed: bool = state.remove_player(name)
    if removed:
        return {"message": f"{name} left table {table_id}"}
    else:
        return {"message": f"could not find {name} at table {table_id}"}

@router.post("/tables/{table_id}/boot")
def boot_game(table_id: str):
    state: GameState = room_manager.get_room(int(table_id))
    if state is None:
        return {"message": f"table {table_id} does not exist"}
    
    start_game(state)
    return {"message": f"started game at table {table_id}"}

@router.post("/tables/{table_id}/pause")
def pause_game(table_id: str):
    state: GameState = room_manager.get_room(int(table_id))
    if state is None:
        return {"message": f"table {table_id} does not exist"}
    
    state.toggle_pause()

@router.post("/tables/{room_id}/actions")
def apply_action(table_id: str, player_index: int, action_schema: ActionSchema):
    state: GameState = room_manager.get_room(int(table_id))
    if state is None:
        return {"message": f"table {table_id} does not exist"}
    
    if state.current_player_index != player_index:
        return {"message": f"current player is player {state.current_player_index}"}
    
    action: GameAction = GameAction(
        action=str_to_action(action_schema.action),
        bet=action_schema.bet,
    )

    make_action(state, player_index, action)

    return {"message": f"next player idx: {state.current_player_index}"}
