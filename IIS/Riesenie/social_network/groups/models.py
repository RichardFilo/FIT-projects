from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User
from PIL import Image

# Create your models here.

class Group(models.Model):
    label = models.CharField(unique=True, max_length=40, help_text="label of group must be unique")
    image = models.ImageField(default='groups_pics/default.jpg', upload_to='groups_pics')
    description = models.TextField(null=True, default="", blank=True, help_text="Optional.")
    reg_date = models.DateTimeField(default=timezone.now)
    creator = models.ForeignKey(User, on_delete=models.CASCADE)

    class Account_perms(models.TextChoices):
        GROUP_MEMBER = 'Group members'
        REGISTERED_USER = 'Registered users'
        EVERYBODY = 'Everybody'

    permissions = models.CharField(max_length=20, default=Account_perms.EVERYBODY, choices=Account_perms.choices, help_text="Choose who can see you profile.") 

    def __str__(self):
        return f'Group {self.label}'

    def save(self, *args, **kwargs):
        super(Group, self).save(*args, **kwargs)

        img = Image.open(self.image.path)

        if img.height > 300 or img.width > 300:
            output_size = (300,300)
            img.thumbnail(output_size)
            img.save(self.image.path)

    def is_memReq(self, _user):
        return Member.objects.filter(user=_user, group=self).exists()

    def is_member(self, _user):
        return Member.objects.filter(user=_user, group=self, role__gt=0).exists()

    def is_modReq(self, _user):
        return Member.objects.filter(user=_user, group=self, role__gt=1).exists()

    def is_moderator(self, _user):
        return Member.objects.filter(user=_user, group=self, role__gt=2).exists()

    def whatRole(self, _user):
        if not _user.is_anonymous and Member.objects.filter(user=_user, group=self).exists(): 
            member = Member.objects.get(user=_user, group=self)
            return member.role
        else:
            return -1


class Member(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    group = models.ForeignKey(Group, on_delete=models.CASCADE)
    role = models.IntegerField(default=0) # 0=>mem_req 1=>member 2=>mod_req 3=>moderator

    class Meta:
        unique_together = (("user", "group"),)
    
    def __str__(self):
        return f'{self.user} member of {self.group}'

    def is_groupMember(user1, user2):
        user1_groups = Member.objects.filter(user=user1, role__gt=0)
        for user1_group in user1_groups:
            if user1_group.group.is_member(user2):
                return True
        return False


