# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
# Comment out to disable the options.

CONSOLE_ENABLE = no			# Console for debug (+4686)
BOOTMAGIC_ENABLE = no		# Virtual DIP switch configuration (+644)
MAGIC_ENABLE = no			# Save space by not PROCESS_MAGIC, which is bootmagic with out the boot (+634)
GRAVE_ESC_ENABLE = no		# Save space by not using KC_GESC (+127)
SPACE_CADET_ENABLE = no 	# Save space by not using space cadet left/right shift (+350)
LTO_ENABLE = yes			# Save space by link time optimization

MOUSEKEY_ENABLE = yes		# Mouse keys (+1482)
EXTRAKEY_ENABLE = yes		# Audio control and System control (+450)
NKRO_ENABLE = yes			# NKRO (+328)
RGBLIGHT_ENABLE = yes		# RGB lighting (+3826)
RGB_MATRIX_ENABLE = no		# RGB matrix for reactive effects (-1068)
RGB_MATRIX_DRIVER = WS2812	# Addressable LED strand driver
UNICODE_ENABLE = yes   	    # Unicode
ENCODER_ENABLE = yes		# Rotary encoders (+1112)
COMBO_ENABLE = yes         	# Tap combo chording (+952)
TAP_DANCE_ENABLE = no      	# Tap dance (+1008). Not VIA compatible.
