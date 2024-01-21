VIA_ENABLE = yes
MOUSEKEY_ENABLE = yes
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite

TD_LSFT_CAPSLOCK_ENABLE = yes
IDLE_TIMEOUT_ENABLE = yes
STARTUP_NUMLOCK_ON = yes
ENCODER_DEFAULTACTIONS_ENABLE = yes

LEADER_ENABLE = no			# Leader keys
COMBO_ENABLE = no			# Combo keys
TAP_DANCE_ENABLE = yes

LTO_ENABLE = no				# MCU has 256kB space - 4kB for the EEPROM.


SRC += jonavin.c
ifeq ($(strip $(ENCODER_DEFAULTACTIONS_ENABLE)), yes)
    OPT_DEFS += -DENCODER_DEFAULTACTIONS_ENABLE
endif
ifeq ($(strip $(TD_LSFT_CAPSLOCK_ENABLE)), yes)
    OPT_DEFS += -DTD_LSFT_CAPSLOCK_ENABLE
endif
ifeq ($(strip $(IDLE_TIMEOUT_ENABLE)), yes)
    OPT_DEFS += -DIDLE_TIMEOUT_ENABLE
endif
ifeq ($(strip $(STARTUP_NUMLOCK_ON)), yes)
    OPT_DEFS += -DSTARTUP_NUMLOCK_ON
endif
ifeq ($(strip $(COLEMAK_LAYER_ENABLE)), yes)
    OPT_DEFS += -DCOLEMAK_LAYER_ENABLE
endif