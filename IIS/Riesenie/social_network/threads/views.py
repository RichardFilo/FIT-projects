from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from .models import Thread, Post, Rank
from groups.models import Group, Member
from threads.forms import ThreadCreateUpdateForm, PostCreateForm
from django.contrib import messages
from django.urls import reverse
# Create your views here.

def home(request):
    items = Thread.objects.none()
    if request.user.is_anonymous:
        groups = Group.objects.filter(permissions='Everybody')
        for group in groups:
            items = items | Thread.objects.filter(group=group)
        items = items.order_by('reg_date').reverse()

    else:
        groups = Member.objects.filter(user=request.user, role__gt=0)
        for group in groups:
            items = items | Thread.objects.filter(group=group.group)
        items = items.order_by('reg_date').reverse()
            
    return render(request, 'threads/home.html',{'items':items})


def thread(request, id):
    obj = get_object_or_404(Thread, id=id)
    items = Post.objects.filter(thread=obj)
    for item in items:
        item.rank = item.get_rank()
        item.userRank = item.get_userRank(request.user)
        print(item.rank, item.userRank)
    role = obj.group.whatRole(request.user)
    form = None

    if request.user.is_superuser or obj.group.permissions == 'Everybody' or obj.group.permissions == 'Registered users' and request.user.is_authenticated or request.user.is_authenticated and obj.group.permissions == 'Group members' and obj.group.is_member(request.user):
        visib = True
    else:
        visib = False
        messages.warning(request, 'You have no permissions to see the thread!')

    if obj.group.whatRole(request.user) > 0: 
        if request.method == 'POST':
            form = PostCreateForm(request.POST)

            if form.is_valid():
                form.instance.creator = request.user
                form.instance.thread = obj
                form.save()
                messages.success(request, 'The post has been created!')
                return redirect('thread', id)
        else:
            form = PostCreateForm()

    return render(request, "threads/thread.html", {'obj':obj, 'visib':visib, 'items':items, 'role':role, 'form':form})


@login_required
def thread_create(request, group_label):
    obj = get_object_or_404(Group, label=group_label)
    if obj.whatRole(request.user) > 0: 
        if request.method == 'POST':
            form = ThreadCreateUpdateForm(request.POST)

            if form.is_valid():
                form.instance.creator = request.user
                form.instance.group = obj
                form.save()
                messages.success(request, 'The thread has been created!')
                return redirect('thread', form.instance.id)
        else:
            form = ThreadCreateUpdateForm()

    else:
        messages.warning(request, 'You have no permission to create a thread in the group!')
        return redirect('group_threads', group_label)

    return render(request, 'threads/thread_create.html', {'form': form})


@login_required
def thread_edit(request, id):
    obj = get_object_or_404(Thread, id=id)
    if request.user.is_superuser or obj.group.whatRole(request.user) == 3: 
        if request.method == 'POST':
            form = ThreadCreateUpdateForm(request.POST, instance=obj)

            if form.is_valid():
                form.save()
                messages.success(request, 'The thread has been updated!')
                return redirect('thread', id)
        else:
            form = ThreadCreateUpdateForm(instance=obj)

    else:
        messages.warning(request, 'You have no permission to edit a thread in the group!')
        return redirect('thread', id)

    return render(request, 'threads/thread_edit.html', {'form': form})


@login_required
def thread_delete(request, id):
    obj = get_object_or_404(Thread, id=id)
    if request.user.is_superuser or obj.group.whatRole(request.user) == 3:
        group_label = obj.group.label
        obj.delete()
        messages.success(request, 'The thread has been deleted!')
        return redirect('group_threads', group_label)

    else:
        messages.warning(request, 'You have no permissions to delete the thread!')
        return redirect('thread', id)


@login_required
def post_delete(request, id):
    obj = get_object_or_404(Post, id=id)
    thread_id = obj.thread.id
    if request.user.is_superuser or obj.thread.group.whatRole(request.user) == 3: 
        obj.delete()
        messages.success(request, 'The post has been deleted!')
        return redirect('thread', thread_id)

    else:
        messages.warning(request, 'You have no permission to delete a post in the thread!')
        return redirect('thread', thread_id)



@login_required
def post_like(request, id):
    obj = get_object_or_404(Post, id=id)
    thread_id = obj.thread.id
    if obj.thread.group.whatRole(request.user) > 0 and obj.get_userRank(request.user) != 1: 
        if Rank.objects.filter(post=obj, user=request.user).exists():
            rank = Rank.objects.get(post=obj, user=request.user)
            rank.value = 1
        else:
            rank = Rank(post=obj, user=request.user, value=1)
        rank.save()
        messages.success(request, 'The post has been liked!')
        return redirect('thread', thread_id)

    else:
        messages.warning(request, 'You are not able to like the post!')
        return redirect('thread', thread_id)

@login_required
def post_dislike(request, id):
    obj = get_object_or_404(Post, id=id)
    thread_id = obj.thread.id
    if obj.thread.group.whatRole(request.user) > 0 and obj.get_userRank(request.user) != -1: 
        if Rank.objects.filter(post=obj, user=request.user).exists():
            rank = Rank.objects.get(post=obj, user=request.user)
            rank.value = -1
        else:
            rank = Rank(post=obj, user=request.user, value=-1)
        rank.save()
        messages.success(request, 'The post has been disliked!')
        return redirect('thread', thread_id)

    else:
        messages.warning(request, 'You are not able to dislike the post!')
        return redirect('thread', thread_id)