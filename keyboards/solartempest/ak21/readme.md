# Atlantis AK21 Macropad

![Atlantis AK21]

A 21-key macro pad with pushbutton rotary encoder and underglow RGB per key RGB and for the case.

For detailed instructions on using VIA and flashing, please refer to the sections further down the page!

* Keyboard Maintainer: solartempest
* Hardware Supported: Atlantis AK21
* Hardware Availability: [rioo897](https://shop198276076.world.taobao.com/index.htm?spm=2013.1.w5002-23418336364.2.3f4d7d51DkVX3s)

## Make and Flashing

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb solartempest/ak21 -km via

To reset the board into bootloader mode, tap the Reset switch mounted on the bottom of the PCB.
Flash with QMK toolbox, auto-flash.

## Using with VIA

-   After flashing, in VIA make sure to Import Keymap, which is "ak21 VIA keymap.json". This will alow VIA to recognize the updated layout and custom functions. VIA will not auto-recognize the keyboard with this firmware because of the necessary customization.
-   Go to Save+Load to Load Saved Layout. You can import my own layout "as21 VIA layout.json" or just use the Keymap tab to assign your own keys. Having another keyboard connected can be handy for doing this step.
-   It is a good idea to Save Current Layout after you decide on your mapping.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
