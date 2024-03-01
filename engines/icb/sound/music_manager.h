/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1999-2000 Revolution Software Ltd.
 * This code is based on source code created by Revolution Software,
 * used with permission.
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

#ifndef ICB_MUSICMANAGER_H_INCLUDED_
#define ICB_MUSICMANAGER_H_INCLUDED_

#include "engines/icb/common/px_common.h"
#include "engines/icb/sound/direct_sound.h"

#include "common/stream.h"

#include "audio/audiostream.h"
#include "audio/mixer.h"

namespace ICB {

class MusicManager {
private:
	Audio::AudioStream *_audioStream;
	Audio::SoundHandle _handle;

	uint32 m_bufferLength; // Stores the length of the sound buffers in bytes
	int32 m_musicVol;        // The volume the each stream was started at

	uint32 m_wavByteOffsetInCluster;
	uint32 m_wavDataSize;

	bool8 m_paused;
	int32 m_lengthInCycles; // Assumes 12 frames per second

	int32 m_fading;
	int32 m_adjustFadeVol;

	uint32 m_identifier; // Handle if you like of loaded music

public:
	MusicManager();
	~MusicManager();

	bool8 UpdateMusic();

	bool8 LoadMusic(const char *clusterName, uint32 byteOffsetToWav, int32 vol = 128);
	bool8 StartMusic(const char *clusterName, uint32 byteOffsetToWav, int32 vol = 128);
	bool8 PlayMusic();
	void StopMusic();
	void SetMusicPausedStatus(bool8 p = TRUE8);
	void SetMusicVolume(int32 volume);

	bool8 IsPlaying();
	bool8 IsPaused() { return m_paused; }
	int32 GetLength() { return m_lengthInCycles; }

private:
	bool8 OpenMusic(Common::SeekableReadStream *stream);
	void KillBuffer();
	void SetVolume(int32 volume);
	void AdjustVolume(int32 amount);
};

extern MusicManager *g_theMusicManager;

} // End of namespace ICB

#endif
