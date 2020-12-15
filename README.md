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
- R17 & R18 must be changed according to the output voltage gain of the amplifier.
- R5 & R6 set the gain for TPA3128D2. Default gain is 36dB in the PCB. Refer to [TPA3128D2 datasheet](https://www.ti.com/lit/ds/symlink/tpa3128d2.pdf?ts=1607302833960) for help.

## PCB

The main and extension PCB sources are located in `/PCB`. There are two sources availible; one for Altium and one for EasyEDA. PCB gerbers are in the releases.

**Other notes:**
- U3 & U5 are input/output connectors for the XR1075 extension PCB. If you are not using it, brige the holes.
- C50 & C51 on the XR1075 extension module will most likely not be needed, as LC low pass filters are already applied.

## Enclosure 

- Enclosure demensions are as follows (when looking at the front & in inches. Sorry metric users you will have to convert the measurements on your own!): Length: 10.5, Width: 4.25, Depth: 3.5
- The port of the enslosure is simply a PVC pipe with a inner diameter of 0.5 inches and is 9.75 inches in length (port tuning is between 39Hz - 40Hz. Due to Hoffman's Iron Law, the speaker will suffer in efficiency but will have a deep frequency response.
- 

## Drivers

- The two 3.5 inch drivers are manufactured by BH Acoustics (see [datasheet](https://cdn.komachine.com/media/product-catalog/bh-acoustic_84067_fngrun.pdf)). They were pulled from two Samsung WAM1500 smart speakers. Due two the limited availibility of these drivers, it is recomended to use [these drivers](https://www.parts-express.com/dayton-audio-nd90-4-3-1-2-aluminum-cone-full-range-neo-driver-4-ohm--290-208?gclid=EAIaIQobChMI4NT3tpzQ7QIVxqeGCh1ngwkfEAQYASABEgL25PD_BwE) as an alternative.
- The center speaker is simply a tweeter that has been physically modified to play frequencies as low as 160Hz. It is rated at 10w 4ohm and was also pulled from Samsung WAM1500. There is no other documentation of this tweeter online. Please use [this](https://www.amazon.com/dp/B00LSEVA8I/ref=sspa_dk_detail_4?psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExMjNDVFhLNklCVUdHJmVuY3J5cHRlZElkPUEwMTM0NTc4MTI4WFROUlVBVEI5OCZlbmNyeXB0ZWRBZElkPUEwNDU2MDk1MzIyMkdWSDRQRE5BNSZ3aWRnZXROYW1lPXNwX2RldGFpbDImYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl) driver instead. 
- The two surround speakers can be found [here](https://www.amazon.com/AIYIMA-Portable-Speakers-Loudspeaker-Accessories/dp/B07CWMCMQR/ref=sr_1_4?dchild=1&keywords=2+inch+speaker&qid=1608043699&sr=8-4).
