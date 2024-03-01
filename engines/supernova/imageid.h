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

#ifndef SUPERNOVA_IMAGEID_H
#define SUPERNOVA_IMAGEID_H

namespace Supernova {

enum ImageId {
	// file 0
	kImageAxacussanShipBackground,
	kImageAxacussanShipCenterMouthOpen,
	kImageAxacussanShipRightMouthOpen,
	// file 1
	kImageNewspaper1,
	// file 2
	kImageNewspaper2,
	// file 3
	kImageElevatorBackground,
	kImageElevatorGreenButton,
	kImageElevatorRedButton,
	kImageElevatorDoorAnimation1,
	kImageElevatorDoorAnimation2,
	kImageElevatorDoorAnimation3,
	kImageElevatorDoorAnimation4,
	kImageElevatorDoorAnimation5,
	kImageElevatorDummy1,
	kImageElevatorDummy2,
	kImageElevatorDummy3,
	kImageElevatorDummy4,
	// file 4
	kImageShipSpaceBackground,
	kImageShipSpaceRope,
	kImageShipSpaceDummy1,
	kImageShipSpaceDummy2,
	// file 5
	kImageBusStationBackground,
	kImageBusStationArrived,
	kImageBusStationPlantAnimation1,
	kImageBusStationPlantAnimation2,
	kImageBusStationPlantAnimation3,
	kImageBusStationPlantAnimation4,
	kImageBusStationPlantAnimation5,
	kImageBusStationPlantAnimation6,
	kImageBusStationPlantAnimation7,
	kImageBusStationDoorOpened,
	// file 6
	kImageOfficesBackground,
	kImageOfficesDoorOpenTopLeft,
	kImageOfficesDoorOpenBottomLeft,
	kImageOfficesDoorOpenTopRight,
	kImageOfficesDoorOpenBottomRight,
	kImageOfficesAlienCorridorAnimation1,
	kImageOfficesAlienCorridorAnimation2,
	kImageOfficesAlienCorridorAnimation3,
	kImageOfficesAlienCorridorAnimation4,
	kImageOfficesAlienCorridorAnimation5,
	kImageOfficesAlienCorridorAnimation6,
	kImageOfficesAlienTopOfficeAnimation1,
	kImageOfficesAlienTopOfficeAnimation2,
	kImageOfficesAlienTopOfficeAnimation3,
	kImageOfficesAlienTopOfficeAnimation4,
	kImageOfficesAlienTopOfficeAnimation5,
	kImageOfficesAlienBottomOfficeAnimation1,
	kImageOfficesAlienBottomOfficeAnimation2,
	kImageOfficesAlienBottomOfficeAnimation3,
	kImageOfficesAlienBottomOfficeAnimation4,
	kImageOfficesAlienBottomOfficeAnimation5,
	kImageOfficesAlienBottom,
	// file 7
	kImageOfficeLeftBackground,
	kImageOfficeLeftDecoration,
	kImageOfficeLeftMemo,
	kImageOfficeLeftGraffiti,
	kImageOfficeLeftTerminalSmashed,
	kImageOfficeLeftDrawerMoney,
	kImageOfficeLeftSafeOpen,
	kImageOfficeLeftSafeClosed,
	kImageOfficeLeftSafeMoney,
	kImageOfficeLeftDoorOpen,
	kImageOfficeLeftAlienShootAnimation1,
	kImageOfficeLeftAlienShootAnimation2,
	kImageOfficeLeftAlienShootAnimation3,
	kImageOfficeLeftAlienShootAnimation4,
	kImageOfficeLeftAlienShootAnimation5,
	kImageOfficeLeftAlienShootAnimation6,
	kImageOfficeLeftTerminalText,
	kImageOfficeLeftDoorClosed,
	kImageOfficeLeftDummy1,
	kImageOfficeLeftDummy2,
	kImageOfficeLeftDummy3,
	kImageOfficeLeftDummy4,
	kImageOfficeLeftDummy5,
	// file 8
	kImageOfficeRightBackground,
	kImageOfficeRightDecorationPictures,
	kImageOfficeRightDecorationPlants,
	kImageOfficeRightDoorOpen,
	kImageOfficeRightTerminalSmashed,
	kImageOfficeRightAlienShootAnimation1,
	kImageOfficeRightAlienShootAnimation2,
	kImageOfficeRightAlienShootAnimation3,
	kImageOfficeRightAlienTalking,
	kImageOfficeRightDummy1,
	kImageOfficeRightDummy2,
	kImageOfficeRightDummy3,
	kImageOfficeRightDummy4,
	// file 9
	kImageShipCockpitBackground,
	kImageShipCockpitPilotAnimation1,
	kImageShipCockpitPilotAnimation2,
	kImageShipCockpitPilotAnimation3,
	kImageShipCockpitPilotAnimation4,
	kImageShipCockpitPilotAnimation5,
	kImageShipCockpitPilotAnimation6,
	kImageShipCockpitPilotAnimation7,
	kImageShipCockpitPilotAnimation8,
	kImageShipCockpitPilotAnimation9,
	kImageShipCockpitPilotAnimation10,
	kImageShipCockpitPilotAnimation11,
	kImageShipCockpitPilotAnimation12,
	kImageShipCockpitPilotAnimation13,
	kImageShipCockpitPilotAnimation14,
	kImageShipCockpitPilotAnimation15,
	kImageShipCockpitPilotAnimation16,
	kImageShipCockpitPilotAnimation17,
	kImageShipCockpitPilotAnimation18,
	kImageShipCockpitPilotAnimation19,
	kImageShipCockpitPilotAnimation20,
	kImageShipCockpitDisplayStatusAnimation1,
	kImageShipCockpitDisplayStatusAnimation2,
	kImageShipCockpitWindowRocks,
	// file 10
	kImageRestaurantEntranceBackground,
	kImageRestaurantEntrancePorterAnimation1,
	kImageRestaurantEntrancePorterAnimation2,
	kImageRestaurantEntrancePorterAnimation3,
	kImageRestaurantEntrancePorterAnimation4,
	kImageRestaurantEntranceBathroomDoorAnimation1,
	kImageRestaurantEntranceBathroomDoorAnimation2,
	kImageRestaurantEntranceBathroomDoorAnimation3,
	kImageRestaurantEntranceBathroomDoorAnimation4,
	kImageRestaurantEntranceBathroomDoorAnimation5,
	kImageRestaurantEntranceGreenCandy,
	kImageRestaurantEntranceBlueCandy,
	kImageRestaurantEntrancePinkCandy,
	kImageRestaurantEntranceWhiteCandy,
	kImageRestaurantEntranceBlackCandy,
	kImageRestaurantEntraceDummy1,
	kImageRestaurantEntraceDummy2,
	// file 11
	kImageDeathScreen,
	// file 12
	kImageRocksBackground,
	kImageRocksRockAnimation1,
	kImageRocksRockAnimation2,
	kImageRocksRockAnimation3,
	// file 13
	kImageBluePlanetBackground,
	kImageBluePlanetShipAnimation1,
	kImageBluePlanetShipAnimation2,
	kImageBluePlanetShipAnimation3,
	kImageBluePlanetShipAnimation4,
	kImageBluePlanetShipAnimation5,
	kImageBluePlanetShipAnimation6,
	kImageBluePlanetShipAnimation7,
	kImageBluePlanetShipAnimation8,
	kImageBluePlanetShipAnimation9,
	kImageBluePlanetShipAnimation10,
	kImageBluePlanetShipAnimation11,
	kImageBluePlanetShipAnimation12,
	kImageBluePlanetShipAnimation13,
	// file 14
	kImageRogerCrashBackground,
	kImageRogerCrashAnimation1,
	kImageRogerCrashAnimation2,
	kImageRogerCrashAnimation3,
	kImageRogerCrashAnimation4,
	kImageRogerCrashAnimation5,
	kImageRogerCrashAnimation6,
	kImageRogerCrashAnimation7,
	kImageRogerCrashAnimation8,
	kImageRogerCrashAnimation9,
	kImageRogerCrashAnimation10,
	kImageRogerCrashAnimation11,
	kImageRogerCrashAnimation12,
	kImageRogerCrashAnimation13,
	kImageRogerCrashAnimation14,
	kImageRogerCrashAnimation15,
	kImageRogerCrashAnimation16,
	kImageRogerCrashAnimation17,
	kImageRogerCrashAnimation18,
	kImageRogerCrashAnimation19,
	// file 15
	kImageShipCorridorBackground,
	kImageShipCorridorCockpitDoorOpen,
	kImageShipCorridorSleepCabinDoorAnimation1,
	kImageShipCorridorSleepCabinDoorAnimation2,
	kImageShipCorridorSleepCabinDoorAnimation3,
	kImageShipCorridorDummy1,
	// file 16
	kImageAxacussCorridorTileWalled,
	kImageAxacussCorridorToLeft,
	kImageAxacussCorridorToRight,
	kImageAxacussCorridorToTop,
	kImageAxacussCorridorToBottom,
	kImageAxacussCorridorTile,
	kImageAxacussCorridorDoorClosed,
	kImageAxacussCorridorDoorOpen,
	kImageAxacussCorridorDesk,
	kImageAxacussCorridorLaptop,
	kImageAxacussCorridorStuff10,
	kImageAxacussCorridorStuff11,
	kImageAxacussCorridorStuff12,
	kImageAxacussCorridorStuff13,
	kImageAxacussCorridorStuff14,
	kImageAxacussCorridorStuff15,
	kImageAxacussCorridorStuff16,
	kImageAxacussCorridorStuff17,
	kImageAxacussCorridorStuff18,
	kImageAxacussCorridorStuff19,
	kImageAxacussCorridorStuff20,
	kImageAxacussCorridorStuff21,
	kImageAxacussCorridorStuff22,
	kImageAxacussCorridorStuff23,
	kImageAxacussCorridorStuff24,
	kImageAxacussCorridorStuff25,
	kImageAxacussCorridorStuff26,
	kImageAxacussCorridorStuff27,
	kImageAxacussCorridorStuff28,
	kImageAxacussCorridorAlarmStatus,
	kImageAxacussCorridorAlienRight,
	kImageAxacussCorridorAlienLeft,
	kImageAxacussCorridorAlienBottom,
	kImageAxacussCorridorAlienTop,
	// file 17
	kImageShipCorridorCabinBackground,
	kImageShipCorridorCabinL1Open,
	kImageShipCorridorCabinL2Open,
	kImageShipCorridorCabinL3Open,
	kImageShipCorridorCabinR1Open,
	kImageShipCorridorCabinR2Open,
	kImageShipCorridorCabinR3Open,
	kImageShipCorridorCabinAirlockDoorAnimation1,
	kImageShipCorridorCabinAirlockDoorAnimation2,
	kImageShipCorridorCabinAirlockDoorAnimation3,
	kImageShipCorridorCabinDummy1,
	kImageShipCorridorCabinDummy2,
	kImageShipCorridorCabinDummy3,
	kImageShipCorridorCabinDummy4,
	kImageShipCorridorCabinDummy5,
	kImageShipCorridorCabinDummy6,
	// file 18
	kImageShipGeneratorBackground,
	kImageShipGeneratorHatchOpen,
	kImageShipGeneratorJunctionBoxOpen,
	kImageShipGeneratorJunctionBoxOffline,
	kImageShipGeneratorJunctionBoxDisplay,
	kImageShipGeneratorKeycard,
	kImageShipGeneratorSpoolFloating,
	kImageShipGeneratorSpoolOnGround,
	kImageShipGeneratorCableUnplugged,
	kImageShipGeneratorCablePluggedIn,
	kImageShipGeneratorHatchRocks,
	kImageShipGeneratorRopeRocks,
	kImageShipGeneratorRopeSpace,
	kImageShipGeneratorRopeFloor,
	kImageShipGeneratorDummy1,
	kImageShipGeneratorDummy2,
	kImageShipGeneratorDummy3,
	kImageShipGeneratorDummy4,
	kImageShipGeneratorDummy5,
	kImageShipGeneratorDummy6,
	kImageShipGeneratorDummy7,
	kImageShipGeneratorDummy8,
	// file 19
	kImageRogerShipBackground,
	kImageRogerShipButtonPressed1,
	kImageRogerShipButtonPressed2,
	kImageRogerShipButtonPressed3,
	kImageRogerShipButtonPressed4,
	kImageRogerShipCardInSlot,
	kImageRogerShipCompartmentOpen,
	kImageRogerShipUnknown7,
	kImageRogerShipDisplayLeftOn,
	kImageRogerShipGreenDisplayAnimation1,
	kImageRogerShipGreenDisplayAnimation2,
	kImageRogerShipGreenDisplayAnimation3,
	kImageRogerShipGreenDisplayAnimation4,
	kImageRogerShipGreenDisplayAnimation5,
	kImageRogerShipGreenDisplayAnimation6,
	kImageRogerShipGreenDisplayAnimation7,
	kImageRogerShipBlueDisplayAnimation1,
	kImageRogerShipBlueDisplayAnimation2,
	kImageRogerShipBlueDisplayAnimation3,
	kImageRogerShipBlueDisplayAnimation4,
	kImageRogerShipBlueDisplayAnimation5,
	kImageRogerShipBlueDisplayAnimation6,
	kImageRogerShipBlueDisplayAnimation7,
	kImageRogerShipUnknown23,
	kImageRogerShipDisplaySinewaveAnimation1,
	kImageRogerShipDisplaySinewaveAnimation2,
	kImageRogerShipDisplaySinewaveAnimation3,
	kImageRogerShipDisplaySinewaveAnimation4,
	kImageRogerShipDisplaySinewaveAnimation5,
	kImageRogerShipDisplaySinewaveAnimation6,
	kImageRogerShipDisplaySinewaveAnimation7,
	kImageRogerShipDisplaySinewaveAnimation8,
	kImageRogerShipDisplaySinewaveAnimation9,
	kImageRogerShipDisplaySinewaveAnimation10,
	kImageRogerShipDisplaySinewaveAnimation11,
	kImageRogerShipDisplaySinewaveAnimation12,
	kImageRogerShipDisplaySinewaveAnimation13,
	kImageRogerShipDisplaySinewaveAnimation14,
	kImageRogerShipCompartmentContent,
	kImageRogerShipDummy1,
	kImageRogerShipDummy2,
	// file 20
	kImageHelpScreen,
	// file 21
	kImageShipCabinLeftBackground,
	kImageShipCabinLeftPaintingSunset,
	kImageShipCabinLeftPaintingLandscape,
	kImageShipCabinLeftPaintingAbstract,
	kImageShipCabinLeftTableStuff1,
	kImageShipCabinLeftCeilingPencil,
	kImageShipCabinLeft3Decoration,
	kImageShipCabinLeftSocketPluggedIn,
	kImageShipCabinLeftVinyl,
	kImageShipCabinLeftTurntable,
	kImageShipCabinLeftSocketUnplugged,
	kImageShipCabinLeftTurntableCableCut,
	kImageShipCabinLeftTurntableCable,
	kImageShipCabinLeftTurntableAnimation1,
	kImageShipCabinLeftTurntableAnimation2,
	kImageShipCabinLeftTurntableAnimation3,
	kImageShipCabinLeftTableStuff2,
	kImageShipCabinLeftLockerOpen,
	kImageShipCabinLeftLockerBooksOpen,
	kImageShipCabinLeftLockerSpoolOpen,
	kImageShipCabinLeftLockerPistolRemoved,
	kImageShipCabinLeftLockerSpoolRemoved,
	kImageShipCabinLeftBedSafeOpen,
	kImageShipCabinLeftBedSafeEmpty,
	kImageShipCabinLeftDoorClosed,
	kImageShipCabinLeftTurntableCableSparks,
	kImageShipCabinLeftTurntableCableCutEnd,
	kImageShipCabinLeftDummy1,
	kImageShipCabinLeftDummy2,
	kImageShipCabinLeftDummy3,
	kImageShipCabinLeftDummy4,
	kImageShipCabinLeftDummy5,
	kImageShipCabinLeftDummy6,
	kImageShipCabinLeftDummy7,
	kImageShipCabinLeftDummy8,
	kImageShipCabinLeftDummy9,
	kImageShipCabinLeftDummy10,
	kImageShipCabinLeftDummy11,
	kImageShipCabinLeftDummy12,
	// file 22
	kImageShipCabinRightBackground,
	kImageShipCabinRightPosterSnowman,
	kImageShipCabinRightTableStuff,
	kImageShipCabinRightCeilingChess,
	kImageShipCabinRightTennisRacket,
	kImageShipCabinRightTennisBallsFloating,
	kImageShipCabinRightTennisBallsOnGround,
	kImageShipCabinRightTableChess,
	kImageShipCabinRight2Bed,
	kImageShipCabinRightLockerBooksOpen,
	kImageShipCabinRightLockerRopeOpen,
	kImageShipCabinRightLockerOpen,
	kImageShipCabinRightLockerRopeRemoved,
	kImageShipCabinRightBedSafeOpen,
	kImageShipCabinRightBedSafeEmpty,
	kImageShipCabinRightDoorClosed,
	kImageShipCabinRightLockerDiscmanRemoved,
	kImageShipCabinRightDummy1,
	kImageShipCabinRightDummy2,
	// file 23
	kImageShipBathroomBackground,
	// file 24
	kImageShipHoldBackgroundFloating,
	kImageShipHoldBackgroundOnGround,
	kImageShipHoldLandingModuleDoorOpen,
	kImageShipHoldGeneratorHatchOpen,
	kImageShipHoldLandingModuleSpool,
	kImageShipHoldCableToGeneratorUnplugged,
	kImageShipHoldCableToGeneratorPluggedIn,
	kImageShipHoldDummy1,
	kImageShipHoldDummy2,
	// file 25
	kImageShipLandingModuleBackground,
	kImageShipLandingModuleDoorClosed,
	kImageShipLandingModuleDisplayLeftOn,
	kImageShipLandingModuleCablePluggedIn,
	kImageShipLandingModuleCableSpoolConnected,
	kImageShipLandingModuleCableToHold,
	kImageShipLandingModuleDisplayRightOn,
	kImageShipLandingModuleDisplayTop1On,
	kImageShipLandingModuleDisplayTop2On,
	kImageShipLandingModuleDisplayTop3On,
	kImageShipLandingModuleCableWithTerminalStrip,
	kImageShipLandingModuleDummy1,
	kImageShipLandingModuleDummy2,
	kImageShipLandingModuleDummy3,
	kImageShipLandingModuleDummy4,
	kImageShipLandingModuleDummy5,
	kImageShipLandingModuleDummy6,
	kImageShipLandingModuleDummy7,
	kImageShipLandingModuleDummy8,
	// file 26
	kImageArsanoStar,
	// file 27
	kImageSaveLoadScreen,
	// file 28
	kImageRestaurantBackground,
	kImageRestaurantAnimation1,
	kImageRestaurantAnimation2,
	kImageRestaurantAnimation3,
	kImageRestaurantAnimation4,
	kImageRestaurantAnimation5,
	kImageRestaurantAnimation6,
	kImageRestaurantAnimation7,
	kImageRestaurantAnimation8,
	kImageRestaurantAnimation9,
	kImageRestaurantAnimation10,
	kImageRestaurantAnimation11,
	kImageRestaurantAnimation12,
	kImageRestaurantAnimation13,
	kImageRestaurantAnimation14,
	kImageRestaurantAnimation15,
	kImageRestaurantAnimation16,
	kImageRestaurantAnimation17,
	kImageRestaurantAnimation18,
	kImageRestaurantAnimation19,
	kImageRestaurantAnimation20,
	kImageRestaurantAnimation21,
	kImageRestaurantAnimation22,
	// file 29
	kImageRestaurantRogerBackground,
	kImageRestaurantRogerEyes1Closed,
	kImageRestaurantRogerMouthOpen,
	kImageRestaurantRogerPlayingChess,
	kImageRestaurantRogerWalletRemoved,
	kImageRestaurantRogerHandAnimation1,
	kImageRestaurantRogerHandAnimation2,
	kImageRestaurantRogerHandAnimation3,
	kImageRestaurantRogerHandAnimation4,
	kImageRestaurantRogerHandAnimation5,
	kImageRestaurantRogerEyes2Closed,
	kImageRestaurantRogerChessBoard,
	kImageRestaurantRogerEyes2Open,
	kImageRestaurantRogerDummy1,
	// file 30
	kImageRogerOutsideBackground,
	kImageRogerOutsideMouthOpen,
	// file 31
	kImageIntroScreenBackground,
	kImageIntroScreenShipAnimation1,
	kImageIntroScreenShipAnimation2,
	kImageIntroScreenShipAnimation3,
	kImageIntroScreenShipAnimation4,
	kImageIntroScreenShipAnimation5,
	kImageIntroScreenShipAnimation6,
	// file 32
	kImageBusStationSignBackground,
	kImageBusStationSignPrice,
	kImageBusStationSignPleaseWait,
	kImageBusStationSignPleasantFlight,
	// file 33
	kImageShipSleepCabinBackground,
	kImageShipSleepCabinTerminalWarning,
	kImageShipSleepCabinTerminal1,
	kImageShipSleepCabinTerminal2,
	kImageShipSleepCabinStatusLight,
	kImageShipSleepCabinTerminal3,
	// file 34
	kImageShipAirlockBackground,
	kImageShipAirlockDoorLeftAnimation1,
	kImageShipAirlockDoorLeftAnimation2,
	kImageShipAirlockDoorLeftAnimation3,
	kImageShipAirlockDoorRightAnimation1,
	kImageShipAirlockDoorRightAnimation2,
	kImageShipAirlockDoorRightAnimation3,
	kImageShipAirlockHelmetRemoved,
	kImageShipAirlockSpacesuitRemoved,
	kImageShipAirlockSupplyRemoved,
	kImageShipAirlockDoorLeftButton,
	kImageShipAirlockDoorRightButton,
	kImageShipAirlockManometerAnimation1,
	kImageShipAirlockManometerAnimation2,
	kImageShipAirlockManometerAnimation3,
	kImageShipAirlockManometerAnimation4,
	kImageShipAirlockManometerAnimation5,
	kImageShipAirlockManometerAnimation6,
	// file 35
	kImageAxacussSpaceBackground,
	kImageAxacussSpaceShipAnimation1,
	kImageAxacussSpaceShipAnimation2,
	kImageAxacussSpaceShipAnimation3,
	kImageAxacussSpaceShipAnimation4,
	kImageAxacussSpaceShipAnimation5,
	kImageAxacussSpaceShipAnimation6,
	kImageAxacussSpaceShipAnimation7,
	kImageAxacussSpaceBusAnimation1,
	kImageAxacussSpaceBusAnimation2,
	kImageAxacussSpaceBusAnimation3,
	kImageAxacussSpaceBusAnimation4,
	kImageAxacussSpaceBusAnimation5,
	kImageAxacussSpaceBusAnimation6,
	kImageAxacussSpaceBusAnimation7,
	kImageAxacussSpaceBusAnimation8,
	kImageAxacussSpaceBusAnimation9,
	kImageAxacussSpaceBusAnimation10,
	kImageAxacussSpaceBusAnimation11,
	kImageAxacussSpaceBusAnimation12,
	kImageAxacussSpaceBusAnimation13,
	kImageAxacussSpaceBusAnimation14,
	// file 36
	kImageAxacussanCapsuleBackground,
	kImageAxacussanCapsuleRobotAnimation1,
	kImageAxacussanCapsuleRobotAnimation2,
	kImageAxacussanCapsuleRobotAnimation3,
	kImageAxacussanCapsuleRobotAnimation4,
	kImageAxacussanCapsuleDummy1,
	// file 37
	kImageArsanoMeetupBackground,
	kImageArsanoMeetupRestaurantLightAnimation1,
	kImageArsanoMeetupRestaurantLightAnimation2,
	kImageArsanoMeetupRestaurantLightAnimation3,
	kImageArsanoMeetupRestaurantLightAnimation4,
	kImageArsanoMeetupRestaurantLightAnimation5,
	kImageArsanoMeetupRestaurantDoorAnimation1,
	kImageArsanoMeetupRestaurantDoorAnimation2,
	kImageArsanoMeetupRestaurantDoorSignAnimation1,
	kImageArsanoMeetupRestaurantDoorSignAnimation2,
	kImageArsanoMeetupRestaurantDoorSignAnimation3,
	kImageArsanoMeetupRestaurantDoorSignAnimation4,
	kImageArsanoMeetupRestaurantDoorSignAnimation5,
	kImageArsanoMeetupRestaurantSignAnimation1,
	kImageArsanoMeetupRestaurantSignAnimation2,
	kImageArsanoMeetupRestaurantSignAnimation3,
	kImageArsanoMeetupRestaurantSignAnimation4,
	kImageArsanoMeetupRestaurantSignAnimation5,
	kImageArsanoMeetupRestaurantSignAnimation6,
	kImageArsanoMeetupRestaurantSignAnimation7,
	kImageArsanoMeetupRestaurantSignAnimation8,
	kImageArsanoMeetupRestaurantSignAnimation9,
	kImageArsanoMeetupRestaurantSignAnimation10,
	kImageArsanoMeetupRestaurantSignAnimation11,
	kImageArsanoMeetupRestaurantSignAnimation12,
	kImageArsanoMeetupRestaurantSignAnimation13,
	kImageArsanoMeetupRestaurantSignAnimation14,
	// file 38
	kImageArsanoAfterNovaBackground,
	kImageArsanoAfterNovaRogerShipAnimation1,
	kImageArsanoAfterNovaRogerShipAnimation2,
	kImageArsanoAfterNovaRogerShipAnimation3,
	kImageArsanoAfterNovaRogerShipAnimation4,
	kImageArsanoAfterNovaRogerShipAnimation5,
	kImageArsanoAfterNovaRogerShipAnimation6,
	kImageArsanoAfterNovaRogerShipAnimation7,
	kImageArsanoAfterNovaRogerShipAnimation8,
	kImageArsanoAfterNovaRogerShipAnimation9,
	kImageArsanoAfterNovaRogerShipAnimation10,
	kImageArsanoAfterNovaRogerShipAnimation11,
	kImageArsanoAfterNovaRoger,
	// file 39
	kImageArsanoDesolate,
	// file 40
	kImageIntersectionBackground,
	kImageIntersectionGuardRemoved,
	kImageIntersectionGuardMouthOpen,
	kImageIntersectionGuardShootAnimation1,
	kImageIntersectionGuardShootAnimation2,
	kImageIntersectionGuardMouthClosed,
	kImageIntersectionDoorOpen,
	kImageIntersectoinKeycard,
	// file 41
	kImageInformationDeskBackground,
	kImageInformationDeskAlienMouthOpen,
	kImageInformationDeskAlienHandMoved,
	kImageInformationDeskAlienShoot,
	// file 42
	kImageArtGalleryBackground,
	kImageArtGalleryAlienShootAnimation1,
	kImageArtGalleryAlienShootAnimation2,
	kImageArtGalleryAlienShootAnimation3,
	kImageArtGalleryThrowingBlockAnimation1,
	kImageArtGalleryThrowingBlockAnimation2,
	kImageArtGalleryThrowingBlockAnimation3,
	kImageArtGalleryThrowingBlockAnimation4,
	kImageArtGalleryThrowingBlockAnimation5,
	kImageArtGalleryThrowingBlockAnimation6,
	kImageArtGalleryThrowingBlockAnimation7,
	kImageArtGalleryDummy1,
	// file 43
	kImageCellBackground,
	kImageCellCablePluggedIn,
	kImageCellCableUnplugged,
	kImageCellCableCutUnplugged,
	kImageCellCableCutPluggedIn,
	kImageCellCableCutTableUnplugged,
	kImageCellCableCutTablePluggedIn,
	kImageCellTableTablet,
	kImageCellRobotComesAnimation1,
	kImageCellRobotComesAnimation2,
	kImageCellRobotComesAnimation3,
	kImageCellRobotComesAnimation4,
	kImageCellRobotComesAnimation5,
	kImageCellRobotComesAnimation6,
	kImageCellRobotComesAnimation7,
	kImageCellRobotComesAnimation8,
	kImageCellRobotComesAnimation9,
	kImageCellRobotComesAnimation10,
	kImageCellRobotComesAnimation11,
	kImageCellRobotLeavesAnimation1,
	kImageCellRobotLeavesAnimation2,
	kImageCellRobotLeavesAnimation3,
	kImageCellRobotLeavesAnimation4,
	kImageCellRobotLeavesAnimation5,
	kImageCellRobotLeavesAnimation6,
	kImageCellRobotLeavesAnimation7,
	kImageCellRobotLeavesAnimation8,
	kImageCellRobotLeavesAnimation9,
	kImageCellRobotSparks,
	kImageCellRobotBroken,
	kImageCellDoorClosed,
	kImageCellDummy1,
	// file 55
	kImageOutroScreen
};

}

#endif