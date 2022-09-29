from django.shortcuts import render
from django import http
# Create your views here.



def get(request, *args, **kwargs):
   return http.HttpResponse("hehexd");