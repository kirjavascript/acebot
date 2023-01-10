# acebot

minimalist arduino powered tasbot-like replay device for NES

![](./acebot.png)

### parts needed

* nes controller
* arduino leonardo
* 128x64 OLED screen
* wires, soldering stuff

the screen is optional but useful for debugging

other arduino boards should work with minor adjustments

### circuit 

[controller pin diagram](https://content.instructables.com/FAS/BGIL/I4SCSNBA/FASBGILI4SCSNBA.jpg)

connect each controller button to a digital pin on the arduino

connect controller ground to arduino ground

connect controller latch to an interrupt pin on the arduino

read or change the code in `acebot.ino` for pin mapping

### playback

install the adafruit gfx drivers in arduino IDE or remove the display code


create a TAS in BizHawk and save a `tasproj` file
BizHawk's `Input Log.txt` from TAStudio
