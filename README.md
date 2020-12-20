#  3.2 Channel Bluetooth Speaker (SMT-PBTS)

This is the first ever DIY 3.2 Channel Portable Bluetooth Speaker to be published online. This project is experimental is not yet intended for everyday use. 

 **Features:**
  - 60w of output power
  - Very low overall THD (0.5% max.)
  - 3.2 channels; three mid-to-high range channels & two 3.5 inch subwoofers
  - BBE® sound enhancement¹
  - Battery pack cycle life enhancment; 3v overdischarge cell cutoff²
  - 8 hours of battery live (at 30w output power)³
  - 38Hz - 20,000kHz frequency response
  - Bluetooth v4.1 connectivity (up to 66 feet range)
  - AUX switching input
  
  1. *Only when using XR1075 extention module*
  2. *Only when using S-8254AAWFT IC in the bms*
  3. *Only when using four Samsung 35E cells*

## Schematic

The schematic for this project is located in `/schematic`. It is availible in .svg & .json (to be imported via EasyEDA) files for the source and .png in the releases. 

**Other notes:**
- R23-R26 are resistors in the LC low pass filters and the resistance values must be changed in order for the low pass filter to be effective. Use the LC filter formula to determine a cutoff frequency.
- R15 is a resistor in a LC high pass filter for the center channel and the resistance values must be changed in order for the high pass filter to be effective. Use the LC filter formula to determine a cutoff frequency.
- R17 & R18 must be changed according to the output voltage gain of the amplifier. 
- R21 & R22 control the crosstalk between surround channels. Higher resistance increases the cross talk, but will also increase the phase seperation (closer to 180° out of phase).
- R5 & R6 set the gain for TPA3128D2. Default gain is 36dB in the PCB. Refer to [TPA3128D2 datasheet](https://www.ti.com/lit/ds/symlink/tpa3128d2.pdf?ts=1607302833960) for help.

## PCB

The main and extension PCB sources are located in `/PCB`. There are two sources availible; one for Altium and one for EasyEDA. PCB gerbers are in the releases.

**Other notes:**
- L & R are input/output connectors (next to KRC-86B v4.0) for the XR1075 extension PCB. If you are not using it, brige the holes.
- C50 & C51 on the XR1075 extension module will most likely not be needed, as LC low pass filters are already applied in the main PCB.
- If you use a larger enclosure/smaller drivers for the speaker, then XR1075 module may not be needed.
- R16 is a 1/2w carbon film resistor (1K ±5%) and is not listed on the PCB. Please connect this externally from the PCB.
- BTLED is a blue 5mm LED and PWRLED is a 5mm green LED

## BoM
- BoM is availible in .csv file
- Only parts and componants on the PCBs are in the BoM. Please refer to the other sections of this README to find other additional parts for the project.

## Enclosure 

- Outer enclosure demensions are as follows (when looking at the front & in inches. Sorry metric users you will have to convert the measurements on your own!): Length: 10.5; Width: 4.25; Depth: 3.5
- Speaker hole diameters (also in inches): Left and right surround speakers: 1.9; two bass drivers: 3.5; center speaker: 1.9
- Connector, Port, and LED hole diameters (again.. in inches): Power & AUX connectors: 0.5; LEDs: 3/16; Port: 5/8
- It is reccomended to use polyfill in the enclosure for better frequency response around the port tuning frequency. 
- The port of the enslosure is simply a PVC pipe with a inner diameter of 0.5 inches and is 9.75 inches in length (port tuning is between 39Hz - 40Hz). Due to Hoffman's Iron Law, the speaker will suffer in efficiency from the small enclosure & narrow port but will have a deep frequency response. A port was used due to no room for a passive radiator.
- 0.25 inch thick MDF wood is reccomended for the speaker enclosure build.

## Drivers

- The two bass drivers are 3.5 inches in diameter and are manufactured by BH Acoustics (see [datasheet](https://cdn.komachine.com/media/product-catalog/bh-acoustic_84067_fngrun.pdf)). They were pulled from two Samsung WAM1500 smart speakers. Due two the limited availibility of these drivers, it is recomended to use [these other drivers](https://www.parts-express.com/dayton-audio-nd90-4-3-1-2-aluminum-cone-full-range-neo-driver-4-ohm--290-208?gclid=EAIaIQobChMI4NT3tpzQ7QIVxqeGCh1ngwkfEAQYASABEgL25PD_BwE) as an alternative.
- The center speaker is simply a tweeter that has been physically modified to play frequencies as low as 160Hz. It is rated at 10w 4ohm and was also pulled from Samsung WAM1500. There is no other documentation of this tweeter online. Please use [this](https://www.amazon.com/dp/B00LSEVA8I/ref=sspa_dk_detail_4?psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExMjNDVFhLNklCVUdHJmVuY3J5cHRlZElkPUEwMTM0NTc4MTI4WFROUlVBVEI5OCZlbmNyeXB0ZWRBZElkPUEwNDU2MDk1MzIyMkdWSDRQRE5BNSZ3aWRnZXROYW1lPXNwX2RldGFpbDImYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl) driver instead. 
- The two surround speakers can be found [here](https://www.amazon.com/AIYIMA-Portable-Speakers-Loudspeaker-Accessories/dp/B07CWMCMQR/ref=sr_1_4?dchild=1&keywords=2+inch+speaker&qid=1608043699&sr=8-4).

## Inputs 
- AUX input via 3.5mm audio jack. Buy it [here](https://www.parts-express.com/35mm-stereo-gold-plated-snap-in-jack--090-281)
- Power input via 5.5mm power jack. Buy it [here](https://www.parts-express.com/21-x-55mm-dc-coaxial-power-snap-in-jack--090-5030)
- This project features Bluetooth v4.1 using the KRC-86B v4.0 Bluetooth module. The module can be reprogrammed to change the device's name as well as other features using a special microcontroller and some software. Follow the directions below to learn how to reprogram a CSR Bluetooth device: 
1. First you will need the special CSR microcontroller USB-SPI converter. You can buy the original one [here](https://www.aliexpress.com/item/32775070191.html?src=google&albch=shopping&acnt=494-037-6276&isdl=y&slnk=&plac=&mtctp=&albbt=Google_7_shopping&aff_platform=google&aff_short_key=UneMJZVf&&albagn=888888&albcp=9824643245&albag=103112554314&trgt=901524112532&crea=en32775070191&netw=u&device=c&albpg=901524112532&albpd=en32775070191&gclid=CjwKCAiA_eb-BRB2EiwAGBnXXndOKJJVaxX_gCD3rRJvCNkSjhx2zsD4KVPEarOYSEoiylvzrDLkuxoCNq0QAvD_BwE&gclsrc=aw.ds). If you don't want to pay the expensive price and/or don't want to wait for the shipping from China, then use [this new microcontroller](https://www.digikey.com/en/products/detail/qualcomm-technologies-international,-ltd./DK-USB-SPI-10225-1A/5269739?utm_adgroup=Programmers%2C%20Emulators%2C%20and%20Debuggers&utm_source=google&utm_medium=cpc&utm_campaign=Shopping_Product_Development%20Boards%2C%20Kits%2C%20Programmers_NEW&utm_term=&utm_content=Programmers%2C%20Emulators%2C%20and%20Debuggers&gclid=CjwKCAiA_eb-BRB2EiwAGBnXXkE3N6KQK4NOpo7lJF4k9YGp8LHvVVaPRt-t7ffovO93XN6W43aERhoCHx8QAvD_BwE) shipped and sold in the US as a cheaper alternative. A mini USB to USB A cable that supports data transfer will also be required.
2. Download and install [CSR Bluesuit v2.6.6](https://drive.google.com/file/d/1OHdcJ7Q7dSbCMiuglO7hV6pjNrMVJkaL/view?usp=sharing) (Windows only). After installation, go to `C:\Program Files (x86)\CSR\BlueSuite 2.6.6` in file explorer. Connect your CSR USB-SPI converter to your computer. Connect the jumper wires from the microcontroller to the SPI female headers on the main PCB. The connections are labeled on both the PCB and the CSR USB-SPI modules. If you are using the new CSR SPI-USB module, then you will need to use an external power source to power the KRC-86B due to 3v being too low for its operation.
3. Open PStool.exe. Ensure `SPI BCCMD` bubble is selected. Your USB-SPI converter should show up in the dropdown next to `SPI BCCMD` (note: third party USB-SPI converters will not show up here; only CSR devices). Select OK.
4. In the *Filter* textbox, type `name`. Select the change user friendly name in the list (should be the only one in the list) and there you can change the device name.
5. After you have set the name, select the `set` button, then you can close PStool. All done!

## Other
- The pre-modulated 4s BMS PCB can be found [here](https://www.amazon.com/Anmbest-Charger-Protection-Lithium-Battery/dp/B07KSPX859/ref=sr_1_12?dchild=1&keywords=4s+bms&qid=1608227266&sr=8-12)
- Samsung 35E 18650 battery cells can be found [here](https://www.18650batterystore.com/products/samsung-35e)
- For fire prevention, use 20AWG wires or better for the power connections and TPA3128D2 output connections.
- KRC-86B v4.0 Bluetooth module can be found [here](https://www.amazon.com/HiLetgo-KRC-86B-Bluetooth-Receiver-Amplifier/dp/B071Z7S3JL/ref=sr_1_3?crid=2S69IR6LEVEXN&dchild=1&keywords=krc-86b&qid=1608305471&sprefix=krc-86%2Caps%2C154&sr=8-3)

## Disclaimer & Licenses
- Licenses are located in `/License`. By using the contents in this repository, you automatically agree to the terms and conditions in the licenses as well as the disclaimers listed below.
- License1 covers the software aspects of this repository including the schematic, PCB source, PCB gerber, etc.
- License2 covers the hardware aspects of the project including the contentes in `/Photos`, enclosure design, and overall design of the speaker.
- The contents of this project are NOT risk-free of failure and therefore must be proofchecked by the user before use. The user assumes responsibility for any damages caused by electrical/mechanical failures.
- Soldering lithium-ion batteries can be dangerous! Proper use and knowledge of the risks associated with the use of lithium-ion batteries must be considered by the user before attempting to create a battery pack.
- Some components used in the PCBs are microscopic and require special microsoldering skills to assemble. This process is not for the "faint of heart" nor should be attempted if you don't have the right equipment. 
- This project is the first ever DIY 3.2 Channel Portable Bluetooth Speaker to be published online based on *my own research only.*
- ***I can't hold your hand through every step and procedure in this project.*** You must have prior knowlage in electronics, physics, and other necessary skills in order to contruct this speaker. Please report problems in the issues page.
