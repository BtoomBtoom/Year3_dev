from pyexpat import model
from unittest.util import _MAX_LENGTH
from django.db import models

# Create your models here.

#>>>>>>>>>>>>>>>>>>>>>>>>can not migrate table to postgresql<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

class User(models.Model):
   user_id = models.IntegerField(primary_key = True)
   user_name = models.CharField(max_length=50)
   email = models.CharField(max_length=255)

class Sensor(models.Model):
   i = models.IntegerField(primary_key = True)
   user_id = models.ForeignKey(User, on_delete = models.CASCADE)
   time = models.BigIntegerField()
   temperature = models.FloatField()
   humidity  = models.FloatField()
   light = models.FloatField()
   dust = models.FloatField()
   sound = models.FloatField()
   red = models.SmallIntegerField()
   green = models.SmallIntegerField()
   blue = models.SmallIntegerField()
   co2 = models.SmallIntegerField()
   tvoc = models.SmallIntegerField()
   motion = models.SmallIntegerField()
   id = models.SmallIntegerField()


