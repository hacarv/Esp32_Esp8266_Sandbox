JSON Message Structure
// Estructura de mensajes JSON:
// Para establecer el color del LED:
// {
//   "led": {"r": 255, "g": 0, "b": 0}
// }

// Para establecer la posición del servo motor:
// {
//   "servo": 90
// }

// Para mover el motor stepper (pasos positivos para una dirección, negativos para la otra):
// {
//   "stepper": 200
// }

// Respuesta de actualización del valor de la LDR:
// {
//   "ldr": 123
// }

// Respuesta de actualización del valor del potenciómetro:
// {
//   "potentiometer": 456
// }

Establecer AP:
{
    "setAP": {
        "ssid": "AP_SSID",
        "password": "AP_PASSWORD",
        "ip": "192.168.1.1"
    }
}

Conectar a WiFi:
{
    "connectWiFi": {
        "ssid": "WiFi_SSID",
        "password": "WiFi_PASSWORD"
    }
}

Escanear redes WiFi:
{
    "scanNetworks": true
}

Notificación de Estado:
{
    "status": "connected"
}