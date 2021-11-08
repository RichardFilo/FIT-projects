from django.db import models
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.dispatch import receiver
from PIL import Image
# Create your models here.

class Account(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    image = models.ImageField(default='account_pics/default.jpg', upload_to='account_pics')
    info = models.TextField(null=True, default="", blank=True, help_text="Optional.")
    
    class Account_perms(models.TextChoices):
        NOBODY = 'Nobody'
        GROUP_MEMBER = 'Group members'
        REGISTERED_USER = 'Registered users'
        EVERYBODY = 'Everybody'

    permissions = models.CharField(max_length=20, default=Account_perms.EVERYBODY, choices=Account_perms.choices, help_text="Choose who can see you profile.") 

    def __str__(self):
        return f'{self.user.username} Account'

    @receiver(post_save, sender=User)
    def create_user_account(sender, instance, created, **kwargs):
        if created:
            Account.objects.create(user=instance)

    @receiver(post_save, sender=User)
    def save_user_account(sender, instance, **kwargs):
        instance.account.save()

    def save(self, *args, **kwargs):
        super(Account, self).save(*args, **kwargs)

        img = Image.open(self.image.path)

        if img.height > 300 or img.width > 300:
            output_size = (300,300)
            img.thumbnail(output_size)
            img.save(self.image.path)