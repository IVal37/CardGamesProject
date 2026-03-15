from fastapi import APIRouter
from app.api.routes.health import router as health_router
from app.api.routes.tables import router as tables_router

api_router = APIRouter()

api_router.include_router(health_router, tags=["health"])
api_router.include_router(tables_router, tags=["tables"])