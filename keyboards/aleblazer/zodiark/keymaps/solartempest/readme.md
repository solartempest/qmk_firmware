### --- Note: When flashing this firmware, be sure to load the VIA keymap and layout files otherwise your keys won't work! Please refer to the VIA section below. ---

# Zodiark Keyboard

![Zodiark](https://i.imgur.com/B7bDYeE.jpg)

Zodiark is a 68-key column-staggered split keyboard with per key RGB, rotary encoders, and 2x I2C headers per side. Created by Aleblazer.

Build guide is available here: [Zodiark build log/guide](https://www.splitlogic.xyz/buildguides/zodiark-build-guide)

* Keyboard Maintainer: [Solartempest]
* Hardware Supported: Zodiark, ProMicro / Elite-C, 1.3" 128x64 SSD1306 OLEDs, Pimoroni Trackball, Pimoroni Haptic Buzz!
* Hardware Availability: [Split Logic Group Buy - Discord Link](https://discord.gg/BCSbXwskVt)

# Custom Features:
### OLED Features:
-	OLED displays current layer, lock key status, WPM, custom pixel art, and custom name.
-	OLED shuts off on idle and when computer is sleeping.

### Trackball Features:
-   Supports Pimoroni Trackball installed on master side.
-	Default action is scrolling. Hold Raise layer for mouse mode.
-	Mouse mode and precision mode are toggleable with trackball LED indication.
-	Trackball LED shuts off when computer is sleeping (currently bugged).
-	Clicking and dragging is enabled using mouse keys on keymap.

### RGB Features:
-   Adds custom layer lighting with custom gradients for each layer.
-   Adds white caps lock, scroll lock, and num lock key indicators using the top row LEDs.

### Rotary Encoder and VIA Features:
-   Fully emappable left encoder controls volume up/down/mute. Right encoder left/right arrow keys.
-   Allows for  live remapping of per-layer rotary encoder functions in VIA.
-   VIA support included by default.
-   Custom macro key in VIA for Super Alt Tab, which is fully compatible with rotary encoders.
-   Custom macro key in VIA for moving windows to other monitors in Windows, which is fully compatible with rotary encoders.

### Haptic Feedback Features:
-   Supports Pimoroni Haptic Bzzz installed on master side.
-	Different vibrations when layers are activated.
-	Provides tactile feedback when trackball is clicked or mouse keys are used.
-	Tactile feedback for specific keys on gaming layer.

### Tap and Other Features:
-   Push left-shift + backspace to delete whole words. Right-shift + backspace to delete whole words in the opposite direction.
-   Double tap layers to stay on a layer instead of momentary push.

### Acknowledgements
-   Thanks Aleblazer for creating this great keyboard! Also thanks for sharing the VIA json which made addition of the rotary encoders in VIA much faster.
-   Thanks Drashna for the OLED timeout and extensible rotary encoder code.
-	Thanks Dasky for helping me resolve prior trackball code issues.
-	Thanks to Hellsingcoder for creating Luna and Jackasaur for optimizing the code for less space. This was the base code I used for my pixel art.

## Using with VIA (Important! Please Read.)

-   After flashing, in VIA make sure to Import Keymap, which is "zodiark VIA keymap.json". This will alow VIA to recognize the updated layout and custom functions. VIA will auto-recognize the default keyboard but that does not match this firmware because of the necessary customization.
-   Go to Save+Load to Load Saved Layout. You can import my own layout "zodiark VIA layout.json" or just use the Keymap tab to assign your own keys. Having another keyboard connected can be handy for doing this step.
-   It is a good idea to Save Current Layout after you decide on your mapping.


# Compiling

Compile with the command below:

```sh
# for Elite C with Left Side Master builds
qmk compile -kb aleblazer/zodiark -km solartempest
```

## Flashing

Flash using the correct command below or use QMK Toolbox. Specifying side during compile is unnecessary as Master Left is defined by default:

```sh
# for pro micro-based builds
qmk flash -kb aleblazer/zodiark  -km solartempest

# for Elite C or dfu bootloader builds
qmk flash -kb aleblazer/zodiark  -km solartempest
```

These commands can be mixed if, for example, you have an Elite C on the left and a pro micro on the right.
Press reset button on he keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
