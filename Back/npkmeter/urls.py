from django.urls import include, path
from rest_framework import routers

from .views import BasicAPI, PredictionAPI



urlpatterns = [
    path("npkph/", BasicAPI.as_view()),
    path("npkph/prediction", PredictionAPI.as_view())
]


