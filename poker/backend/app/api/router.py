from fastapi import APIRouter
from ..api.routes.health import router as health_router
from ..api.routes.tables import router as tables_router
from ..api.routes.actions import router as actions_router
from ..api.routes.debug import router as debug_router

api_router = APIRouter()

api_router.include_router(health_router, tags=["health"])
api_router.include_router(tables_router, tags=["tables"])
api_router.include_router(actions_router, tags=["actions"])
api_router.include_router(debug_router, tags=["debug"])