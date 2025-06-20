import argparse
import base64
import json
import logging
import signal
import struct
import sys
import time

from telegram.ext import Application
from telegram.ext import CommandHandler
from telegram.ext import MessageHandler
from telegram.ext import filters

import paho.mqtt.client as mqtt
from datetime import datetime, timezone

r_value = "VOID"


def on_connect(mqttc, obj, flags, reason_code, properties=None):
    print(f"Connected to {mqttc._host}:{mqttc._port}")
    print(f"Flags: {flags}")
    print(f"Reason Code: {reason_code}")
    print(f"Properties: {properties}")

    mqttc.subscribe("v3/+/devices/#", qos=0)


def on_message(client, userdata, msg):
    global r_value
    print("msg received with topic: {} and payload: {}".format(
        msg.topic, str(msg.payload)))

    if (msg.topic == "v3/lopys2ttn@ttn/devices/lopy4sense/up"):

        themsg = json.loads(msg.payload.decode("utf-8"))
        dpayload = themsg["uplink_message"]["decoded_payload"]

        print("@%s >> temp=%.3f hum=%.3f lux=%.3f" %
              (time.strftime("%H:%M:%S"), dpayload["temperature"],
               dpayload["humidity"], dpayload["lux"]))

        r_value = dpayload["temperature"]


async def start(update, context):
    options_text = ("👋 ¡Hola! I'm a Bot 🤖.")
    await context.bot.send_message(chat_id=update.effective_chat.id, text=options_text)


async def getdata(update, context):
    await context.bot.send_message(chat_id=update.effective_chat.id,
                                   text=f"🌡️ Current temperature is: {r_value}°C")

async def unknown(update, context):
    options_text = (
        "💬 Sorry I dont understand this command. 😕\n\n"
        "Please use one of the following:\n"
        "/start - See all available options 👀.\n"
        "/getdata - Get data 🌡️.\n"
    )
    await context.bot.send_message(chat_id=update.effective_chat.id, text=options_text)


# setting up MQTT
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set(
    "___FILL_IN_HERE___",
    password=
    "___FILL_IN_HERE___"
)
client.connect("___FILL_IN_HERE___", port=1883, keepalive=60)
client.loop_start()


# bot configuration
application = Application.builder().token("___FILL_IN_HERE___").build()

## commands handlers
start_handler = CommandHandler('start', start)
application.add_handler(start_handler)

getdata_handler = CommandHandler('getdata', getdata)
application.add_handler(getdata_handler)

unknown_handler = MessageHandler(filters.TEXT | (~filters.COMMAND), unknown)
application.add_handler(unknown_handler)

# starts bot
application.run_polling()
