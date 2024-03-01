/* Copyright (C) 2023 Giovanni Cascione <ing.cascione@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LIBRETRO_MAPPER_H
#define LIBRETRO_MAPPER_H

#include <libretro.h>
#include "common/keyboard.h"

#define RETRO_DEVICE_KEY_STATUS         0
#define RETRO_DEVICE_KEY_PREV_STATUS    1
#define RETRO_DEVICE_KEY_CHANGED        2

#define RETRO_DEVICE_ID_JOYPAD_ANALOG   16

#define RETRO_DEVICE_ID_JOYPAD_LR       16
#define RETRO_DEVICE_ID_JOYPAD_LL       17
#define RETRO_DEVICE_ID_JOYPAD_LD       18
#define RETRO_DEVICE_ID_JOYPAD_LU       19
#define RETRO_DEVICE_ID_JOYPAD_RR       20
#define RETRO_DEVICE_ID_JOYPAD_RL       21
#define RETRO_DEVICE_ID_JOYPAD_RD       22
#define RETRO_DEVICE_ID_JOYPAD_RU       23

#define RETRO_DEVICE_ID_JOYPAD_LAST     24

#define RETROKE_VKBD -1
#define RETROKE_LEFT -2
#define RETROKE_UP -3
#define RETROKE_DOWN -4
#define RETROKE_RIGHT -5
#define RETROKE_LEFT_BUTTON -6
#define RETROKE_RIGHT_BUTTON -7
#define RETROKE_FINE_CONTROL -8
#define RETROKE_SCUMMVM_GUI -9
#define RETROKE_SHIFT_MOD -10
#define RETROKE_CTRL_MOD -11
#define RETROKE_ALT_MOD -12

/* libretro.cpp functions */
extern retro_input_state_t retro_input_cb;
extern int retro_setting_get_analog_deadzone(void);
extern bool retro_get_input_bitmask_supported(void);

struct retro_keymap {
	int retro_id;
	int scummvm_id;
	const char *value;
};

