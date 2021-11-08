from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import login, authenticate
from .forms import SignUpForm, UserUpdateForm, AccountUpdateForm
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from django.contrib import messages
from groups.models import Group, Member

# Create your views here.

def about(request):
    return render(request, 'about.html')


def signup(request):
    if request.method == 'POST':
        form = SignUpForm(request.POST)
        if form.is_valid():
            form.save()
            username = form.cleaned_data.get('username')
            raw_password = form.cleaned_data.get('password1')
            user = authenticate(username=username, password=raw_password)
            login(request, user)
            messages.success(request, 'The account has been created!')
            return redirect('account', form.instance.username)
    else:
        form = SignUpForm()
    return render(request, 'accounts/signup.html', {'form': form})



def account(request,user_name):
    obj = get_object_or_404(User, username=user_name)
    items = Member.objects.filter(user=obj, role__gt=0)
    if request.user.is_superuser or obj.username == request.user.username or obj.account.permissions == 'Everybody' or obj.account.permissions == 'Registered users' and request.user.is_authenticated or request.user.is_authenticated and obj.account.permissions == 'Group members' and Member.is_groupMember(obj, request.user):
        visib = True
    else:
        visib = False
        messages.warning(request, 'You have no permissions to see the profile!')
    return render(request, "accounts/account.html", {'obj':obj, 'visib':visib, 'items':items})


@login_required
def account_edit(request, user_name):
    obj = get_object_or_404(User, username=user_name)
    if request.user.is_superuser or obj.username == request.user.username :

        if request.method == 'POST':
            form_u = UserUpdateForm(request.POST, instance=obj)
            form_a = AccountUpdateForm(request.POST, request.FILES, instance=obj.account)

            if form_u.is_valid() and form_a.is_valid():
                form_u.save()
                form_a.save()
                messages.success(request, 'The account has been updated!')
                return redirect('account', form_u.instance.username)
        else:
            form_u = UserUpdateForm(instance=obj)
            form_a = AccountUpdateForm(instance=obj.account)
        return render(request, 'accounts/account_edit.html', {'form_u': form_u, 'form_a': form_a})

    else:
        messages.warning(request, 'You have no permissions to edit the account!')
        return redirect('account', user_name)    


def accounts(request):
    accounts = User.objects.all()
    return render(request, "accounts/accounts.html", {'accounts': accounts })

@login_required
def account_delete(request, user_name):
    obj = get_object_or_404(User, username=user_name)
    if request.user.is_superuser or obj.username == request.user.username :
        obj.delete()
        messages.success(request, 'The account has been deleted!')
        return redirect('home')

    else:
        messages.warning(request, 'You have no permissions to delete the account!')
        return redirect('account', user_name)
