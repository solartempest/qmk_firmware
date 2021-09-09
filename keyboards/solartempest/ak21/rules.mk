# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#

BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes      # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
SLEEP_LED_ENABLE = no      # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes          # USB Nkey Rollover
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = yes      # Enable keyboard RGB underglow
RGB_MATRIX_ENABLE = no     # RGB matrix for individual LED control
RGB_MATRIX_DRIVER = WS2812 # Addressable LED strand driver (keep for RGBLIGHT too)
BLUETOOTH_ENABLE = no      # Enable Bluetooth
AUDIO_ENABLE = no          # Audio output
MIDI_ENABLE = no           # No midi
UNICODE_ENABLE = yes       # Unicode
COMBO_ENABLE = yes         # Tap combo chording
TAP_DANCE_ENABLE = yes     # Tap dance
LTO_ENABLE = yes           # Reduce firmware size
