# Custom firmware configuration guide
SMT-PBTS uses Qualcomm's CSR8675 via the BTM875-E module for Bluetooth radio music streaming. SMT-PBTS requires a specific firmware configuration in order for everything to function as expected. The default firmware I configured myself for my specific application is in the releases. However, your application will be slightly different and therefore it is highly recommended to create your own firmware for the best quality results. This guide will show you the general steps for the correct custom firmware configuration.

## Requirements
- [This](https://www.digikey.com/short/0d7541zq) USB-SPI programmer
- Texas Instruments [PurePath Studio](https://www.ti.com/tool/AICPUREPATH_STUDIO) (proprietary, requires registration)
- CSR867X ADK v4.3.1.5 - software development kit (proprietary, you must find on your own)
- Knowledge of the C programming language
- Knowledge of Qualcomm's xIDE and standard library (I won't discuss its usage in this guide, please read its docs)
- Knowledge of the I2C bus protocol

## Configuring PurePath code
<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/gde.png" width="650"/>
</p>

Use GDE in the PurePath portable installation to configure the AIC3254 to your liking. The photo above is the configuration used in the firmware I have configured for my specific application. Be sure to use I2S as the input and set the PLL clock to BCLK (this can be found in the AIC3254 app configuration block). The left output channel is for the surround tweeters and the right output is for the center tweeter.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/vscode.png" width="650"/>
</p>

Above is the assembled output code from the GDE configuration. This code must be tweaked in order to be compatible with the CSR8675 firmware that we will build soon. The code lines starting with 'd' must be removed entirely. Delay is not supported in the CSR8675 firmware. The '>' ressembles register incrementation from the previous line which is also not supported and so you must convert these to register values in hex too.

## Adding code to the sink application

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/xide.png" width="640"/>
</p>

Open xIDE in the ADK v4.3.1.5 installation folder and use one of the sample sink app workspaces in the `/apps` directory as a template for your firmware (I recommend the `soundbar.xiw` sample). Also add any of the decoders that you would like (AAC, MP3, aptX-HD, etc.) by going to `Project > Insert project to workspace` and selecting the kalimba project files (in `/a2dp_sink` directory) relating to the codecs that you would like configured.<br />
Create functions and add the code assembled from PurePath GDE into the `main.c` file in the `vm - soundbar` xIDE project. See the `main.c` file in this repository's `/src` folder for a complete example. The example file has the I2C library functions set up and demonstrates the function usage for all relevant code.<br />
Finally, change the configuration properties of the `vm - soundbar` project so that the device is set to CSR8675, the transfer is SPI, and wired audio is enabled (for I2S). You can configure other properties such as subwoofer link, hi-res audio output and more there too, but is completely optional. Be aware though that the CSR8675 on the BTM875-E module only has 16MB of flash memory. Make sure you don't have everything enabled in the project properties as the device will not have enough storage for all of the features! Open the `speaker.mak` file in the `vm -speaker` project and uncomment the A2DP decoder compilation paths for the decoders that you have added to the workspace. 

## Flashing the CSR8675

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/debug.png" width="640"/>
</p>

Go to `Debug > run` in xIDE after you have configured all of the code and properties. **Make sure the BTM875-E and the USB-SPI module is connected to your computer and the CSR8675 chip is erased (use BlueFlash.exe in the ADK installtion folder), else it will fail.** It could take several minutes to compile and assemble all of the code. After all compilation is complete, the firmware will automatically flash itself to the CSR8675 device. 

## Persistent store keys configuration

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/psi2c.png" width="660"/>
</p>

Open PSTool and merge the `sink_system_csr8675.psr` default file located in the `/configurations` folder of your sink project directory.<br />
Search i2c in the search box and change the I2C configuration key value to 1 as shown above. This is for I2C fast mode enable.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/psscl.png" width="660"/>
</p>

Set the SCL pin to 0007 as shown above for PIO7 according to the hardware configuration on the SMT-PBTS PCB.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/pssda.png" width="660"/>
</p>

Set the SDA pin to 0003 as shown above for PIO3 according to the hardware configuration on the SMT-PBTS PCB.<br />
Now switch off the MFB switch on the SMT-PBTS PCB and then unplug the battery. Plug back in the battery connector and then switch on the MFB switch to turn on the module.

## ADK configuration settings

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/channels.png" width="650"/>
</p>

Now open the ADK Configuration Tool located in the ADK v4.3.1.5 installation folder. With the USB-SPI module still connected to the SMT-PBTS PCB, select the USB-SPI in the connection drop-down menu and then select the `Go Configurable` button. Once the device configurations loads, select the `Read device` button.<br />
Go to `Audio > Output > Channel Allocation` in the menu and set the configuration to the picture as shown above.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/i2c.png" width="650"/>
</p>

Now go to `Audio > I2S` and set the configurations to the picture as shown above.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/pio.png" width="650"/>
</p>

Lastly, go to `Input/Output > Output PIOs` and set the configuration to the picture as shown above in accordance to the hardware configuration on the SMT-PBTS PCB. In the `PIO Invert Mask Bitfields` menu, also invert PIO2 by selecting the checkbox next to it. You may configure other settings, such as changing the LED sequence and start-up tones in the other menus. Once finished, select `Write device` to add the configuration to the CSR8675 and then select `Go normal` to make the module run normally.

## DSP configuration

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/ufe.png" width="630"/>
</p>

At last, open UniversalFrontEnd in the ADK v4.3.1.5 installation directory and then select `music manager` in the menu. Select your USB-SPI device in the menu. **Make sure music is playing before you connect else you will get an error. Make sure music plays for the rest of this part of the guide to prevent problems.** Once connected, select the sunglasses-looking icon on the top of the program to monitor the DSP memory in real-time. Your screen should look like the one pictured above. To apply changes that you make to all decoders, select the `Decoder` block and then select all relevent checkboxes.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/co.png" width="630"/>
</p>

Select the `Cross over` block to see the crossover menu and configure it to what you see in the photo above. Select OK to apply the changes.

<p align="center">
  <img align="top" src="https://github.com/DaGooseYT/SMT-PBTS/blob/main/src/pic/eq.png" width="680"/>
</p>

Select the `Speaker EQ` block to see the DSP equilizer. Set this accoding to your liking. DSP EQ tuning can take a lot of time for the perfect configuration so be sure to have patience when testing different EQ configs. The 10th EQ band for some reason doesn't work and if you select the checkbox the app will crash. The DSP EQ config shown in the photo above is the one I made for my application. Yours will most likely look very different!<br /><br />
This concludes the firmware configuration guide. I did not provide much details as far as the usage of these tools because I expect that you already know how to use them. If you don't, please refer to the documentation for each of them. **Please refrain from opening issues regarding usage of the tools; I won't hold your hand through each little step not mentioned in this guide.**