static const struct retro_keymap retro_keys[] = {
	{0, 0, "---"},
	{RETROKE_VKBD, 0, "RETROKE_VKBD"},
	{RETROKE_LEFT, 0, "RETROKE_LEFT"},
	{RETROKE_UP, 0, "RETROKE_UP"},
	{RETROKE_DOWN, 0, "RETROKE_DOWN"},
	{RETROKE_RIGHT, 0, "RETROKE_RIGHT"},
	{RETROKE_LEFT_BUTTON, 0, "RETROKE_LEFT_BUTTON"},
	{RETROKE_RIGHT_BUTTON, 0, "RETROKE_RIGHT_BUTTON"},
	{RETROKE_FINE_CONTROL, 0, "RETROKE_FINE_CONTROL"},
	{RETROKE_SCUMMVM_GUI, 0, "RETROKE_SCUMMVM_GUI"},
	{RETROKE_SHIFT_MOD, 0, "RETROKE_SHIFT_MOD"},
	{RETROKE_CTRL_MOD, 0, "RETROKE_CTRL_MOD"},
	{RETROKE_ALT_MOD, 0, "RETROKE_ALT_MOD"},
	{RETROK_BACKSPACE, Common::KEYCODE_BACKSPACE, "RETROK_BACKSPACE"},
	{RETROK_TAB, Common::KEYCODE_TAB, "RETROK_TAB"},
	{RETROK_CLEAR, Common::KEYCODE_CLEAR, "RETROK_CLEAR"},
	{RETROK_RETURN, Common::KEYCODE_RETURN, "RETROK_RETURN"},
	{RETROK_PAUSE, Common::KEYCODE_PAUSE, "RETROK_PAUSE"},
	{RETROK_ESCAPE, Common::KEYCODE_ESCAPE, "RETROK_ESCAPE"},
	{RETROK_SPACE, Common::KEYCODE_SPACE, "RETROK_SPACE"},
	{RETROK_EXCLAIM, Common::KEYCODE_EXCLAIM, "RETROK_EXCLAIM"},
	{RETROK_QUOTEDBL, Common::KEYCODE_QUOTEDBL, "RETROK_QUOTEDBL"},
	{RETROK_HASH, Common::KEYCODE_HASH, "RETROK_HASH"},
	{RETROK_DOLLAR, Common::KEYCODE_DOLLAR, "RETROK_DOLLAR"},
	{RETROK_AMPERSAND, Common::KEYCODE_AMPERSAND, "RETROK_AMPERSAND"},
	{RETROK_QUOTE, Common::KEYCODE_QUOTE, "RETROK_QUOTE"},
	{RETROK_LEFTPAREN, Common::KEYCODE_LEFTPAREN, "RETROK_LEFTPAREN"},
	{RETROK_RIGHTPAREN, Common::KEYCODE_RIGHTPAREN, "RETROK_RIGHTPAREN"},
	{RETROK_ASTERISK, Common::KEYCODE_ASTERISK, "RETROK_ASTERISK"},
	{RETROK_PLUS, Common::KEYCODE_PLUS, "RETROK_PLUS"},
	{RETROK_COMMA, Common::KEYCODE_COMMA, "RETROK_COMMA"},
	{RETROK_MINUS, Common::KEYCODE_MINUS, "RETROK_MINUS"},
	{RETROK_PERIOD, Common::KEYCODE_PERIOD, "RETROK_PERIOD"},
	{RETROK_SLASH, Common::KEYCODE_SLASH, "RETROK_SLASH"},
	{RETROK_0, Common::KEYCODE_0, "RETROK_0"},
	{RETROK_1, Common::KEYCODE_1, "RETROK_1"},
	{RETROK_2, Common::KEYCODE_2, "RETROK_2"},
	{RETROK_3, Common::KEYCODE_3, "RETROK_3"},
	{RETROK_4, Common::KEYCODE_4, "RETROK_4"},
	{RETROK_5, Common::KEYCODE_5, "RETROK_5"},
	{RETROK_6, Common::KEYCODE_6, "RETROK_6"},
	{RETROK_7, Common::KEYCODE_7, "RETROK_7"},
	{RETROK_8, Common::KEYCODE_8, "RETROK_8"},
	{RETROK_9, Common::KEYCODE_9, "RETROK_9"},
	{RETROK_COLON, Common::KEYCODE_COLON, "RETROK_COLON"},
	{RETROK_SEMICOLON, Common::KEYCODE_SEMICOLON, "RETROK_SEMICOLON"},
	{RETROK_LESS, Common::KEYCODE_LESS, "RETROK_LESS"},
	{RETROK_EQUALS, Common::KEYCODE_EQUALS, "RETROK_EQUALS"},
	{RETROK_GREATER, Common::KEYCODE_GREATER, "RETROK_GREATER"},
	{RETROK_QUESTION, Common::KEYCODE_QUESTION, "RETROK_QUESTION"},
	{RETROK_AT, Common::KEYCODE_AT, "RETROK_AT"},
	{RETROK_LEFTBRACKET, Common::KEYCODE_LEFTBRACKET, "RETROK_LEFTBRACKET"},
	{RETROK_BACKSLASH, Common::KEYCODE_BACKSLASH, "RETROK_BACKSLASH"},
	{RETROK_RIGHTBRACKET, Common::KEYCODE_RIGHTBRACKET, "RETROK_RIGHTBRACKET"},
	{RETROK_CARET, Common::KEYCODE_CARET, "RETROK_CARET"},
	{RETROK_UNDERSCORE, Common::KEYCODE_UNDERSCORE, "RETROK_UNDERSCORE"},
	{RETROK_BACKQUOTE, Common::KEYCODE_BACKQUOTE, "RETROK_BACKQUOTE"},
	{RETROK_a, Common::KEYCODE_a, "RETROK_a"},
	{RETROK_b, Common::KEYCODE_b, "RETROK_b"},
	{RETROK_c, Common::KEYCODE_c, "RETROK_c"},
	{RETROK_d, Common::KEYCODE_d, "RETROK_d"},
	{RETROK_e, Common::KEYCODE_e, "RETROK_e"},
	{RETROK_f, Common::KEYCODE_f, "RETROK_f"},
	{RETROK_g, Common::KEYCODE_g, "RETROK_g"},
	{RETROK_h, Common::KEYCODE_h, "RETROK_h"},
	{RETROK_i, Common::KEYCODE_i, "RETROK_i"},
	{RETROK_j, Common::KEYCODE_j, "RETROK_j"},
	{RETROK_k, Common::KEYCODE_k, "RETROK_k"},
	{RETROK_l, Common::KEYCODE_l, "RETROK_l"},
	{RETROK_m, Common::KEYCODE_m, "RETROK_m"},
	{RETROK_n, Common::KEYCODE_n, "RETROK_n"},
	{RETROK_o, Common::KEYCODE_o, "RETROK_o"},
	{RETROK_p, Common::KEYCODE_p, "RETROK_p"},
	{RETROK_q, Common::KEYCODE_q, "RETROK_q"},
	{RETROK_r, Common::KEYCODE_r, "RETROK_r"},
	{RETROK_s, Common::KEYCODE_s, "RETROK_s"},
	{RETROK_t, Common::KEYCODE_t, "RETROK_t"},
	{RETROK_u, Common::KEYCODE_u, "RETROK_u"},
	{RETROK_v, Common::KEYCODE_v, "RETROK_v"},
	{RETROK_w, Common::KEYCODE_w, "RETROK_w"},
	{RETROK_x, Common::KEYCODE_x, "RETROK_x"},
	{RETROK_y, Common::KEYCODE_y, "RETROK_y"},
	{RETROK_z, Common::KEYCODE_z, "RETROK_z"},
	{RETROK_KP0, Common::KEYCODE_KP0, "RETROK_KP0"},
	{RETROK_KP1, Common::KEYCODE_KP1, "RETROK_KP1"},
	{RETROK_KP2, Common::KEYCODE_KP2, "RETROK_KP2"},
	{RETROK_KP3, Common::KEYCODE_KP3, "RETROK_KP3"},
	{RETROK_KP4, Common::KEYCODE_KP4, "RETROK_KP4"},
	{RETROK_KP5, Common::KEYCODE_KP5, "RETROK_KP5"},
	{RETROK_KP6, Common::KEYCODE_KP6, "RETROK_KP6"},
	{RETROK_KP7, Common::KEYCODE_KP7, "RETROK_KP7"},
	{RETROK_KP8, Common::KEYCODE_KP8, "RETROK_KP8"},
	{RETROK_KP9, Common::KEYCODE_KP9, "RETROK_KP9"},
	{RETROK_KP_PERIOD, Common::KEYCODE_KP_PERIOD, "RETROK_KP_PERIOD"},
	{RETROK_KP_DIVIDE, Common::KEYCODE_KP_DIVIDE, "RETROK_KP_DIVIDE"},
	{RETROK_KP_MULTIPLY, Common::KEYCODE_KP_MULTIPLY, "RETROK_KP_MULTIPLY"},
	{RETROK_KP_MINUS, Common::KEYCODE_KP_MINUS, "RETROK_KP_MINUS"},
	{RETROK_KP_PLUS, Common::KEYCODE_KP_PLUS, "RETROK_KP_PLUS"},
	{RETROK_KP_ENTER, Common::KEYCODE_KP_ENTER, "RETROK_KP_ENTER"},
	{RETROK_KP_EQUALS, Common::KEYCODE_KP_EQUALS, "RETROK_KP_EQUALS"},
	{RETROK_UP, Common::KEYCODE_UP, "RETROK_UP"},
	{RETROK_DOWN, Common::KEYCODE_DOWN, "RETROK_DOWN"},
	{RETROK_LEFT, Common::KEYCODE_LEFT, "RETROK_LEFT"},
	{RETROK_RIGHT, Common::KEYCODE_RIGHT, "RETROK_RIGHT"},
	{RETROK_INSERT, Common::KEYCODE_INSERT, "RETROK_INSERT"},
	{RETROK_DELETE, Common::KEYCODE_DELETE, "RETROK_DELETE"},
	{RETROK_HOME, Common::KEYCODE_HOME, "RETROK_HOME"},
	{RETROK_END, Common::KEYCODE_END, "RETROK_END"},
	{RETROK_PAGEUP, Common::KEYCODE_PAGEUP, "RETROK_PAGEUP"},
	{RETROK_PAGEDOWN, Common::KEYCODE_PAGEDOWN, "RETROK_PAGEDOWN"},
	{RETROK_F1, Common::KEYCODE_F1, "RETROK_F1"},
	{RETROK_F2, Common::KEYCODE_F2, "RETROK_F2"},
	{RETROK_F3, Common::KEYCODE_F3, "RETROK_F3"},
	{RETROK_F4, Common::KEYCODE_F4, "RETROK_F4"},
	{RETROK_F5, Common::KEYCODE_F5, "RETROK_F5"},
	{RETROK_F6, Common::KEYCODE_F6, "RETROK_F6"},
	{RETROK_F7, Common::KEYCODE_F7, "RETROK_F7"},
	{RETROK_F8, Common::KEYCODE_F8, "RETROK_F8"},
	{RETROK_F9, Common::KEYCODE_F9, "RETROK_F9"},
	{RETROK_F10, Common::KEYCODE_F10, "RETROK_F10"},
	{RETROK_F11, Common::KEYCODE_F11, "RETROK_F11"},
	{RETROK_F12, Common::KEYCODE_F12, "RETROK_F12"},
	{RETROK_F13, Common::KEYCODE_F13, "RETROK_F13"},
	{RETROK_F14, Common::KEYCODE_F14, "RETROK_F14"},
	{RETROK_F15, Common::KEYCODE_F15, "RETROK_F15"},
	{RETROK_NUMLOCK, Common::KEYCODE_NUMLOCK, "RETROK_NUMLOCK"},
	{RETROK_CAPSLOCK, Common::KEYCODE_CAPSLOCK, "RETROK_CAPSLOCK"},
	{RETROK_SCROLLOCK, Common::KEYCODE_SCROLLOCK, "RETROK_SCROLLOCK"},
	{RETROK_LSHIFT, Common::KEYCODE_LSHIFT, "RETROK_LSHIFT"},
	{RETROK_RSHIFT, Common::KEYCODE_RSHIFT, "RETROK_RSHIFT"},
	{RETROK_LCTRL, Common::KEYCODE_LCTRL, "RETROK_LCTRL"},
	{RETROK_RCTRL, Common::KEYCODE_RCTRL, "RETROK_RCTRL"},
	{RETROK_LALT, Common::KEYCODE_LALT, "RETROK_LALT"},
	{RETROK_RALT, Common::KEYCODE_RALT, "RETROK_RALT"},
	{RETROK_LMETA, Common::KEYCODE_LMETA, "RETROK_LMETA"},
	{RETROK_RMETA, Common::KEYCODE_RMETA, "RETROK_RMETA"},
	{RETROK_LSUPER, Common::KEYCODE_LSUPER, "RETROK_LSUPER"},
	{RETROK_RSUPER, Common::KEYCODE_RSUPER, "RETROK_RSUPER"},
	{RETROK_MODE, Common::KEYCODE_MODE, "RETROK_MODE"},
	{RETROK_COMPOSE, Common::KEYCODE_COMPOSE, "RETROK_COMPOSE"},
	{RETROK_HELP, Common::KEYCODE_HELP, "RETROK_HELP"},
	{RETROK_PRINT, Common::KEYCODE_PRINT, "RETROK_PRINT"},
	{RETROK_SYSREQ, Common::KEYCODE_SYSREQ, "RETROK_SYSREQ"},
	{RETROK_BREAK, Common::KEYCODE_BREAK, "RETROK_BREAK"},
	{RETROK_MENU, Common::KEYCODE_MENU, "RETROK_MENU"},
	{RETROK_POWER, Common::KEYCODE_POWER, "RETROK_POWER"},
	{RETROK_EURO, Common::KEYCODE_EURO, "RETROK_EURO"},
	{RETROK_UNDO, Common::KEYCODE_UNDO, "RETROK_UNDO"},
	{RETROK_LAST, 0, ""}
};

