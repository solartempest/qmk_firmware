# Atlantis PS17 Macropad

![Atlantis PS17](https://i.imgur.com/Y0rkPgA.jpg)

A 17-key macro pad with pushbutton rotary encoder and underglow RGB per key RGB and for the case.

For detailed instructions on using VIA and flashing, please refer to the sections further down the page!

* Keyboard Maintainer: solartempest
* Hardware Supported: Atlantis PS17 v2
* Hardware Availability: [rioo897](https://shop198276076.world.taobao.com/index.htm?spm=2013.1.w5002-23418336364.2.3f4d7d51DkVX3s)

# Custom Features:

-   Remappable rotary encoder controls volume up/down/mute.
-   Allows for remapping of per-layer rotary encoder functions in VIA.
-   VIA support included by default.
-   RGB underglow and matrix support and remapped to physical locations for nicer gradient and effects.
-   Adds custom layer lighting with custom gradients for each.
-   Custom macro key in VIA for Super Alt Tab, which is fully compatible with rotary encoders.
-   Custom macro key in VIA for moving windows to other monitors in Windows, which is fully compatible with rotary encoders.
-   Custom macro key in VIA for Stretch Timer. It animates the LEDs after 30 minutes as a reminder to stand up and stretch. Push to dismiss.
-   Adds key combo functionality for backspace, delete, and arrow keys. Plus+8/9 along with Enter+4/5/6/8.

## Make and Flashing

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb solartempest/ps17 -km via

To reset the board into bootloader mode, tap the Reset switch mounted on the bottom of the PCB.
Flash with QMK toolbox, auto-flash.

## Using with VIA

-   After flashing, in VIA make sure to Import Keymap, which is "ps17 VIA keymap.json". This will alow VIA to recognize the updated layout and custom functions. VIA will not auto-recognize the keyboard with this firmware because of the necessary customization.
-   Go to Save+Load to Load Saved Layout. You can import my own layout "ps17 VIA layout.json" or just use the Keymap tab to assign your own keys. Having another keyboard connected can be handy for doing this step.
-   It is a good idea to Save Current Layout after you decide on your mapping.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
