# Onbus

The Onbus Device Firmware is a sophisticated solution designed for efficient access control and monitoring. Leveraging the PN532 module NFC (Near Field Communication) technology and NFC swipe cards, this firmware offers a comprehensive set of features:

NFC Card Integration:

The firmware seamlessly integrates with the PN532 module NFC technology, allowing the device to read NFC swipe cards.
Card ID Extraction:

Whenever an NFC swipe card is presented to the device, it swiftly extracts the unique card ID embedded in the card.
ESP32 Integration:

The firmware interfaces with the ESP32 microcontroller, a powerful and versatile platform for processing data and communication.
Mac Address Inclusion:

In addition to the card ID, the firmware also captures the ESP32's MAC address, creating a secure and unique data pair.
Endpoint Communication:

Upon card swipe, the extracted card ID and ESP32 MAC address are sent to a designated endpoint, ensuring real-time access control and monitoring.
Sim800 Integration:

The firmware is also equipped with integration for the Sim800 module, enabling the device to fetch status details and error messages.
OLED Display:

To enhance user interaction and feedback, the firmware supports a 0.91-inch OLED display. This display is utilized to present status details and error messages fetched from the Sim800 module, ensuring immediate visibility to the user.
 
