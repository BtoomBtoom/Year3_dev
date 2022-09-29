from django.db import models

# Create your models here.

class Users(models.Model):
   users_id = models.IntegerField()
   user_name = models.CharField(max_length=50)
   email = models.models.CharField(max_length=255)

class Sensors(models.Model):
   user