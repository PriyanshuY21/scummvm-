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

/* Sound engine */
#ifndef SCI_SOUND_AUDIO_H
#define SCI_SOUND_AUDIO_H

#include "sci/engine/vm_types.h"
#include "audio/mixer.h"

namespace Audio {
class RewindableAudioStream;
} // End of namespace Audio

namespace Sci {

enum AudioCommands {
	kSciAudioWPlay = 1, /* Loads an audio stream */
	kSciAudioPlay = 2, /* Plays an audio stream */
	kSciAudioStop = 3, /* Stops an audio stream */
	kSciAudioPause = 4, /* Pauses an audio stream */
	kSciAudioResume = 5, /* Resumes an audio stream */
	kSciAudioPosition = 6, /* Return current position in audio stream */
	kSciAudioRate = 7, /* Return audio rate */
	kSciAudioVolume = 8, /* Return audio volume */
	kSciAudioLanguage = 9, /* Return audio language */
	kSciAudioCD = 10 /* Plays SCI1.1 CD audio */
};

#define AUDIO_VOLUME_MAX 127

class Resource;
class ResourceId;
class ResourceManager;
class SegManager;

class AudioPlayer {
public:
	AudioPlayer(ResourceManager *resMan);
	~AudioPlayer();

	void setAudioRate(uint16 rate) { _audioRate = rate; }
	Audio::SoundHandle *getAudioHandle() { return &_audioHandle; }
	Audio::RewindableAudioStream *getAudioStream(uint32 number, uint32 volume, int *sampleLen);
	int getAudioPosition();
	int startAudio(uint16 module, uint32 tuple);
	int wPlayAudio(uint16 module, uint32 tuple);
	void stopAudio();
	void pauseAudio();
	void resumeAudio();

	void handleFanmadeSciAudio(reg_t sciAudioObject, SegManager *segMan);

	int audioCdPlay(int track, int start, int duration);
	void audioCdStop();
	void audioCdUpdate();
	int audioCdPosition();

	void stopAllAudio();

	void incrementPlayCounter();
	uint16 getPlayCounter();

private:
	ResourceManager *_resMan;
	uint16 _audioRate;
	Audio::SoundHandle _audioHandle;
	Audio::Mixer *_mixer;
	uint32 _audioCdStart;
	bool _wPlayFlag;
	bool _initCD;
	uint16 _playCounter;
};

} // End of namespace Sci

#endif // SCI_SOUND_AUDIO_H
