from fastapi import APIRouter
from typing import List

from ....app.services.room_manager import room_manager
from ....app.models.game_state import GameState
from ....app.schemas.state import GameStateSchema
from ....app.schemas.player import PlayerSchema
from ....app.schemas.card import CardSchema

router = APIRouter()

@router.post("/tables")
def create_table():
    id: str = room_manager.create_room()
    return {"message": f"table {id} created"}

@router.get("/tables/{room_id}")
def get_state(room_id: str):
    state: GameState = room_manager.get_room(room_id)

    player_schemas: List[PlayerSchema] = list()
    for player in state.players:
        # Create nested card schemas for player schema
        card_schemas: List[CardSchema] = list()
        for card in player.cards:
            temp_card_schema: CardSchema = CardSchema(
                rank=card.rank.name,
                suit=card.suit.name,
            )
            card_schemas.append(temp_card_schema)
        # Create nested player schema for game state schema
        temp_player_schema: PlayerSchema = PlayerSchema(
            name=player.name,
            stack=player.stack,
            cards=card_schemas,
            current_bet=player.current_bet,
            state=player.state.name,
        )
        player_schemas.append(temp_player_schema)

    board_cards_schemas: List[CardSchema] = list()
    for card in state.board:
        temp_card_schema: CardSchema = CardSchema(
            rank=card.rank.name,
            suit=card.suit.name,
        )
        board_cards_schemas.append(temp_card_schema)

    return GameStateSchema(
        players=player_schemas,
        active_players=state.active_player_count,
        board=board_cards_schemas,
        street=state.street.name,
        pot=state.pot,
        bet_to_match = state.current_bet_to_match,
    )

