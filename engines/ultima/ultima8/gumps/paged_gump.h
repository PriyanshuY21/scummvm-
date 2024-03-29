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

#ifndef ULTIMA8_GUMPS_PAGEDGUMP_H
#define ULTIMA8_GUMPS_PAGEDGUMP_H

#include "ultima/ultima8/gumps/modal_gump.h"
#include "ultima/ultima8/misc/classtype.h"

namespace Ultima {
namespace Ultima8 {

/**
 * Base class for gumps which have multiple pages (books, save/load game)
 */
class PagedGump : public ModalGump {
public:
	ENABLE_RUNTIME_CLASSTYPE()

	PagedGump(int left, int right, int top, int shape);
	~PagedGump() override;

	// Init the gump, call after construction
	void InitGump(Gump *newparent, bool take_focus = true) override;
	void Close(bool no_del = false) override;

	// Paint the Gump
	void PaintThis(RenderSurface *, int32 lerp_factor, bool scaled) override;

	void onMouseDouble(int button, int32 mx, int32 my) override;
	bool OnKeyDown(int key, int mod) override;
	void ChildNotify(Gump *child, uint32 message) override;

	//! add a page. Note: g already has to be a child gump.
	void addPage(Gump *g);
	void showPage(uint index);

	void enableButtons(bool enabled) {
		_buttonsEnabled = enabled;
	}

	bool loadData(Common::ReadStream *rs);
	void saveData(Common::WriteStream *ws) override;

protected:
	int _leftOff, _rightOff, _topOff, _gumpShape;
	Common::Array<Gump *> _gumps;
	Gump *_nextButton;
	Gump *_prevButton;
	uint _current;
	bool _buttonsEnabled;
};

} // End of namespace Ultima8
} // End of namespace Ultima

#endif
