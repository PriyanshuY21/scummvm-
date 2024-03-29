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

#ifndef NUVIE_CORE_BACKGROUND_H
#define NUVIE_CORE_BACKGROUND_H

#include "ultima/nuvie/gui/widgets/gui_widget.h"

namespace Ultima {
namespace Nuvie {

class Configuration;
class U6Shape;

class Background: public GUI_Widget {
	const Configuration *config;
	int game_type;

	U6Shape *background;
	uint16 bg_w, bg_h;
	uint16 x_off, y_off, right_bg_x_off, left_bg_x_off, border_width;

public:

	Background(const Configuration *cfg);
	~Background() override;

	bool init();
	uint16 get_border_width() const {
		return border_width;
	}
	void Display(bool full_redraw) override;
	bool drag_accept_drop(int x, int y, int message, void *data) override; // needed for original+_full_map
	void drag_perform_drop(int x, int y, int message, void *data) override; // needed for original+_full_map
	U6Shape *get_bg_shape() {
		return background;
	}
	uint16 get_bg_w() const {
		return bg_w;
	}
};

} // End of namespace Nuvie
} // End of namespace Ultima

#endif
