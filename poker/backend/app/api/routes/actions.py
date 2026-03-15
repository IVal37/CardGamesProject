from fastapi import APIRouter

router = APIRouter()

@router.post("/tables")
def create_table():
    return {"message": "table created"}

@router.get("/tables/{room_id}")
def get_table(room_id: str):
    return {"room_id": room_id}