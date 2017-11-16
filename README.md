DIY RC transmitter project

In order to get some experience with freertos I decided to build my own RC transmitter.
Goals:
- setup freertos for a cortex M4 board using a gcc-arm toolchain under linux/macosx from scratch.
- build my own transmitter

After I got the toolchain setup, and freertos running on the board I ran into something I completely underestimated:
- writing a GUI.

Status summary: 
Can I use this to fly my RC airplane? No.
Will it ever be possible? Maybe.. For now my intention is 

The GUI is far from complete, but I got it to a point where I see no difficulties anymore.

GUI - inputs:
The GUI uses a rotary encoder (up/down) and two buttons: select/back. Much like the old ipod interfaces you can click/scroll into a menu structure, and go back level-by-level.

GUI - statemachine:
The GUI uses a statemachine that is constructed using a structure with function pointers and some state data. 
Each function represents a state, eg. "showing menu".
In order to reduce the amount of state functions, I re-used the "showing menu" function. This functions displays different info on the display based on a menu structure in a doubly lined list.



