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

#ifndef GRIM_EMI_LUACODE_COMPONENT_H
#define GRIM_EMI_LUACODE_COMPONENT_H

#include "engines/grim/costume/component.h"
#include "engines/grim/lua/lua.h"

namespace Grim {

class EMILuaCodeComponent : public Component {
public:
	EMILuaCodeComponent(Component *parent, int parentID, const char *name, Component *prevComponent, tag32 tag);
	~EMILuaCodeComponent();
	void init() override;
	int update(uint time) override;
	void reset() override;
	void draw() override;
	void setKey(int val) override;
private:
};

} // end of namespace Grim

#endif
