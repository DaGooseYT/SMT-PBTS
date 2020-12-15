#  3.2 Channel Bluetooth Speaker (SMT-PBTS)

This is the first ever DIY 3.2 Channel Portable Bluetooth Speaker to be published online. This project is experimental is not yet intended for everyday use. 

 **Features:**
  - 60w of output power
  - Very low overall THD (0.5% max.)
  - 3.2 channels; three mid-to-high range channels & two 3.5 inch subwoofers
  - BBE® sound enhancement¹
  - Battery pack cycle life enhancment; 3v overdischarge cell cutoff²
  - 8 hours of battery live (at 30w output power)³
  - 38hz - 20,000kHz frequency response
  - Bluetooth v4.1 connectivity (up to 66 feet range)
  - AUX switching input
  
  1. *Only when using XR1075 extention module*
  2. *Only when using 
  3. *Only when using four Samsung 35E cells*

## Schematic

The schematic for this project is located in `/schematic`. It is availible in .svg & .json (to be imported via EasyEDA) files for the source and .png in the releases. 

**Other notes:**
- R23-R26 are resistors in the LC low pass filters and the resistance values must be changed in order for the low pass filter to be effective. Use the LC filter formula to determine a cutoff frequency.
- R17 & R18 must be changed according to the output voltage gain of the amplifier.
- R5 & R6 set the gain for TPA3128D2. Refer to [TPA3128D2 datasheet](https://www.ti.com/lit/ds/symlink/tpa3128d2.pdf?ts=1607302833960) for help.

## PCB

The main and extension PCB sources are located in `/PCB`. There are two sources availible; one for Altium and one for EasyEDA. PCB gerbers are in the releases.

**Other notes:**
- U3 & U5 are input/output connectors for the XR1075 extension PCB. If you are not using it, brige the holes.
- C50 & C51 on the XR1075 extension module will most likely not be needed.
