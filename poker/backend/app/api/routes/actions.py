from fastapi import APIRouter

from ....app.services.room_manager import room_manager

router = APIRouter()

@router.post("/tables/{room_id}/join")
def join_table(room_id: str):
    return {"message": f"joined table {room_id}"}

@router.post("/tables/{room_id}/leave")
def leave_table():
    return {"message": "left table"}

@router.post("/tables/{room_id}/actions")
def apply_action(room_id: str): #TODO action schema passed as arg
    return {"message": "applied action"}