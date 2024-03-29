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

#ifndef PEGASUS_NEIGHBORHOOD_PREHISTORIC_H
#define PEGASUS_NEIGHBORHOOD_PREHISTORIC_H

#include "pegasus/neighborhood/neighborhood.h"

namespace Pegasus {

static const TimeScale kPrehistoricMovieScale = 600;
static const TimeScale kPrehistoricFramesPerSecond = 15;
static const TimeScale kPrehistoricFrameDuration = 40;

//	Alternate IDs.

static const AlternateID kAltPrehistoricNormal = 0;
static const AlternateID kAltPrehistoricBridgeSet = 1;

//	Room IDs.

static const RoomID kPrehistoric01 = 0;
static const RoomID kPrehistoric02 = 1;
static const RoomID kPrehistoric03 = 2;
static const RoomID kPrehistoric04 = 3;
static const RoomID kPrehistoric05 = 4;
static const RoomID kPrehistoric06 = 5;
static const RoomID kPrehistoric07 = 6;
static const RoomID kPrehistoric08 = 7;
static const RoomID kPrehistoric09 = 8;
static const RoomID kPrehistoric10 = 9;
static const RoomID kPrehistoric11 = 10;
static const RoomID kPrehistoric12 = 11;
static const RoomID kPrehistoric13 = 12;
static const RoomID kPrehistoric14 = 13;
static const RoomID kPrehistoric15 = 14;
static const RoomID kPrehistoric16 = 15;
static const RoomID kPrehistoric17 = 16;
static const RoomID kPrehistoric18 = 17;
static const RoomID kPrehistoric19 = 18;
static const RoomID kPrehistoric20 = 19;
static const RoomID kPrehistoric21 = 20;
static const RoomID kPrehistoric22 = 21;
static const RoomID kPrehistoric22North = 22;
static const RoomID kPrehistoric23 = 23;
static const RoomID kPrehistoric24 = 24;
static const RoomID kPrehistoric25 = 25;
static const RoomID kPrehistoricDeath = 26;

//	Hot Spot Activation IDs.

static const HotSpotActivationID kActivationVaultClosed = 1;
static const HotSpotActivationID kActivationVaultOpen = 2;

//	Hot Spot IDs.

static const HotSpotID kPre18EastSpotID = 5000;
static const HotSpotID kPre22NorthSpotID = 5001;
static const HotSpotID kPre22NorthOutSpotID = 5002;
static const HotSpotID kPre22NorthBreakerSpotID = 5003;
static const HotSpotID kPrehistoricKeyDropSpotID = 5004;
static const HotSpotID kPrehistoricHistoricalLogSpotID = 5005;

//	Extra sequence IDs.

static const ExtraID kPreArrivalFromTSA = 0;
static const ExtraID kPre18EastBridgeOut = 1;
static const ExtraID kPre18EastBridgeOn = 2;
static const ExtraID kPre18EastZoom = 3;
static const ExtraID kPre18EastZoomOut = 4;
static const ExtraID kPre22ThrowBreaker = 5;
static const ExtraID kPre25EastUnlockingVaultWithLog = 6;
static const ExtraID kPre25EastVaultOpenWithLog = 7;
static const ExtraID kPre25EastViewWithLog = 8;
static const ExtraID kPre25EastUnlockingVaultNoLog = 9;
static const ExtraID kPre25EastVaultOpenNoLog = 10;
static const ExtraID kPre25EastViewNoLog = 11;

class PegasusEngine;

class Prehistoric : public Neighborhood {
public:
	Prehistoric(InputHandler *, PegasusEngine *);
	~Prehistoric() override {}

	uint16 getDateResID() const override;
	void init() override;

	void arriveAt(const RoomID, const DirectionConstant) override;
	void activateHotspots() override;
	void clickInHotspot(const Input &, const Hotspot *) override;
	Common::Path getBriefingMovie() override;
	Common::Path getEnvScanMovie() override;
	uint getNumHints() override;
	Common::Path getHintMovie(uint) override;

	Hotspot *getItemScreenSpot(Item *, DisplayElement *) override;
	void dropItemIntoRoom(Item *, Hotspot *) override;
	void pickedUpItem(Item *) override;

	void start() override;

	void bumpIntoWall() override;

	void checkContinuePoint(const RoomID, const DirectionConstant) override;

	bool canSolve() override;
	void doSolve() override;

protected:
	enum {
		kPrehistoricPrivateVaultOpenFlag,
		kPrehistoricPrivateExtendedBridgeFlag,
		kNumPrehistoricPrivateFlags
	};

	void setUpAIRules() override;
	int16 getStaticCompassAngle(const RoomID, const DirectionConstant) override;
	void getExitCompassMove(const ExitTable::Entry &, FaderMoveSpec &) override;
	void receiveNotification(Notification *, const NotificationFlags) override;
	void spotCompleted() override;
	void turnTo(const DirectionConstant) override;
	void zoomToVault();
	TimeValue getViewTime(const RoomID, const DirectionConstant) override;
	void findSpotEntry(const RoomID, const DirectionConstant, SpotFlags, SpotTable::Entry &) override;

	void loadAmbientLoops() override;

	FlagsArray<byte, kNumPrehistoricPrivateFlags> _privateFlags;

	Common::Path getNavMovieName() override;
	Common::Path getSoundSpotsName() override;
};

} // End of namespace Pegasus

#endif
