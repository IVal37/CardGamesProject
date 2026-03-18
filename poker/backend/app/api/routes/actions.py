from fastapi import APIRouter

from ....app.services.room_manager import room_manager
from ....app.models.game_state import GameState
from ....app.models.player import Player
from ....app.schemas.player import PlayerPostSchema
from ....app.services.game_engine import start_game, toggle_pause

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
    
    toggle_pause(state)

@router.post("/tables/{room_id}/actions")
def apply_action(room_id: str, action: str): #TODO action schema passed as arg
    return {"message": f"applied action {action}"}