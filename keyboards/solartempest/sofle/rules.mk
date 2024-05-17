MCU = atmega32u4
BOOTLOADER = atmel-dfu

# Build Options
# Comment out to disable the options.

SPLIT_KEYBOARD = yes			# Split keyboard
CONSOLE_ENABLE = no				# Console for debug (+4686)
BOOTMAGIC_ENABLE = no			# Virtual DIP switch configuration (+644)
MAGIC_ENABLE = no				# Save space by not PROCESS_MAGIC, which is bootmagic with out the boot (+634)
GRAVE_ESC_ENABLE = no			# Save space by not using KC_GESC (+127)
SPACE_CADET_ENABLE = no 		# Save space by not using space cadet left/right shift (+350)
LTO_ENABLE = yes				# Save space by link time optimization

RGBLIGHT_ENABLE = yes			# RGB lighting (+3826)
ENCODER_ENABLE = yes			# Rotary encoders (+1112)
EXTRAKEY_ENABLE = yes			# Audio control and System control (+450)
MOUSEKEY_ENABLE = no			# Mouse keys (+1482). Not required for trackball usage.
NKRO_ENABLE = no				# 6KRO by default. NKRO works if enabled (+328)
COMBO_ENABLE = no				# Tap combo chording (+952)
#VIA							# VIA_ENABLE with the keymap (+2300). Note: VIA is required as non-via layouts were removed to save space.

OLED_ENABLE = yes				# Must be disabled if OLEDs are not installed (+3608-4774 with pet)
OLED_DRIVER = SSD1306			# Specify OLED driver
WPM_ENABLE = no					# WPM counter for typing-speed-reactive keyboard pets (+782)

POINTING_DEVICE_ENABLE = yes	# Enable Pimoroni Trackball on master (+2304)
POINTING_DEVICE_DRIVER = pimoroni_trackball

HAPTIC_ENABLE = no				# Enable Pimoroni Haptic Bzzz LRA (+1192)
HAPTIC_DRIVER += DRV2605L
