from pydantic import BaseModel

class CardSchema(BaseModel):
    rank: str
    suit: str
