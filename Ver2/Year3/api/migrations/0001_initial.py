# Generated by Django 4.1.1 on 2022-09-30 09:44

from django.conf import settings
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        migrations.swappable_dependency(settings.AUTH_USER_MODEL),
    ]

    operations = [
        migrations.CreateModel(
            name='Sensor',
            fields=[
                ('i', models.BigAutoField(primary_key=True, serialize=False)),
                ('time', models.BigIntegerField()),
                ('temperature', models.FloatField()),
                ('humidity', models.FloatField()),
                ('light', models.FloatField()),
                ('dust', models.FloatField()),
                ('sound', models.FloatField()),
                ('red', models.SmallIntegerField()),
                ('green', models.SmallIntegerField()),
                ('blue', models.SmallIntegerField()),
                ('co2', models.SmallIntegerField()),
                ('tvoc', models.SmallIntegerField()),
                ('motion', models.SmallIntegerField()),
                ('id', models.SmallIntegerField()),
                ('user', models.ForeignKey(default=1, null=True, on_delete=django.db.models.deletion.SET_NULL, to=settings.AUTH_USER_MODEL)),
            ],
        ),
    ]
