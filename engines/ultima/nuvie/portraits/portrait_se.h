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

#ifndef NUVIE_PORTRAIT_PORTRAIT_SE_H
#define NUVIE_PORTRAIT_PORTRAIT_SE_H

#include "ultima/nuvie/portraits/portrait.h"
#include "ultima/nuvie/files/u6_lib_n.h"

namespace Ultima {
namespace Nuvie {

class Configuration;
class Actor;

class PortraitSE : public Portrait {
	U6Lib_n faces;

public:
	PortraitSE(const Configuration *cfg): Portrait(cfg) {};

	bool init() override;
	bool load(NuvieIO *objlist) override;
	unsigned char *get_portrait_data(Actor *actor) override;

private:

	U6Shape *get_background_shape(Actor *actor);
	uint8 get_background_shape_num(Actor *actor) const;
	uint8 get_portrait_num(Actor *actor) const override;

};

} // End of namespace Nuvie
} // End of namespace Ultima

#endif
