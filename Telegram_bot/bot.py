# bot.py
from telegram.ext import Application
from telegram.ext import CommandHandler
from telegram.ext import MessageHandler
from telegram.ext import filters

from MQTT_client import MQTTClient

# Configuración
TELEGRAM_TOKEN = "TU_TOKEN_AQUI"
MQTT_CONFIG = {
    "host": "BROKER_IP",
    "port": 1883,
    "username": "USUARIO_MQTT",
    "password": "CONTRASEÑA_MQTT"
}
MQTT_TOPIC = "rfid/access"

# Inicialización del bot y del cliente MQTT
application = Application.builder().token(TELEGRAM_TOKEN).build()
mqtt_client = MQTTClient(application, MQTT_TOPIC, MQTT_CONFIG)

# Handlers
async def start(update, context):
    mqtt_client.set_chat_id(update.effective_chat.id)
    await context.bot.send_message(
        chat_id=update.effective_chat.id,
        text="👋 Bot conectado y escuchando el canal MQTT de accesos."
    )

async def unknown(update, context):
    await context.bot.send_message(
        chat_id=update.effective_chat.id,
        text="❓ Comando no reconocido. Usa /start para comenzar."
    )

# Registro de comandos
application.add_handler(CommandHandler("start", start))
application.add_handler(MessageHandler(filters.TEXT & ~filters.COMMAND, unknown))

# Inicio de MQTT y bot
mqtt_client.start()
application.run_polling()
