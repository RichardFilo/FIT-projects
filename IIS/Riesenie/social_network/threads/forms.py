from django import forms
from .models import Thread, Post

class ThreadCreateUpdateForm(forms.ModelForm):

    class Meta:
        model = Thread
        fields = ('subject',)

class PostCreateForm(forms.ModelForm):
    content = forms.CharField(widget=forms.Textarea(attrs={'rows': 4,}))
    
    class Meta:
        model = Post
        fields = ('content',)