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
 *
 * This file is dual-licensed.
 * In addition to the GPLv3 license mentioned above, this code is also
 * licensed under LGPL 2.1. See LICENSES/COPYING.LGPL file for the
 * full text of the license.
 *
 */

#ifndef GOB_PREGOB_ONCEUPON_CHARGENCHILD_H
#define GOB_PREGOB_ONCEUPON_CHARGENCHILD_H

#include "common/system.h"

#include "gob/aniobject.h"

namespace Gob {

class Surface;
class ANIFile;

namespace OnceUpon {

/** The child running around on the character generator screen. */
class CharGenChild : public ANIObject {
public:
	enum Sound {
		kSoundNone = 0,
		kSoundWalk    ,
		kSoundJump
	};

	CharGenChild(const ANIFile &ani);
	~CharGenChild() override;

	/** Advance the animation to the next frame. */
	void advance() override;

	/** Should we play a sound right now? */
	Sound shouldPlaySound() const;
};

} // End of namespace OnceUpon

} // End of namespace Gob

#endif // GOB_PREGOB_ONCEUPON_CHARGENCHILD_H
