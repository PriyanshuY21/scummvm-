/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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

#ifndef NUVIE_CORE_NUVIE_DEFS_H
#define NUVIE_CORE_NUVIE_DEFS_H

#include "common/scummsys.h"
#include "ultima/nuvie/misc/sdl_compat.h"

namespace Ultima {
namespace Nuvie {

typedef int8 sint8;
typedef int16 sint16;
typedef int32 sint32;

#define USE_BUTTON Shared::BUTTON_LEFT
#define WALK_BUTTON Shared::BUTTON_RIGHT
#define ACTION_BUTTON Shared::BUTTON_RIGHT
#define DRAG_BUTTON Shared::BUTTON_LEFT

typedef uint8 nuvie_game_t; // Game type (1=u6,2=md,4=se)

#define NUVIE_GAME_NONE  0
#define NUVIE_GAME_U6    1
#define NUVIE_GAME_MD    2
#define NUVIE_GAME_SE    4

#define NUVIE_CONFIG_NAME_U6 "ultima6"
#define NUVIE_CONFIG_NAME_MD "martian"
#define NUVIE_CONFIG_NAME_SE "savage"

#define NUVIE_STYLE_ORIG 0
#define NUVIE_STYLE_NEW  1
#define NUVIE_STYLE_ORIG_PLUS_CUTOFF_MAP 2
#define NUVIE_STYLE_ORIG_PLUS_FULL_MAP   3

#define clamp_min(v, c)  (((v) < (c)) ? (c) : (v))
#define clamp_max(v, c)  (((v) > (c)) ? (c) : (v))
#define clamp(v, c1, c2) ( ((v) < (c1)) ? (c1) : (((v) > (c2)) ? (c2) : (v)) )

#ifndef INT_MAX
#define INT_MAX 0x7fffffff
#endif
#ifndef UCHAR_MAX
#define UCHAR_MAX 0xff
#endif
#ifndef SHRT_MAX
#define SHRT_MAX 0x7fff
#endif

//FIXME fix for future maps which will probably be 1024 wide starting at level 6..
#define WRAPPED_COORD(c,level) ((c)&((level)?255:1023))
#define WRAP_COORD(c,level) ((c)&=((level)?255:1023))

#define MAP_SIDE_LENGTH(map_level) ((map_level > 0 && map_level < 6) ? 256 : 1024)

/*
 * on all levels, except level 0 (conveniently 'false') the map pitch is 256.
 * to properly wrap, mask the coordinate with the relevant bit-mask.
 * Another way to write this would be:

const uint16 map_pitch[2] = { 1024, 256 }; // width of 0:surface plane, and 1:all other planes
#define WRAPPED_COORD(c,level) ((c)&(map_pitch[(level==0)?0:1]-1)) // mask high bit, wrap C to map_pitch
#define WRAP_COORD(c,level) ((c)&=(map_pitch[(level==0)?0:1]-1)) // modifies C
*/

enum NuvieDir {
	NUVIE_DIR_N = 0,
	NUVIE_DIR_E = 1,
	NUVIE_DIR_S = 2,
	NUVIE_DIR_W = 3,

	NUVIE_DIR_NE = 4,
	NUVIE_DIR_SE = 5,
	NUVIE_DIR_SW = 6,
	NUVIE_DIR_NW = 7,

	NUVIE_DIR_NONE = 8,
};

#define TRAMMEL_PHASE 1.75
#define FELUCCA_PHASE 1.1666666666666667

enum DebugLevelType {
	LEVEL_EMERGENCY = 0,
	LEVEL_ALERT,
	LEVEL_CRITICAL,
	LEVEL_ERROR,
	LEVEL_WARNING,
	LEVEL_NOTIFICATION,
	LEVEL_INFORMATIONAL,
	LEVEL_DEBUGGING
};

enum ConverseGumpType {
	CONVERSE_GUMP_DEFAULT = 0,
	CONVERSE_GUMP_U7_STYLE = 1,
	CONVERSE_GUMP_WOU_STYLE = 2,
};

#ifdef WITHOUT_DEBUG
inline void u6debug(bool no_header, const DebugLevelType level, const char *format, ...) {}
#else
extern void u6debug(bool no_header, const DebugLevelType level, const char *format, ...);
#endif

#ifdef DEBUG
#undef DEBUG
#endif
#define DEBUG u6debug

#define U6PATH_DELIMITER '/'

#define NUVIE_RAND_MAX 0x7fffffff // POSIX: 2^(31)-1
#define NUVIE_RAND() getRandom(NUVIE_RAND_MAX)

} // End of namespace Nuvie
} // End of namespace Ultima

#endif
