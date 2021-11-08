from django.urls import path
from . import views

urlpatterns = [
    path('all/', views.groups, name='groups'),
    path('create/', views.group_create, name='group_create'),
    path('<str:group_label>/profile/', views.group, {'session':'profile'}, name='group'),
    path('<str:group_label>/members/', views.group, {'session':'members'}, name='group_members'),
    path('<str:group_label>/threads/', views.group, {'session':'threads'}, name='group_threads'),
    path('<str:group_label>/edit/', views.group_edit, name='group_edit'),
    path('<str:group_label>/delete/', views.group_delete, name='group_delete'),
    path('<str:group_label>/mem_req/', views.mem_req, name='mem_req'),
    path('<str:group_label>/mod_req/', views.mod_req, name='mod_req'),
    path('<str:group_label>/add_mem/<str:user_name>/', views.add_mem, name='add_mem'),
    path('<str:group_label>/add_mod/<str:user_name>/', views.add_mod, name='add_mod'),
    path('<str:group_label>/rem_mod/<str:user_name>/', views.rem_mod, name='rem_mod'),
    path('<str:group_label>/rem_mem/<str:user_name>/', views.rem_mem, name='rem_mem'),
]
