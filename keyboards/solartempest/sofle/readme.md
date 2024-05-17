### --- Note: When flashing this firmware, be sure to load the VIA keymap and layout files otherwise your keys won't work! Please refer to the VIA section below. ---

# Sofle Keyboard

![SofleKeyboard version 2.1 RGB Keyhive](https://i.imgur.com/utkZbYS.jpeg)

Sofle is a 58-key column-staggered split keyboard with rotary encoders and OLEDs with support for a trackball and haptic feedback. Based on Lily58, Corne and Helix keyboards.

For details about the keyboard design, refer to Josef's blog: [Sofle Keyboard - a split keyboard based on Lily58 and Crkbd](https://josef-adamcik.cz/electronics/let-me-introduce-you-sofle-keyboard-split-keyboard-based-on-lily58.html)

Build guide and log is available here: [SofleKeyboard build log/guide](https://josef-adamcik.cz/electronics/soflekeyboard-build-log-and-build-guide.html)

* Keyboard Maintainer: [Solartempest]
* Hardware Supported: SofleKeyboard V2.1 RGB PCB, ProMicro / Elite-C
* Hardware Availability: [Keyhive](https://keyhive.xyz/shop/sofle)

# Custom Features:
### OLED Features:
-   Includes Snakey keyboard pet! Slithers according to WPM, bites, and sticks its tongue out at you!
-   Includes Snakey minimal version, with less animations and WPM-free to allow for more free space.
-	OLED displays current layer, lock key status, WPM, custom logo, and custom name.
-	OLED shuts off on idle and when computer is sleeping.
-	Includes working Luna keyboard pet.
-	Includes working Bongocat (disable other features for sufficient space).
-   Includes stock OLED code as well.

### Trackball Features:
-   Supports Pimoroni Trackball installed on master side.
-	Default action is scrolling. Hold Raise layer for mouse mode.
-	Mouse mode and precision mode are toggleable with trackball LED indication.
-	Trackball LED shuts off when computer is sleeping.
-	Clicking and dragging is enabled using mouse keys on keymap.

### RGB Features:
-   Adds custom layer lighting with custom gradients for each layer.
-   RGB underglow support and remapped to physical locations (nicer gradients and effects).
-   Adds white caps lock, scroll lock, and num lock key indicators using the top row/underglow LEDs.

### Rotary Encoder and VIA Features:
-   Fully emappable left encoder controls volume up/down/mute. Right encoder PGUP/PGDOWN.
-   Allows for  live remapping of per-layer rotary encoder functions in VIA.
-   VIA support included by default.
-   This fixes the Keyhive left bottom row offset issue in VIA. You will need to import sofle.json in VIA.
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
-   Symmetric modifiers (CMD/Super, Alt/Opt, Ctrl, Shift).

### Acknowledgements
-   Thanks Drashna for the OLED timeout and extensible rotary encoder code.
-	Thanks Dasky for helping me resolve prior trackball code issues.
-	Thanks to Hellsingcoder for creating Luna and Jackasaur for optimizing the code for less space. This was the base code I used for Snakey.
-	Bongocat code by foureight84, included for those who want to try it easily.
-	Stock OLED code by Keyhive and 

## Using with VIA (Important! Please Read.)

-   After flashing, in VIA make sure to Import Keymap, which is "sofle VIA keymap.json". This will alow VIA to recognize the updated layout and custom functions. VIA will not auto-recognize the keyboard with this firmware because of the necessary customization.
-   Go to Save+Load to Load Saved Layout. You can import my own layout "sofle VIA layout.json" or just use the Keymap tab to assign your own keys. Having another keyboard connected can be handy for doing this step.
-   It is a good idea to Save Current Layout after you decide on your mapping.


# Compiling

Compile with the command below:

```sh
# for Elite C with Left Side Master builds
qmk compile -kb solartempest/sofle -km via
```

## Flashing

Flash using the correct command below or use QMK Toolbox. Specifying side during compile is unnecessary as Master Left is defined by default:

```sh
# for pro micro-based builds
qmk flash -kb solartempest/sofle -km via

# for Elite C or dfu bootloader builds
qmk flash -kb solartempest/sofle -km via
```

These commands can be mixed if, for example, you have an Elite C on the left and a pro micro on the right.
Press reset button on he keyboard when asked.

Disconnect the first half, connect the second one and repeat the process.


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
