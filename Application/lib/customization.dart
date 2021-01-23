// This section contains all the variables that need to be changed
// in order for the app to work on the user's devices

// Use true is the app is going to be compiled for iPhone devices
// or false for Android devices
// This is required for the bluetooth configuration
const forIPhone = false;

// The device name that is in the DEVICE_NAME variable in the lights_on.cpp
const deviceName = "LightsOn tmp";

// The MAC address of the microcontroller
// If you don't know it, install the LightsOn program on the microcontroller
// power it on, and use an app to find out the MAC Address.
// The device you are looking for has the name that you have put in the DEVICE_NAME variable in the lights_on.cpp
const deviceMac = "8C:AA:B5:A2:03:DE";

// The Service UUID that is in the RECEIVE_SERVICE_UUID variable in the lights_on.cpp
const bluetoothServiceUUID = "ffa97fbe-93e9-489f-a768-cae63c65c7dd";

// The Characteristic UUID that is in the DATA_CHARACTERISTIC_UUID variable in the lights_on.cpp
const bluetoothCharacteristicUUID = "6f63f4e0-251e-4374-970e-7fea2104788a";
