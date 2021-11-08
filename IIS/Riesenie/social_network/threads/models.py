from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User
from groups.models import Group
# Create your models here.

class Thread(models.Model):
    subject = models.CharField( max_length=100)
    reg_date = models.DateTimeField(default=timezone.now)
    creator = models.ForeignKey(User, on_delete=models.CASCADE)
    group = models.ForeignKey(Group, on_delete=models.CASCADE)

    def __str__(self):
        return self.subject[:15]


class Post(models.Model):
    content = models.TextField()
    reg_date = models.DateTimeField(default=timezone.now)
    creator = models.ForeignKey(User, on_delete=models.CASCADE)
    thread = models.ForeignKey(Thread, on_delete=models.CASCADE)


    def get_rank(self):
        rank = 0
        items = Rank.objects.filter(post=self)
        for item in items:
            rank += item.value
        return rank

    def get_userRank(self,user):
        if user.is_authenticated and Rank.objects.filter(post=self,user=user).exists():
            rank = Rank.objects.get(post=self, user=user).value
            return rank
        else:
            return 0

class Rank(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE)
    post = models.ForeignKey(Post, on_delete=models.CASCADE)
    value = models.IntegerField()

    class Meta:
        unique_together = (("user", "post"),)
