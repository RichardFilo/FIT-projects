from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth.decorators import login_required
from django.contrib.auth.models import User
from .models import Group, Member
from threads.models import Thread
from .forms import GroupUpdateForm
from django.contrib import messages
from django.urls import reverse

# Create your views here.


def group(request,group_label,session):
    obj = get_object_or_404(Group, label=group_label)
    role = obj.whatRole(request.user)
    threads = Thread.objects.filter(group=obj).order_by('reg_date').reverse()


    if request.user.is_superuser or obj.permissions == 'Everybody' or obj.permissions == 'Registered users' and request.user.is_authenticated or request.user.is_authenticated and obj.permissions == 'Group members' and obj.is_member(request.user):
        visib = True
    else:
        visib = False
        messages.warning(request, 'You have no permissions to see the group!')

    if request.user.is_superuser: #admin content
        content = {
            'control': [
                {
                    'text': 'Edit group',
                    'color': 'primary',
                    'func_url': reverse('group_edit',args=(group_label,))
                },
                {
                    'text': 'Delete group',
                    'color': 'danger',
                    'func_url': reverse('group_delete',args=(group_label,))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Moderator requests',
                    'items' : Member.objects.filter(group=obj, role=2),
                    'control': [
                        {
                            'text': 'confirm',
                            'color': 'primary',
                            'func': 'add_mod',
                        },
                        {
                            'text': 'reject',
                            'color': 'danger',
                            'func': 'rem_mod',
                        },
                    ],              
                },
                {
                    'text'  : 'Member requests',
                    'items' : Member.objects.filter(group=obj, role=0),
                    'control': [
                        {
                            'text': 'confirm',
                            'color': 'primary',
                            'func': 'add_mem',
                        },
                        {
                            'text': 'reject',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [
                        {
                            'text': 'remove moderator',
                            'color': 'danger',
                            'func': 'rem_mod',
                        },
                        {
                            'text': 'remove member',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control': [
                        {
                            'text': 'remove member',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
            ],
        }
        if request.user == obj.creator:
            content['role'] = 'Admin: Group manager'
        elif role == -1:
            content['role'] = 'Admin'
            content['control'] +=[
                {
                    'text': 'Send the member request',
                    'color': 'primary',
                    'func_url': reverse('mem_req',args=(group_label,))
                }
            ]
        elif role == 0:
            content['role'] = 'Admin: member request sent'
            content['control'] +=[
                {
                    'text': 'Cancel the member request',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ]
        elif role == 1:
            content['role'] = 'Admin: member'
            content['control'] +=[
                {
                    'text': 'Send the moderator request',
                    'color': 'primary',
                    'func_url': reverse('mod_req',args=(group_label,))
                },
                {
                    'text': 'Leave the group',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ]
        elif role == 2:
            content['role'] = 'Admin: moderator request sent'
            content['control'] +=[
                {
                    'text': 'Cancel moderator request',
                    'color': 'warning',
                    'func_url': reverse('rem_mod',args=(group_label,request.user.username))
                },
                {
                    'text': 'Leave the group',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ]
        else:
            content['role'] = 'Admin: moderator'
            content['control'] +=[
                {
                    'text': 'Cancel moderator',
                    'color': 'warning',
                    'func_url': reverse('rem_mod',args=(group_label,request.user.username))
                },
                {
                    'text': 'Leave the group',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ]

    elif request.user == obj.creator: #creator content
        content = {
            'role': 'Group manager',
            'control': [
                {
                    'text': 'Edit group',
                    'color': 'primary',
                    'func_url': reverse('group_edit',args=(group_label,))
                },
                {
                    'text': 'Delete group',
                    'color': 'danger',
                    'func_url': reverse('group_delete',args=(group_label,))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Moderator requests',
                    'items' : Member.objects.filter(group=obj, role=2),
                    'control': [
                        {
                            'text': 'confirm',
                            'color': 'primary',
                            'func': 'add_mod',
                        },
                        {
                            'text': 'reject',
                            'color': 'danger',
                            'func': 'rem_mod',
                        },
                    ],              
                },
                {
                    'text'  : 'Member requests',
                    'items' : Member.objects.filter(group=obj, role=0),
                    'control': [
                        {
                            'text': 'confirm',
                            'color': 'primary',
                            'func': 'add_mem',
                        },
                        {
                            'text': 'reject',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [
                        {
                            'text': 'remove moderator',
                            'color': 'danger',
                            'func': 'rem_mod',
                        },
                        {
                            'text': 'remove member',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control': [
                        {
                            'text': 'remove member',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
            ],
        }
    elif not request.user.is_authenticated:    #loged out user content
        content = {
            'control': [],
            'all_members': [
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control':[],              
                },
            ],
        }
    elif role == -1:    #loged in nonmember content
        content = {
            'control': [
                {
                    'text': 'Send the member request',
                    'color': 'primary',
                    'func_url': reverse('mem_req',args=(group_label,))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control':[],              
                },
            ],
        }
    elif role == 0:     #req_member content
        content = {
            'role': 'Member request sent',
            'control': [
                {
                    'text': 'Cancel the member request',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control':[],              
                },
            ],
        }
    elif role == 1:     #member content
        content = {
            'role': 'Member',
            'control': [
                {
                    'text': 'Send the moderator request',
                    'color': 'primary',
                    'func_url': reverse('mod_req',args=(group_label,))
                },
                {
                    'text': 'Leave the group',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control':[],              
                },
            ],
        }
    elif role == 2:     #req_moderator content
        content = {
            'role': 'Moderator request sent',
            'control': [
                {
                    'text': 'Cancel moderator request',
                    'color': 'warning',
                    'func_url': reverse('rem_mod',args=(group_label,request.user.username))
                },
                {
                    'text': 'Leave the group',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control':[],              
                },
            ],
        }
    else:               #moderator content
        content = {
            'role': 'Moderator',
            'control': [
                {
                    'text': 'Cancel moderator',
                    'color': 'warning',
                    'func_url': reverse('rem_mod',args=(group_label,request.user.username))
                },
                {
                    'text': 'Leave the group',
                    'color': 'danger',
                    'func_url': reverse('rem_mem',args=(group_label,request.user.username))
                }
            ],
            'all_members': [
                {
                    'text'  : 'Member requests',
                    'items' : Member.objects.filter(group=obj, role=0),
                    'control': [
                        {
                            'text': 'confirm',
                            'color': 'primary',
                            'func': 'add_mem',
                        },
                        {
                            'text': 'reject',
                            'color': 'danger',
                            'func': 'rem_mem',
                        },
                    ],              
                },
                {
                    'text'  : 'Moderators',
                    'items' : Member.objects.filter(group=obj, role=3),
                    'control': [],              
                },
                {
                    'text'  : 'Other members',
                    'items' : Member.objects.filter(group=obj, role__gt=0, role__lt=3),
                    'control':[],              
                },
            ],
        }

    context ={
        'obj'       : obj,
        'visib'     : visib,
        'content'   : content,
        'threads'   : threads,
        'role_num'  : role,
    }
    return render(request, f"groups/group_{session}.html",context)



def groups(request):
    groups = Group.objects.all()
    return render(request, "groups/groups.html", {'groups': groups })

@login_required
def group_edit(request,group_label):
    obj = get_object_or_404(Group, label=group_label)
    if request.user.is_superuser or obj.creator.username == request.user.username :
        if request.method == 'POST':
            form = GroupUpdateForm(request.POST, request.FILES, instance=obj)

            if form.is_valid():
                form.save()
                messages.success(request, 'Group profile has been updated!')
                return redirect('group', form.instance.label)
        else:
            form = GroupUpdateForm(instance=obj)

        return render(request, 'groups/group_edit.html', {'form': form})

    else:
        messages.warning(request, 'You have no permissions to edit the group!')
        return redirect('group', obj.label)


@login_required
def group_delete(request,group_label):
    obj = get_object_or_404(Group, label=group_label)
    if request.user.is_superuser or obj.creator.username == request.user.username :
        obj.delete()
        messages.success(request, 'The group has been deleted!')
        return redirect('groups')

    else:
        messages.warning(request, 'You have no permissions to delete the group!')
        return redirect('group', group_label)


@login_required
def group_create(request):

    if request.method == 'POST':
        form = GroupUpdateForm(request.POST, request.FILES)

        if form.is_valid():
            form.instance.creator = request.user
            form.save()
            member = Member(user= request.user, group= form.instance, role=3)
            member.save()
            messages.success(request, 'Group profile has been created!')
            return redirect('group', form.instance.label)
    else:
        form = GroupUpdateForm()

    return render(request, 'groups/group_create.html', {'form': form})


@login_required
def mem_req(request,group_label):
    obj = get_object_or_404(Group, label=group_label)
    if obj.whatRole(request.user) == -1:
        member = Member(user=request.user, group= obj, role=0)
        member.save()
        messages.success(request, 'You have created the member request.')
    else:
        messages.warning(request, 'You are not able to create the member request.')

    if request.META.get('HTTP_REFERER') == None:
        red_url = reverse('group',args=(group_label,))
    else:
        red_url = request.META.get('HTTP_REFERER')
    return redirect(red_url)

@login_required
def mod_req(request,group_label):  
    obj = get_object_or_404(Group, label=group_label)
    if obj.whatRole(request.user) == 1:
        member = Member.objects.get(user=request.user, group= obj)
        member.role = 2
        member.save()
        messages.success(request, 'You have created the moderator request.')
    else:
        messages.warning(request, 'You are not able to create the moderator request.')

    return redirect(request.META.get('HTTP_REFERER'))


@login_required
def add_mem(request,group_label,user_name):
    _group = get_object_or_404(Group, label=group_label)
    _user = get_object_or_404(User, username=user_name)
    if request.user.is_superuser or _group.whatRole(request.user) == 3 and _group.whatRole(_user) == 0:
        member = Member.objects.get(user=_user, group=_group)
        member.role = 1
        member.save()
        messages.success(request, f'You have added the user {_user.username} to the group {_group.label}.')
    else:
        messages.warning(request, 'You are not able to add a member.')

    return redirect(request.META.get('HTTP_REFERER'))


@login_required
def add_mod(request,group_label,user_name):
    _group = get_object_or_404(Group, label=group_label)
    _user = get_object_or_404(User, username=user_name)
    if request.user.is_superuser or request.user == _group.creator and _group.whatRole(_user) == 2:
        member = Member.objects.get(user=_user, group=_group)
        member.role = 3
        member.save()
        messages.success(request, f'You have added the moderator {_user.username} to the group {_group.label}.')
    else:
        messages.warning(request, 'You are not able to add a moderator.')

    return redirect(request.META.get('HTTP_REFERER'))


@login_required
def rem_mod(request,group_label,user_name):
    _group = get_object_or_404(Group, label=group_label)
    _user = get_object_or_404(User, username=user_name)
    if _user != _group.creator and _group.whatRole(_user) > 1 and (request.user.is_superuser or request.user == _group.creator or request.user == _user):
        member = Member.objects.get(user=_user, group=_group)
        member.role = 1
        member.save()
        messages.success(request, f'You have removed the moderator {_user.username} from the group {_group.label}.')
    else:
        messages.warning(request, 'You are not able to remove the moderator.')

    return redirect(request.META.get('HTTP_REFERER'))


@login_required
def rem_mem(request,group_label,user_name):
    _group = get_object_or_404(Group, label=group_label)
    _user = get_object_or_404(User, username=user_name)
    if _user != _group.creator and _group.whatRole(_user) > -1 and (request.user.is_superuser or request.user == _group.creator or request.user == _user):
        member = Member.objects.get(user=_user, group=_group)
        member.delete()
        messages.success(request, f'You have removed the member {_user.username} from the group {_group.label}.')
    else:
        messages.warning(request, 'You are not able to remove the member.')

    return redirect(request.META.get('HTTP_REFERER'))