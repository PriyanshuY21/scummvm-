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

#include "crab/ui/SlideShow.h"

namespace Crab {

using namespace pyrodactyl::ui;
using namespace pyrodactyl::image;
using namespace pyrodactyl::input;

void SlideShow::load(rapidxml::xml_node<char> *node) {
	if (nodeValid(node)) {
		if (nodeValid("pos", node))
			_pos.load(node->first_node("pos"));

		if (nodeValid("bg", node))
			_bg.load(node->first_node("bg"));

		if (nodeValid("prev", node)) {
			_prev.load(node->first_node("prev"));
			_prev._hotkey.set(IU_PREV);
		}

		if (nodeValid("next", node)) {
			_next.load(node->first_node("next"));
			_next._hotkey.set(IU_NEXT);
		}

		_path.clear();
		for (auto n = node->first_node("slide"); n != nullptr; n = n->next_sibling("slide")) {
			Common::Path p;
			loadPath(p, "path", n);
			_path.push_back(p);
		}

		_index = 0;

		loadBool(_usekeyboard, "keyboard", node, false);
	}
}

void SlideShow::draw() {
	_bg.draw();
	_img.draw(_pos.x, _pos.y);

	if (_index > 0)
		_prev.draw();

	if (_index < _path.size() - 1)
		_next.draw();
}

void SlideShow::handleEvents(const Common::Event &event) {
	using namespace pyrodactyl::input;

	if (_index > 0)
		if (_prev.handleEvents(event) == BUAC_LCLICK || (_usekeyboard && g_engine->_inputManager->state(IU_LEFT))) {
			_index--;
			refresh();
		}

	if (_index < _path.size() - 1)
		if (_next.handleEvents(event) == BUAC_LCLICK || (_usekeyboard && g_engine->_inputManager->state(IU_RIGHT))) {
			_index++;
			refresh();
		}
}

void SlideShow::refresh() {
	_img.deleteImage();

	if (_index < _path.size())
		_img.load(_path[_index]);
}

void SlideShow::setUI() {
	_pos.setUI();
	_bg.setUI();
	_prev.setUI();
	_next.setUI();
}

} // End of namespace Crab
