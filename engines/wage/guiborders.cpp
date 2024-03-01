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
 * MIT License..
 *
 * Copyright (c) 2009 Alexei Svitkine, Eugene Sandulenko
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions..
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "wage/wage.h"
#include "wage/gui.h"

namespace Wage {

// Original files sit in engines/wage/guiborders
// to print out similar pictures, use
//   bmpDecoder.getSurface()->debugPrint(0, 0, 0, 0, 0, 1);
// in MacWindowBorder::loadBorder()
//
// TODO: Store these as XPM files?

static const char *wage_border_inact_title[] = {
"......................................  ..  ..  ......................................",
"..                                    ..      ..                                    ..",
"..  ################################  ..  ##  ..  ################################  ..",
"..  ################################      ##      ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################      ##      ################################  ..",
"..  ################################  ..  ##  ..  ################################    ",
"..                                    ..      ..                                      ",
"  ....  ########################  ..................  ########################  ....  ",
"..                                    ..........                                      ",
"..  ################################  ..........  ################################    ",
"..  ################################              ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################              ################################  ..",
"..  ################################  ..........  ################################  ..",
"..                                    ..........                                    ..",
"..................................                  .................................."};

static const char *wage_border_act_noscrollbar_title[] = {
"......................................  ..  ..  ......................................",
"..                                    ..      ..                                    ..",
"..  ################################  ..  ##  ..  ################################  ..",
"..  ################################      ##      ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ########                ########      ##      ################################  ..",
"..  ########  ############  ########      ##      ################################  ..",
"..  ########  ############  ########      ##      ################################  ..",
"..  ########  ############  ########      ##      ################################  ..",
"..  ########  ############  ########      ##      ################################  ..",
"..  ########  ############  ########      ##      ################################  ..",
"..  ########  ############  ########      ##      ################################  ..",
"..  ########                ########      ##      ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################  ##  ##  ##  ################################  ..",
"..  ################################      ##      ################################  ..",
"..  ################################  ..  ##  ..  ################################    ",
"..                                    ..      ..                                      ",
"  ....  ####                ####  ..................  ####                ####  ....  ",
"..                                    ..........                                      ",
"..  ################################  ..........  ################################    ",
"..  ################################              ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################              ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################  ##########  ################################  ..",
"..  ################################              ################################  ..",
"..  ################################  ..........  ################################  ..",
"..                                    ..........                                    ..",
"..................................                  .................................."};

static const char *wage_border_inact[] = {
"......................................  ......................................",
"..                                    ..                                    ..",
"..  ################################  ..  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ..  ################################    ",
"..                                    ..                                      ",
"  ....  ########################  ..........  ########################  ....  ",
"..                                    ..                                      ",
"..  ################################  ..  ################################    ",
"..  ################################      ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ..  ################################  ..",
"..                                    ..                                    ..",
"..................................          .................................."};

static const char *wage_border_act[] = {
"......................................  ......................................",
"..                                    ..                                    ..",
"..  ################################  ..  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ########                ########      ################################  ..",
"..  ########  ############  ########      ################################  ..",
"..  ########  ############  ########      ################################  ..",
"..  ########  ############  ########      ################################  ..",
"..  ########  ############  ########      ################################  ..",
"..  ########  ############  ########      ################################  ..",
"..  ########  ############  ########      ################################  ..",
"..  ########                ########      ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ..  ################################    ",
"..                                    ..                                      ",
"......  ####                ####  ..........  ##########    ##########  ....  ",
"......  ####                ####  ..........  ########        ########  ....  ",
"......  ####                ####  ..........  ######            ######  ....  ",
"......  ####                ####  ..........  ####                ####  ....  ",
"......  ####                ####  ..........  ##                    ##  ....  ",
"......  ####                ####  ..........                            ....  ",
"  ....  ####                ####  ..........  ####                ####  ....  ",
"......  ####                ####  ..........                            ....  ",
"......  ####                ####  ..........  ##                    ##  ....  ",
"......  ####                ####  ..........  ####                ####  ....  ",
"......  ####                ####  ..........  ######            ######  ....  ",
"......  ####                ####  ..........  ########        ########  ....  ",
"......  ####                ####  ..........  ##########    ##########  ....  ",
"..                                    ..                                      ",
"..  ################################  ..  ################################    ",
"..  ################################      ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################  ##  ################################  ..",
"..  ################################      ################################  ..",
"..  ################################  ..  ################################  ..",
"..                                    ..                                    ..",
"..................................          .................................."};

static const byte wage_border_palette[] = {
	0,   0,   0,
	255, 255, 255,
	255, 0,   255
};

void Gui::loadBorders() {
	_consoleWindow->enableScrollbar(true);
	loadBorder(_sceneWindow, wage_border_inact_title, ARRAYSIZE(wage_border_inact_title), Graphics::kWindowBorderTitle, 22);
	loadBorder(_sceneWindow, wage_border_act_noscrollbar_title, ARRAYSIZE(wage_border_act_noscrollbar_title), Graphics::kWindowBorderActive|Graphics::kWindowBorderTitle, 22);
	loadBorder(_consoleWindow, wage_border_inact, ARRAYSIZE(wage_border_inact), Graphics::kWindowBorderScrollbar, 0);
	loadBorder(_consoleWindow, wage_border_act, ARRAYSIZE(wage_border_act), Graphics::kWindowBorderScrollbar|Graphics::kWindowBorderActive, 0);
}

void Gui::loadBorder(Graphics::MacWindow *target, const char *border[], uint height, uint32 flags, int titlePos) {
	uint width = strlen(border[0]) / 2;

	Graphics::ManagedSurface *surface = new Graphics::ManagedSurface();
	surface->create(width, height, Graphics::PixelFormat::createFormatCLUT8());
	surface->setPalette(wage_border_palette, 0, 3);
	surface->setTransparentColor(2);

	for (uint y = 0; y < height; y++) {
		byte *dst = (byte *)surface->getBasePtr(0, y);

		for (uint x = 0; x < width; x++) {
			switch(border[y][x * 2]) {
			case ' ':
				*dst = 0;
				break;

			case '#':
				*dst = 1;
				break;

			case '.':
				*dst = 2;
				break;

			default:
				error("Incorrect symbol in bitmap '%c'(%02x) at %d,%d", border[y][x * 2], border[y][x * 2], x, y);
			}

			dst++;
		}
	}

	Graphics::BorderOffsets offsets;
	offsets.left = 16;
	offsets.right = 16;
	offsets.top = 16;
	offsets.bottom = 16;
	offsets.titleTop = 0;
	offsets.titleBottom = 0;
	offsets.dark = false;
	offsets.upperScrollHeight = 16;
	offsets.lowerScrollHeight = 16;
	offsets.titlePos = titlePos;
	target->setBorder(surface, flags, offsets);
}



} // End of namespace Wage
