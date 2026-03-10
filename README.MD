This repository contains code for creating an IOT using HALOW.

**Hardware**
---
I am starting off with the following hardware:

Wi-Fi HaLow Transceiver for Seeed Studio XIAO

LINK: https://www.seeedstudio.com/Wio-WM6180-Wi-Fi-HaLow-Module-for-XIAO-p-6395.html

Seeed Studio XIAO

LINK: https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html

**Architecture**
---
conceptually, we are essentially bringing SDWAN to IOT; the esp32 will connect to a 2.4ghz wifi network, then use a software implementation of packet forwarding to send traffic via the wi-fi HALOW radio attachment. Could I try to figure out ethernet over 8x gpio pins? maybe. Do I want to waste time trying to do that? Not unless bandwidth is absolutely abysmal using the software method. 

router -> esp32 2.4 ghz network interface -> Nat'd & forwarded -> HALOW access point -> HALOW clients

We will want both a bridge mode and a client mode, so you can implement an esp32s3 with this radio as a client device, for example if you wanted to run an IOT sensor. 
