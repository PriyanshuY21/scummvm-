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

#ifndef ULTIMA4_CONTROLLERS_ZTATS_CONTROLLER_H
#define ULTIMA4_CONTROLLERS_ZTATS_CONTROLLER_H

#include "ultima/ultima4/controllers/controller.h"

namespace Ultima {
namespace Ultima4 {

/**
 * Controls interaction while Ztats are being displayed.
 */
class ZtatsController : public WaitableController<void *> {
public:
	ZtatsController() : WaitableController<void *>(nullptr) {}

	bool keyPressed(int key) override;
	void keybinder(KeybindingAction action) override;
};

} // End of namespace Ultima4
} // End of namespace Ultima

#endif
