VIA_ENABLE = yes						# VIA

MOUSEKEY_ENABLE = yes					# Mouse keys for keymap
BOOTMAGIC_ENABLE = lite   				# Enable Bootmagic Lite
LTO_ENABLE = no							# MCU has 256kB space - 4kB for the EEPROM

TD_LSFT_CAPSLOCK_ENABLE = yes			# Enable Jonavin's custom left shift keycode. Requires Tap Dance.
TAP_DANCE_ENABLE = yes					# Tap Dance
STARTUP_NUMLOCK_ON = yes				# Turns numlock on by default
ENCODER_DEFAULTACTIONS_ENABLE = yes		# Enable Jonavin's custom encoder actions

LEADER_ENABLE = no						# Leader keys
COMBO_ENABLE = no						# Combo keys
NKRO_ENABLE = yes						# NKRO


SRC += jonavin.c						# Includes code for Jonavin's custom functions
ifeq ($(strip $(ENCODER_DEFAULTACTIONS_ENABLE)), yes)
    OPT_DEFS += -DENCODER_DEFAULTACTIONS_ENABLE
endif
ifeq ($(strip $(TD_LSFT_CAPSLOCK_ENABLE)), yes)
    OPT_DEFS += -DTD_LSFT_CAPSLOCK_ENABLE
endif
ifeq ($(strip $(STARTUP_NUMLOCK_ON)), yes)
    OPT_DEFS += -DSTARTUP_NUMLOCK_ON
endif
