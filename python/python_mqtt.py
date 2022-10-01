import paho.mqtt.client as mqtt
import numpy as np
import time

path_w = 'file.txt'

broker_address = "broker.hivemq.com"

def on_connect(client, userdata, flags, rc):
  print("Connected with result code " + str(rc))
def on_message(client, userdata, message):
  global s
  s = "received message = " + str(message.payload.decode("utf-8")) + '\n'
  with open(path_w, mode='a') as f:
    f.write(s)


client = mqtt.Client()
client.on_connect = on_connect
client.connect(broker_address,1883,60)
client.loop_start()

while True:
  client.subscribe("DATA 3")
  client.on_message = on_message
  