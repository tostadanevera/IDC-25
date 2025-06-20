# MQTT_client.py
import json
import paho.mqtt.client as mqtt
import asyncio

class MQTTClient:
    def __init__(self, app, topic, mqtt_config):
        self.app = app
        self.topic = topic
        self.chat_id = None

        self.client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2, userdata=self)
        self.client.username_pw_set(mqtt_config["username"], mqtt_config["password"])
        self.client.on_connect = self.on_connect
        self.client.on_message = self.on_message
        self.client.connect(mqtt_config["host"], mqtt_config["port"], 60)

    def set_chat_id(self, chat_id):
        self.chat_id = chat_id

    def start(self):
        self.client.loop_start()

    def on_connect(self, client, userdata, flags, rc, properties=None):
        print(f"✅ Conectado a MQTT. Subscribiendo a {self.topic}")
        client.subscribe(self.topic)

    def on_message(self, client, userdata, msg):
        if not self.chat_id:
            return

        payload = json.loads(msg.payload.decode("utf-8"))
        uid = payload.get("uid", "???")
        access = payload.get("access", False)
        status = "✅ ACCESO PERMITIDO" if access else "⛔ ACCESO DENEGADO"
        message = f"🔔 UID: {uid}\nEstado: {status}"

        asyncio.run(self.app.bot.send_message(chat_id=self.c

