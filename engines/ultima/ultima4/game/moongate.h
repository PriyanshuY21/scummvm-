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

#ifndef ULTIMA4_GAME_MOONGATE_H
#define ULTIMA4_GAME_MOONGATE_H

#include "ultima/ultima4/core/coords.h"
#include "common/hashmap.h"

namespace Ultima {
namespace Ultima4 {

class Moongates : public Common::HashMap<int, Coords> {
public:
	/**
	 * Constructor
	 */
	Moongates();

	/**
	 * Destructor
	 */
	~Moongates();

	void add(int phase, const Coords &coords);
	const Coords *getGateCoordsForPhase(int phase);
	bool findActiveGateAt(int trammel, int felucca, const Coords &src, Coords &dest);
	bool isEntryToShrineOfSpirituality(int trammel, int felucca);
};

extern Moongates *g_moongates;

} // End of namespace Ultima4
} // End of namespace Ultima

#endif
