from pydantic import BaseModel
from typing import Optional

class ActionSchema(BaseModel):
    action: str
    bet: Optional[int]