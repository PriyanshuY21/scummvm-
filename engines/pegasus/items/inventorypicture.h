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

#ifndef PEGASUS_ITEMS_INVENTORYPICTURE_H
#define PEGASUS_ITEMS_INVENTORYPICTURE_H

#include "pegasus/input.h"
#include "pegasus/movie.h"
#include "pegasus/surface.h"

namespace Pegasus {

class Inventory;
class Item;
class Input;
class Transition;

class InventoryPicture : public InputHandler, public Picture {
public:
	InventoryPicture(const DisplayElementID, InputHandler *, Inventory *);
	~InventoryPicture() override {}

	void initInventoryImage(Transition *);
	void throwAwayInventoryImage();

	void panelUp();
	void activateInventoryPicture();
	void deactivateInventoryPicture();
	void handleInput(const Input &, const Hotspot *) override;
	bool wantsCursor() override { return false; }

	InventoryResult addInventoryItem(Item *);
	InventoryResult removeInventoryItem(Item *);
	void removeAllItems();
	Item *getCurrentItem() { return _currentItem; }
	void setCurrentItemIndex(int32);
	void setCurrentItemID(ItemID);
	int32 getCurrentItemIndex() { return _currentItemIndex; }
	bool itemInInventory(Item *);
	bool itemInInventory(const ItemID);

protected:
	void getItemXY(uint32, CoordType &, CoordType &);
	void draw(const Common::Rect &) override;
	void drawItemHighlight(const Common::Rect &);
	virtual void highlightCurrentItem();
	virtual void unhighlightCurrentItem() {}
	virtual TimeValue getItemPanelTime(Item *) = 0;

	Inventory *_inventory;
	uint32 _lastReferenceCount;
	Frame _highlightImage;
	Movie _panelMovie;
	int32 _currentItemIndex;
	Item *_currentItem;
	Common::Rect _highlightBounds;
	bool _active, _shouldDrawHighlight;

	Common::Path _pictName;
	Common::Path _movieName;
	Common::Path _highlightName;
	uint16 _itemsPerRow;
	uint16 _numberOfRows;
	uint16 _itemWidth;
	uint16 _itemHeight;
	uint16 _itemX;
	uint16 _itemY;
};

class InventoryItemsPicture : public InventoryPicture {
public:
	InventoryItemsPicture(const DisplayElementID, InputHandler *, Inventory *);
	~InventoryItemsPicture() override {}

	void deactivateInventoryPicture();

	void disableLooping() { _isLooping = false; }

	void setCommPicture();
	void playEndMessage(DisplayElement *);

protected:
	void highlightCurrentItem() override;
	void unhighlightCurrentItem() override;
	TimeValue getItemPanelTime(Item *) override;
	void loopCurrentItem();

	bool _isLooping;
};

class BiochipPicture : public InventoryPicture {
public:
	BiochipPicture(const DisplayElementID, InputHandler *, Inventory *);
	~BiochipPicture() override {}

protected:
	void unhighlightCurrentItem() override;
	TimeValue getItemPanelTime(Item *) override;
};

} // End of namespace Pegasus

#endif
