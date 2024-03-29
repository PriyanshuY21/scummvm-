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

#ifndef VOYEUR_SOUND_H
#define VOYEUR_SOUND_H

#include "common/scummsys.h"
#include "common/path.h"
#include "audio/mixer.h"

namespace Voyeur {

class SoundManager {
private:
	Audio::Mixer *_mixer;
	Audio::SoundHandle _soundHandle;
	int _vocOffset;
public:
	SoundManager(Audio::Mixer *mixer);

	void playVOCMap(byte *voc, int vocSize);
	void stopVOCPlay();
	void abortVOCMap();
	void setVOCOffset(int offset);
	Common::Path getVOCFileName(int idx);
	void startVOCPlay(const Common::Path &filename);
	void startVOCPlay(int soundId);
	int getVOCStatus();
	uint32 getVOCFrame();
};

} // End of namespace Voyeur

#endif /* VOYEUR_SOUND_H */
