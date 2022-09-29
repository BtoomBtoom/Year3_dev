from http.client import HTTPResponse
from django.shortcuts import render
from django import http

# Create your views here.


def Func(request, *args, **kwargs):
   print(args)
   print(kwargs)
   return http.HttpResponse("hehe^^")
