/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
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

#ifndef PEGASUS_INTERACTION_H
#define PEGASUS_INTERACTION_H

#include "pegasus/input.h"
#include "pegasus/util.h"

namespace Pegasus {

static const InteractionID kNoInteractionID = -1;

class Neighborhood;

class GameInteraction : public IDObject, public InputHandler {
public:
	GameInteraction(const InteractionID id, Neighborhood *nextHandler);

	// If the interaction is open (_isInteracting == true), it's too late to do anything
	// about it here.
	~GameInteraction() override {}

	// startInteraction and stopInteraction are called by the outside world to
	// start and stop the interaction sequence.
	// isInteracting returns a bool indicating whether or not the interaction
	// is going.
	void startInteraction() {
		if (!isInteracting()) {
			openInteraction();
			initInteraction();
			_isInteracting = true;
			_savedHandler = InputHandler::setInputHandler(this);
		}
	}
	void stopInteraction() {
		if (isInteracting()) {
			closeInteraction();
			_isInteracting = false;
			if (InputHandler::_inputHandler == this)
				InputHandler::setInputHandler(_savedHandler);
		}
	}
	void startOverInteraction() {
		if (isInteracting())
			resetInteraction();
	}
	bool isInteracting() const { return _isInteracting; }
	Neighborhood *getOwner() const { return _owner; }

	virtual Common::Path getBriefingMovie() { return Common::Path(); }
	virtual Common::Path getEnvScanMovie() { return Common::Path(); }
	virtual long getNumHints() { return 0; }
	virtual Common::Path getHintMovie(uint) { return Common::Path(); }
	virtual bool canSolve() { return false; }

	virtual void setSoundFXLevel(const uint16) {}
	virtual void setAmbienceLevel(const uint16) {}

	virtual void doSolve() {}

protected:
	// Subclasses override openInteraction and closeInteraction to perform
	// specific initialization and cleanup. Override resetInteraction to
	// "start the interaction over." resetInteraction is called only when
	// the interaction is already open.
	// These functions are only called in pairs, never two opens or closes
	// in a row.
	virtual void openInteraction() {}
	virtual void initInteraction() {}
	virtual void closeInteraction() {}
	virtual void resetInteraction() {}

	InputHandler *_savedHandler;
	Neighborhood *_owner;

private:
	// Private so that only StartInteraction and StopInteraction can touch it.
	bool _isInteracting;
};

} // End of namespace Pegasus

#endif
