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

/*
 * This code is based on Broken Sword 2.5 engine
 *
 * Copyright (c) Malte Thiesen, Daniel Queteschiner and Michael Elsdoerfer
 *
 * Licensed under GNU GPL v2
 *
 */

#ifndef SWORD25_PERSISTENCESERVICE_H
#define SWORD25_PERSISTENCESERVICE_H

#include "sword25/kernel/common.h"

namespace Sword25 {

class PersistenceService {
public:
	PersistenceService();
	virtual ~PersistenceService();

	// -----------------------------------------------------------------------------
	// Singleton Method
	// -----------------------------------------------------------------------------

	static PersistenceService &getInstance();

	// -----------------------------------------------------------------------------
	// Interface
	// -----------------------------------------------------------------------------

	static uint getSlotCount();
	static Common::Path getSavegameDirectory();

	void            reloadSlots();
	bool            isSlotOccupied(uint slotID);
	bool            isSavegameCompatible(uint slotID);
	int             getSavegameVersion(uint slotID);
	Common::String &getSavegameDescription(uint slotID);
	Common::String &getSavegameFilename(uint slotID);

	bool            saveGame(uint slotID, const Common::String &screenshotFilename);
	bool            loadGame(uint slotID);

private:
	struct Impl;
	Impl *_impl;
};

void setGameTarget(const char *target);

} // End of namespace Sword25

#endif
