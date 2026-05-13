# ESP32-PS4-Interface

Use the PS4 controller with the ESP32. Developed for NJIT-ARPA 2026

###### Licensed under GPLv3. Derivations must be openly redistributed

## Features

- ✅ PS4 Controller Bluetooth Interface
- ✅ OTA Firmware Updates
- ✅ Watchdog Timer for Crash Recovery
- ✅ EEPROM Configuration Storage
- ✅ Battery Monitoring with Alerts
- ✅ Production-Ready Logging System
- ✅ CI/CD Pipeline

## Pinouts

### MEGA2560 R3:
RX1 / 19

Connect ground to ground!

## Installation

1. Clone this repository
2. Copy `private.ini.template` to `private.ini`
3. Edit `private.ini` with your MAC address
4. Upload to ESP32

## Configuration

Edit `private.ini`:
- `PS4_TARGET_MAC`: MAC address of paired device
- `FW_VERSION`: Firmware version
- `ENABLE_WATCHDOG`: Enable/disable watchdog timer
- `ENABLE_OTA`: Enable/disable OTA updates
- `ENABLE_LOGGING`: Enable/disable logging

## OTA Updates

1. Ensure device is connected to WiFi
2. Upload new firmware via Arduino IDE or PlatformIO
3. Device will verify signature and rollback on failure

## Battery Monitoring

- Green LED: Battery > 25%
- Orange LED: Battery 15-25%
- Red LED: Battery < 15%

## Watchdog Timer

- Resets device if no activity for 10 seconds
- Can be disabled in `private.ini`

## Logging

Logs are stored in EEPROM and can be retrieved via Serial.

## Troubleshooting

### Device won't connect
- Check MAC address in `private.ini`
- Ensure PS4 controller is in pairing mode
- Check Bluetooth antenna connection

### OTA fails
- Verify WiFi connection
- Check password in `platformio.ini`
- Ensure device has enough free memory

### Watchdog resets device
- Increase timeout in `private.ini`
- Check for infinite loops in code

## Version

Current version: 1.0.0

## License

GPLv3

## Contributing

1. Fork the repository
2. Create a feature branch
3. Submit a pull request

## Security

- OTA updates are signed
- Password protection enabled
- Secure boot verification

## Support

For issues, please open a GitHub issue.
