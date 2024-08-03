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



1. Agregar nombre del dispositivo en Config.h  EL dEVICE kEY Y EL dEVICE pin
2. Crear archivos de clase .h y .cpp
3. Agregar la referencia a DeviceManager.h              #include "Devices/Relay.h"
4. Crear instancia del dispositovo en DeviceManager.h   Relay relay;
5. Inicializar Dispositivo en DeviceManager::begin()
6. Asignar función de envio de mensajes DeviceManager::begin()
7. Agregar el Device Key a DeviceManager::getDevice(const char *deviceKey)
8. Si el dispositivo actualiza su valor automaticamente agregar a DeviceManager::readAndNotifyDevices()

1. Agregar el Dispositivo Key al SystemConstants.DeviceKey
2. Crear el Dispositivo Component en Components/Devices
3. Agregar el link en Components/Layout/NavMenu
