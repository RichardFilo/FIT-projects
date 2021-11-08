from django import forms
from .models import Group

class GroupUpdateForm(forms.ModelForm):

    class Meta:
        model = Group
        fields = ('label','image', 'description', 'permissions',)