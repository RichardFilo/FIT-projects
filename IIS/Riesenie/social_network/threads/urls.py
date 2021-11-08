from django.urls import path
from . import views

urlpatterns = [
    path('<int:id>/', views.thread, name='thread'),
    path('<int:id>/edit/', views.thread_edit, name='thread_edit'),
    path('<int:id>/delete/', views.thread_delete, name='thread_delete'),
    path('create/<str:group_label>/', views.thread_create, name='thread_create'),
    path('post_delete/<int:id>/', views.post_delete, name='post_delete'),
    path('post_like/<int:id>/', views.post_like, name='post_like'),
    path('post_dislike/<int:id>/', views.post_dislike, name='post_dislike'),
]