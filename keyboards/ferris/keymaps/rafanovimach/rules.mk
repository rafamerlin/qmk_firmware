MOUSEKEY_ENABLE 				= no    # Mouse keys
VIA_ENABLE      				= no    # Enable VIA
LTO_ENABLE      				= yes
COMMAND_ENABLE 					= no    # may be required for capsword
CAPS_WORD_ENABLE 				= yes
TAP_DANCE_ENABLE				= no
BOTH_SHIFTS_TURNS_ON_CAPS_WORD 	= yes
COMBO_ENABLE 					= yes
SEND_STRING_ENABLE 				= yes
EXTRAFLAGS += -flto
SRC += features/achordion.c
VPATH += keyboards/gboards

# Enable generic behavior for split boards
SPLIT_KEYBOARD 					= yes