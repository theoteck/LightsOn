// Import BLE library
import 'package:flutter_reactive_ble/flutter_reactive_ble.dart';

// Import widgets
import 'package:lights_on/widgets/toast.dart';
import 'package:lights_on/customization.dart';

// Import convert lirbary; used for converting string to u8
import 'dart:convert';

// If the target device is an iPhone then use it's name, or else use its mac
final deviceId = forIPhone ? deviceName : deviceMac;

// Convert the UUIDs to the library representation
final Uuid serviceUuid = Uuid.parse(bluetoothServiceUUID);
final Uuid characteristicUuid = Uuid.parse(bluetoothCharacteristicUUID);

// Initialize library
final flutterReactiveBle = FlutterReactiveBle();

// Defines the characteristic for data receiving (on the mc side)
final characteristic = QualifiedCharacteristic(
    characteristicId: characteristicUuid,
    serviceId: serviceUuid,
    deviceId: deviceId);

// Simple boolean used by the program to check device connectivity
bool connected = false;

//::bleInit::
//  Initializes the Bluetooth connection between the devices and sets event listeners
void bleInit() {
  // Connect to set device
  flutterReactiveBle
      .connectToAdvertisingDevice(
          id: deviceId,
          withServices: [serviceUuid],
          prescanDuration:
              const Duration(seconds: 5), // Scan before connecting for 5s
          servicesWithCharacteristicsToDiscover: {
            serviceUuid: [characteristicUuid]
          },
          connectionTimeout: Duration(seconds: 10) // Wait for connection 10s
          )
      .listen((event) {
    // Set connected variable according to status
    if (event.connectionState == DeviceConnectionState.connected) {
      connected = true;
    } else if (event.connectionState == DeviceConnectionState.disconnected) {
      connected = false;
    }
  }, onError: (dynamic error) {
    postToast(error.toString()); // Show error to user
  });
}

//::sendData::(effect, setting, data)
//  Used to send data to the mc
void sendData(int effectID, int settingID, int data) async {
  // If the connection is not initialized, or has stopped, connect again
  if (!connected) {
    bleInit();
  }

  // Convert the parameters to a hex string; for data format see TODO
  String sendString = effectID.toRadixString(16).padLeft(2, "0") +
      settingID.toRadixString(16) +
      data.toRadixString(16);

  // Send the previous string as bytes to the mc
  await flutterReactiveBle.writeCharacteristicWithResponse(characteristic,
      value: utf8.encode(sendString));
}
