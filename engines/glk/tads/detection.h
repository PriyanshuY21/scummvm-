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

#ifndef GLK_TADS_DETECTION
#define GLK_TADS_DETECTION

#include "common/fs.h"
#include "engines/game.h"
#include "glk/detection.h"

namespace Glk {
namespace TADS {

enum TADSOption { OPTION_TADS2 = 0, OPTION_TADS3 = 1 };

/**
 * Meta engine for TADS interpreter
 */
class TADSMetaEngine {
public:
	/**
	 * Get a list of supported games
	 */
	static void getSupportedGames(PlainGameList &games);

	/**
	 * Returns a game description for the given game Id, if it's supported
	 */
	static GameDescriptor findGame(const char *gameId);

	/**
	 * Detect supported games
	 */
	static bool detectGames(const Common::FSList &fslist, DetectedGames &gameList);

	/**
	 * Check for game Id clashes with other sub-engines
	 */
	static void detectClashes(Common::StringMap &map);

	/**
	 * Determines whether the given game is TADS 2 or 3
	 * @param game		Open stream pointing to game file
	 * @returns			2 for TADS 2, 3 for TADS 3, or -1 for error
	 */
	static int getTADSVersion(Common::SeekableReadStream &game);
};

} // End of namespace TADS
} // End of namespace Glk

#endif
