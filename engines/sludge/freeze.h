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
#ifndef SLUDGE_FREEZE_H
#define SLUDGE_FREEZE_H

#include "graphics/surface.h"

namespace Sludge {

struct OnScreenPerson;
struct PersonaAnimation;
struct ScreenRegion;
struct SpeechStruct;
struct StatusStuff;
struct EventHandlers;
struct ScreenRegion;

typedef Common::List<ScreenRegion *> ScreenRegionList;
typedef Common::List<OnScreenPerson *> OnScreenPersonList;

class Parallax;

struct FrozenStuffStruct {
	OnScreenPersonList *allPeople;
	ScreenRegionList *allScreenRegions;
	Graphics::Surface backdropSurface;
	Graphics::Surface lightMapSurface;
	uint8 *zBufferTex;
	int zPanels;
	ParallaxLayers *parallaxLayers;
	int lightMapNumber, zBufferNumber;
	SpeechStruct *speech;
	StatusStuff  *frozenStatus;
	EventHandlers *currentEvents;
	PersonaAnimation  *mouseCursorAnim;
	int mouseCursorFrameNum;
	int cameraX, cameraY, sceneWidth, sceneHeight;
	float cameraZoom;

	FrozenStuffStruct *next;
};

} // End of namespace Sludge

#endif
