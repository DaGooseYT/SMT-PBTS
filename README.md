# Surface Mount Technology - Portable Bluetooth Speaker (SMT-PBTS)
![alt text][top]

[top]: https://github.com/DaGooseYT/SMT-PBTS/blob/main/pic/top.png "Top"

SMT-PBTS is an open source, Hi-Fi Bluetooth speaker PCB designed for the smallest, best sounding portable Bluetooth speaker applications. Just smaller than a deck of cards, it features multi-channel configurations for an immersive soundstage, a programmable audio DSP, Bluetooth v5.0 technology with external antenna support, 24-bit 192kHz Hi-Res audio support, and more.

## Key Features

- Ultra small and compact design; it’s smaller than a deck of cards.
- Bluetooth v5.0 specification via Qualcomm’s CSR8675 SoC.
- Connect up to 2 devices simultaneously for shared musical playback.
- Up to 800ft theoretical Bluetooth connectivity range using external antenna.
- Studio quality, Hi-Res audio playback with up to 24-bits and 192kHz sample rate support (only using AptX HD codec).
- Incredible, best in class frequency response; 35Hz-22KHz @-3dB (only with suggested drivers and enclosure).
- High efficiency eliminates the need for heatsinks.
- Hybrid amplifier design consisting of Class D amplifiers for the bass drivers and linear Class AB amplifiers for the left, right, and center tweeters.
- Ultra low total harmonic distortion, even at maximum power: ~0.05% THD.
- Ultra low signal to noise ratio: > 100dB
- 35W + 35W onboard Class D amplifiers with 3x1W Class AB amplifiers.
- Built in startup pop/thump suppression for the on-board amplifiers.
- Uses the highest audio quality preamplifier op-amps in existence: OPA4134, OPA2134 and OPA134.
- Uses high-end Panasonic acrylic resin film caps for all audio decoupling filters.

## Schematic

The schematic source for this project is located in `/src`. It is released as an EasyEDA source file. The SVG of the schematic is located in `/pic`.

## PCB

PCB sources are located in `/src`. The sources are EasyEDA PCB design filetypes. PCB gerbers are in the releases.

## BoM
- BoM is available as a .csv file in `/main`
- Only parts and components on the PCB are in the BoM.

## Suggested Enclosure Design

- Outer enclosure demensions are as follows (in): Length: 10.5; Width: 4.25; Depth: 3.5
- Speaker hole diameters (in): Left and right surround speakers: 1.9; two bass drivers: 3.5; center speaker: 1.9
- Connector, Port, and LED hole diameters (in): Power & AUX connectors: 0.5; LEDs: 3/16; Port: 5/8
- It is recommended to use polyfill in the enclosure for better frequency response and dampening. 
- The port of the enslosure is a PVC pipe with a inner diameter of 0.5 inches and is 9.75 inches in length (port tuning is between 35Hz - 40Hz).
- 0.25in thick MDF wood is reccomended for the speaker enclosure build.

## Suggested Drivers

- The two bass drivers are 3.5in in diameter and are manufactured by BH Acoustics (see [datasheet](https://cdn.komachine.com/media/product-catalog/bh-acoustic_84067_fngrun.pdf)). They were salvaged from two Samsung WAM1500 smart speakers. Due two the limited availability of these drivers, it is recomended to use [these other drivers](https://www.parts-express.com/dayton-audio-nd90-4-3-1-2-aluminum-cone-full-range-neo-driver-4-ohm--290-208?gclid=EAIaIQobChMI4NT3tpzQ7QIVxqeGCh1ngwkfEAQYASABEgL25PD_BwE) as an alternative.
- The center driver is a tweeter. It is rated at 10w 4ohm and was also pulled from a Samsung WAM1500. There is no other public documentation of this driver. [This](https://www.amazon.com/dp/B00LSEVA8I/ref=sspa_dk_detail_4?psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExMjNDVFhLNklCVUdHJmVuY3J5cHRlZElkPUEwMTM0NTc4MTI4WFROUlVBVEI5OCZlbmNyeXB0ZWRBZElkPUEwNDU2MDk1MzIyMkdWSDRQRE5BNSZ3aWRnZXROYW1lPXNwX2RldGFpbDImYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl) driver can be used instead. 
- The two surround speakers can be found [here](https://a.co/d/8RPXRJ0).

## I/) Connectors
- Power input via 5.5mm power jack. Buy it [here](https://www.parts-express.com/21-x-55mm-dc-coaxial-power-snap-in-jack--090-5030)
- This PCB features Bluetooth v5.0 using the BTM875-B Bluetooth module. The module can be reprogrammed to change the device's name as well as other properties using [this](https://www.digikey.com/short/0d7541zq) debugger.

## Other Componants
- The pre-modulated 4s BMS PCB can be found [here](https://a.co/d/1r3xPFF)
- Samsung 50E 21700 battery cells can be found [here](https://www.18650batterystore.com/products/samsung-50e)
- To prevent fire, use 20AWG wires or better for the power connections and TPA3128D2 output connections.
- 16.8V 2A lithium ion battery charger can be found [here](https://a.co/d/1eIaQfp)

## Licensing
This repo is licensed under the GPL v3.0. Any images are licensed under CC BY-SA 3.0.
