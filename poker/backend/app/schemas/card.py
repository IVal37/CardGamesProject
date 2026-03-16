from pydantic import BaseModel

def CardSchema(BaseModel):
    rank: str
    suit: str
