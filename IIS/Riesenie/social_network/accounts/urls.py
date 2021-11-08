from django.urls import path
from . import views

urlpatterns = [
    path('all/', views.accounts, name='accounts'),
    path('<str:user_name>/', views.account, name='account'),
    path('<str:user_name>/edit/', views.account_edit, name='account_edit'),
    path('<str:user_name>/delete/', views.account_delete, name='account_delete'),
]
