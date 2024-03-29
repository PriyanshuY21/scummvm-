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
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

#ifndef CRAB_CHAPTERINTRO_H
#define CRAB_CHAPTERINTRO_H

#include "crab/ui/button.h"
#include "crab/ui/dialogbox.h"
#include "crab/TTSHandler.h"

namespace Crab {

namespace pyrodactyl {
namespace anim {
class Sprite;
} // End of namespace anim

namespace ui {
class ChapterIntro : public TTSHandler {
	// This contains the background image info and start button
	GameDialogBox _dialog;

	// This is where the sprite is drawn
	Element _pos;

	// The traits button
	Button _traits;

public:
	// Should we show the traits screen
	bool _showTraits;

	ChapterIntro() {
		_showTraits = false;
	}

	void load(rapidxml::xml_node<char> *node);

	bool handleEvents(Common::Event &event);

	void draw(pyrodactyl::event::Info &info, Common::String &text,
			  pyrodactyl::anim::Sprite *curSp, const pyrodactyl::people::PersonState &state);
};
} // End of namespace ui
} // End of namespace pyrodactyl

} // End of namespace Crab

#endif // CRAB_CHAPTERINTRO_H
