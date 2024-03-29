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

#include "ultima/shared/std/string.h"
#include "ultima/nuvie/core/nuvie_defs.h"
#include "ultima/nuvie/misc/u6_misc.h"
#include "ultima/nuvie/gui/gui.h"
#include "ultima/nuvie/gui/gui_dialog.h"

namespace Ultima {
namespace Nuvie {

GUI_Dialog::GUI_Dialog(int x, int y, int w, int h, uint8 r, uint8 g, uint8 b, bool is_moveable)
	: GUI_Widget(nullptr, x, y, w, h), R(r), G(g), B(b), bg_color(0), drag(false),
	  can_drag(is_moveable), button_x(0), button_y(0), old_x(-1), old_y(-1),
	  backingstore(nullptr) {
	backingstore_rect.setWidth(w);
	backingstore_rect.setHeight(h);
	loadBorderImages();
}

GUI_Dialog::~GUI_Dialog() {
	if (backingstore)
		free(backingstore);

	for (int i = 0; i < ARRAYSIZE(border); i++)
		delete border[i];
}

void GUI_Dialog::loadBorderImages() {
	char filename[15]; // BorderU6_x.bmp\0
	Common::Path datadir = GUI::get_gui()->get_data_dir();
	Common::Path imagefile;

	for (int i = 0; i < 8; i++) {
		Common::sprintf_s(filename, "Border%s_%d.bmp", "U6", i + 1);
		build_path(datadir, filename, imagefile);
		border[i] = SDL_LoadBMP(imagefile);
		if (border[i] == nullptr) {
			DEBUG(0, LEVEL_ERROR, "Failed to load %s from '%s' directory\n", filename, datadir.toString().c_str());
		}
	}
}

/* Map the color to the display */
void GUI_Dialog::SetDisplay(Screen *s) {
	GUI_Widget::SetDisplay(s);
	bg_color = surface->format.RGBToColor(R, G, B);
}

/* Show the widget  */
void
GUI_Dialog::Display(bool full_redraw) {
	int i;
	if (old_x != area.left || old_y != area.top) {
		if (backingstore) {
			screen->restore_area(backingstore, &backingstore_rect, nullptr, nullptr, false);
			screen->update(backingstore_rect.left, backingstore_rect.top,
				backingstore_rect.width(), backingstore_rect.height());
		}

		backingstore_rect.moveTo(area.left, area.top);
		backingstore = screen->copy_area(&backingstore_rect, backingstore);

		old_x = area.left;
		old_y = area.top;
	}

	Common::Rect framerect = area;
	framerect.grow(-8);
	SDL_FillRect(surface, &framerect, bg_color);

// Draw border corners

	Common::Rect dst;
	dst = area;
	dst.setWidth(8);
	dst.setHeight(8);
	SDL_BlitSurface(border[0], nullptr, surface, &dst);

	dst.left = area.left + area.width() - 8;
	dst.top = area.top;
	dst.setWidth(8);
	dst.setHeight(8);
	SDL_BlitSurface(border[2], nullptr, surface, &dst);

	dst.left = area.left + area.width() - 8;
	dst.top = area.top + area.height() - 8;
	dst.setWidth(8);
	dst.setHeight(8);
	SDL_BlitSurface(border[4], nullptr, surface, &dst);

	dst.left = area.left;
	dst.top = area.top + area.height() - 8;
	dst.setWidth(8);
	dst.setHeight(8);
	SDL_BlitSurface(border[6], nullptr, surface, &dst);

// Draw top and bottom border lines

	for (i = area.left + 8; i < area.left + area.width() - 24; i += 16) {
		dst.left = i;
		dst.top = area.top;
		dst.setWidth(16);
		dst.setHeight(8);
		SDL_BlitSurface(border[1], nullptr, surface, &dst);

		dst.left = i;
		dst.top = area.top + area.height() - 8;
		dst.setWidth(16);
		dst.setHeight(8);
		SDL_BlitSurface(border[5], nullptr, surface, &dst);
	}

	if (i < area.left + area.width() - 8) { // draw partial border images
		Common::Rect src;
		src.left = 0;
		src.top = 0;
		src.setWidth(area.left + area.width() - 8 - i);
		src.setHeight(8);

		dst.left = i;
		dst.top = area.top;
		dst.setWidth(src.width());
		dst.setHeight(8);
		SDL_BlitSurface(border[1], &src, surface, &dst);

		dst.left = i;
		dst.top = area.top + area.height() - 8;
		dst.setWidth(src.width());
		dst.setHeight(8);
		SDL_BlitSurface(border[5], &src, surface, &dst);
	}

// Draw left and right sides


	for (i = area.top + 8; i < area.top + area.height() - 24; i += 16) {
		dst.left = area.left;
		dst.top = i;
		dst.setWidth(8);
		dst.setHeight(16);
		SDL_BlitSurface(border[7], nullptr, surface, &dst);

		dst.left = area.left + area.width() - 8;
		dst.top = i;
		dst.setWidth(8);
		dst.setHeight(16);
		SDL_BlitSurface(border[3], nullptr, surface, &dst);
	}

	if (i < area.top + area.height() - 8) { // draw partial border images
		Common::Rect src;
		src.left = 0;
		src.top = 0;
		src.setWidth(8);
		src.setHeight(area.top + area.height() - 8 - i);

		dst.left = area.left;
		dst.top = i;
		dst.setWidth(8);
		dst.setHeight(src.height());
		SDL_BlitSurface(border[7], &src, surface, &dst);

		dst.left = area.left + area.width() - 8;
		dst.top = i;
		dst.setWidth(8);
		dst.setHeight(src.height());
		SDL_BlitSurface(border[3], &src, surface, &dst);
	}

	DisplayChildren();

	screen->update(area.left, area.top, area.width(), area.height());

	return;
}

GUI_status GUI_Dialog::MouseDown(int x, int y, Shared::MouseButton button) {
	drag = can_drag;
	button_x = x;
	button_y = y;

	grab_focus();

	return GUI_YUM;
}

GUI_status GUI_Dialog::MouseUp(int x, int y, Shared::MouseButton button) {
	drag = false;

	release_focus();

	return GUI_YUM;
}

GUI_status GUI_Dialog::MouseMotion(int x, int y, uint8 state) {
	if (!drag)
		return GUI_PASS;

	int dx = x - button_x;
	int dy = y - button_y;

	button_x = x;
	button_y = y;

	GUI::get_gui()->moveWidget(this, dx, dy);
// Redraw();

	return GUI_YUM;
}

void GUI_Dialog::MoveRelative(int dx, int dy) {
	int new_x = area.left + dx;

	if (new_x < 0) {
		dx = -area.left;
	} else if (new_x + area.width() > screen->get_width()) {
		dx = screen->get_width() - (area.left + area.width());
	}

	int new_y = area.top + dy;

	if (new_y < 0) {
		dy = -area.top;
	} else if (new_y + area.height() > screen->get_height()) {
		dy = screen->get_height() - (area.top + area.height());
	}

	GUI_Widget::MoveRelative(dx, dy);

	return;
}

} // End of namespace Nuvie
} // End of namespace Ultima
