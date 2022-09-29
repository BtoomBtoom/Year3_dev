from django.urls import path
from Api import views


urlpatterns = [
   path('Func/<int:year>/<int:month>/<slug:slug>', views.Func)
]