const struct retro_controller_description retro_controller_list[] = {
	{"None", RETRO_DEVICE_NONE},
	{"Automatic", RETRO_DEVICE_JOYPAD},
	{NULL, 0}
};

const struct retro_controller_info retro_controller_lists[] = {
	{retro_controller_list, sizeof(retro_controller_list) / sizeof(retro_controller_list[0])},
	{NULL, 0}
};

static struct retro_input_descriptor retro_input_desc[] = {
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP, "Up"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN, "Down"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT, "Left"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT, "Right"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B, "B / Fire / Red"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A, "A / 2nd fire / Blue"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y, "Y / Green"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X, "X / Yellow"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "Select"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START, "Start / Play"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L, "L / Rewind"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R, "R / Forward"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L2, "L2"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R2, "R2"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L3, "L3"},
	{0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R3, "R3"},
	{0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_X, "Left Analog X"},
	{0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_LEFT, RETRO_DEVICE_ID_ANALOG_Y, "Left Analog Y"},
	{0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_X, "Right Analog X"},
	{0, RETRO_DEVICE_ANALOG, RETRO_DEVICE_INDEX_ANALOG_RIGHT, RETRO_DEVICE_ID_ANALOG_Y, "Right Analog Y"},
	{0}
};

void mapper_poll_device(void);
bool mapper_set_device_keys(unsigned int retro_device_id, const char *retro_key_value);
uint8 mapper_get_device_key_status(unsigned int retro_device_id);
int16 mapper_get_device_key_value(unsigned int retro_device_id);
int16 mapper_get_device_key_retro_id(unsigned int retro_device_id);
int16 mapper_get_device_key_scummvm_id(unsigned int retro_device_id);
int8 mapper_get_mapper_key_index(int16 key_retro_id, uint8 start_index = 0);
uint8 mapper_get_mapper_key_status(int16 key_retro_id);
int16 mapper_get_mapper_key_value(int16 key_retro_id);

#endif // LIBRETRO_MAPPER_H
