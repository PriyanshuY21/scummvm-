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

#ifndef GOB_PREGOB_ONCEUPON_STORK_H
#define GOB_PREGOB_ONCEUPON_STORK_H

#include "common/system.h"

#include "gob/aniobject.h"

namespace Common {
	class String;
}

namespace Gob {

class GobEngine;

class Surface;
class ANIFile;

namespace OnceUpon {

/** The stork in Baba Yaga / dragon in Abracadabra. */
class Stork : public ANIObject {
public:
	/** Information on how to drop the bundle. */
	struct BundleDrop {
		int16 anim; ///< Animation of the bundle floating down

		int16 dropX; ///< X position the stork drops the bundle
		int16 landY; ///< Y position the bundle lands

		bool dropWhileFar; ///< Does the stork drop the bundle while far instead of near?
	};

	Stork(GobEngine *vm, const ANIFile &ani);
	~Stork() override;

	/** Has the bundle landed? */
	bool hasBundleLanded() const;

	/** Drop the bundle. */
	void dropBundle(const BundleDrop &drop);

	/** Draw the current frame onto the surface and return the affected rectangle. */
	bool draw(Surface &dest, int16 &left, int16 &top, int16 &right, int16 &bottom) override;
	/** Draw the current frame from the surface and return the affected rectangle. */
	bool clear(Surface &dest, int16 &left, int16 &top, int16 &right, int16 &bottom) override;

	/** Advance the animation to the next frame. */
	void advance() override;

private:
	enum State {
		kStateFlyNearWithBundle    = 0,
		kStateFlyFarWithBundle       ,
		kStateFlyNearWithoutBundle   ,
		kStateFlyFarWithoutBundle
	};


	Surface   *_frame;
	ANIObject *_bundle;

	State _state;

	bool       _shouldDrop;
	BundleDrop _bundleDrop;


	void setState(State state, uint16 anim);
	void setState(State state, uint16 anim, int16 x);

	void dropBundle(State state, uint16 anim);
};

} // End of namespace OnceUpon

} // End of namespace Gob

#endif // GOB_PREGOB_ONCEUPON_STORK_H
