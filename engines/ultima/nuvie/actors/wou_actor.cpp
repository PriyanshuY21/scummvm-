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

#include "ultima/nuvie/actors/wou_actor.h"

namespace Ultima {
namespace Nuvie {

bool WOUActor::can_carry_object(Obj *obj) const {
	if (inventory_count_objects(INV_EXCLUDE_READIED_OBJECTS) >= 16) {
		return false;
	}

	return Actor::can_carry_object(obj);
}

bool WOUActor::can_carry_object(uint16 objN, uint32 qty) const {
	if (inventory_count_objects(INV_EXCLUDE_READIED_OBJECTS) >= 16) {
		return false;
	}

	return Actor::can_carry_object(objN, qty);
}

} // End of namespace Nuvie
} // End of namespace Ultima
