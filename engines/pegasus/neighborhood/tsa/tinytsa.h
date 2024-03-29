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

#ifndef PEGASUS_NEIGHBORHOOD_TSA_TINYTSA_H
#define PEGASUS_NEIGHBORHOOD_TSA_TINYTSA_H

#include "pegasus/neighborhood/neighborhood.h"

namespace Pegasus {

//	Room IDs.

static const RoomID kTinyTSA37 = 0;

class TinyTSA : public Neighborhood {
public:
	TinyTSA(InputHandler *, PegasusEngine *);
	~TinyTSA() override {}

	uint16 getDateResID() const override;

	void start() override;

	void checkContinuePoint(const RoomID, const DirectionConstant) override;

protected:
	Common::Path getBriefingMovie() override;
	Common::Path getEnvScanMovie() override;
	void loadAmbientLoops() override;
	void clickInHotspot(const Input &, const Hotspot *) override;

	int16 getStaticCompassAngle(const RoomID, const DirectionConstant) override;

	void arriveFromNorad();
	void arriveFromMars();
	void arriveFromWSC();

	InputBits getInputFilter() override;
	void arriveAt(const RoomID, const DirectionConstant) override;
	void showMainJumpMenu();
	void receiveNotification(Notification *, const NotificationFlags) override;

	Common::Path getNavMovieName() override;
	Common::Path getSoundSpotsName() override { return Common::Path(); }
};

} // End of namespace Pegasus

#endif
