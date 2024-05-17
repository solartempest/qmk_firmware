# Atlantis 9e Macropad

![Atlantis 9e](https://i.imgur.com/hFuZyXU.jpg)

A 18-key macro pad with 9 pushbutton rotary encoders and underglow RGB per key RGB and for the case.

For detailed instructions on using VIA and flashing, please refer to the sections further down the page!

* Keyboard Maintainer: solartempest
* Hardware Supported: Atlantis 9e
* Hardware Availability: [rioo897](https://shop198276076.world.taobao.com/index.htm?spm=2013.1.w5002-23418336364.2.3f4d7d51DkVX3s)

# Custom Features:

-   9 remappable rotary encoder controlling a variety of different things!
-   RGB underglow support and remapped to physical locations.
-   When turning the 3 large rotary encoders the RGB LEDs underneath animate.
-   Adds custom layer lighting with custom gradients for each and static colours for the switches.
-   Adds white caps lock, scroll lock, and num lock key indicators on the top row.
-   VIA support included by default.
-   Allows for remapping of per-layer rotary encoder functions in VIA.
-   Custom macro key in VIA for Super Alt Tab, which is fully compatible with rotary encoders.
-   Custom macro key in VIA for moving windows to other monitors in Windows, which is fully compatible with rotary encoders.
-   Stretch timer (reminder to stop sitting) animates LEDS after 30 minute interval. LED indicator is red and timer is toggled.


## Flashing

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb solartempest/9e -km via

-   Please note that QMK toolbox and configurator cannot be used to flash this board.
-   You will need to use an ISP Programmer to directly flash the 9e. No board reset is required, as you will flash the MCU directly.
-   I used Prog ISP V2.0 but other AVR programmers will also work.
-   Use a 12P AWM 20624 ribbon cable with FCP-12P-1.0mm breakout board. Only 10 pins are used.
-   Plug in the ribbon cable with the data pins facing away from the PCB.

## Using with VIA

-   After flashing, in VIA make sure to Import Keymap, which is "9e VIA keymap.json". This will alow VIA to recognize the updated layout and custom functions. VIA will not auto-recognize the keyboard with this firmware because of the necessary customization.
-   Go to Save+Load to Load Saved Layout. You can import my own layout "9e VIA layout.json" or just use the Keymap tab to assign your own keys. Having another keyboard connected can be handy for doing this step.
-   It is a good idea to Save Current Layout after you decide on your mapping.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
