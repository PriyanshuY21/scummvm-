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

#ifndef NUVIE_CORE_LOOKUP_H
#define NUVIE_CORE_LOOKUP_H

namespace Ultima {
namespace Nuvie {

class Configuration;

class Look {
	const Configuration *config;
	const char *look_tbl[2048];
	uint16 max_len;
	unsigned char *look_data;
	char *desc_buf;

public:

	Look(const Configuration *cfg);
	~Look();

	bool init();

// if description has a plural form, true is returned in plural
	const char *get_description(uint16 tile_num, bool *plural);
	bool has_plural(uint16 tile_num) const;
	uint16 get_max_len() const;

	void print();

protected:
};

} // End of namespace Nuvie
} // End of namespace Ultima

#endif
