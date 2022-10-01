import paho.mqtt.client as mqtt
import json
import psycopg2


mqtt_broker = "broker.hivemq.com"
# mqtt_broker = "broker.broker.com"
mqtt_port = 1883
topic = "Year3"

def on_connect(client, userdata, flags, rc):
    print("Connected successfully")
    client.subscribe(topic)

def insert_to_DB(data):
    conn = psycopg2.connect(
        database = 'year3',
        user = 'quan',
        password = '1',
        host = 'localhost',
        port = '5432',
    )

    conn.autocommit = True
    cursor = conn.cursor()

    query = '''INSERT INTO sensors_sensors (mac, temp, hum) 
    VALUES (%s, %s, %s)'''
    record = (data['ID'], data['Temperature'], data['Humidity'])
    cursor.execute(query, record)

    conn.close()

def on_message(client, userdata, msg):
    msg_str = msg.payload.decode("UTF-8")
    msg_json = json.loads(msg_str)
    insert_to_DB(msg_json)
    print(msg_json['Temperature'])


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(mqtt_broker, mqtt_port, 60)

