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

#ifndef SCI_RESOURCE_RESOURCE_INTERN_H
#define SCI_RESOURCE_RESOURCE_INTERN_H

#include "sci/resource/resource.h"

namespace Common {
class MacResManager;
}

namespace Sci {

enum ResSourceType {
	kSourceDirectory = 0,	///< Directories containing game resources/patches
	kSourcePatch,			///< External resource patches
	kSourceVolume,			///< Game resources (resource.* or ressci.*)
	kSourceExtMap,			///< Non-audio resource maps
	kSourceIntMap,			///< SCI1.1 and later audio resource maps
	kSourceAudioVolume,		///< Audio resources - resource.sfx / resource.aud
	kSourceExtAudioMap,		///< SCI1 audio resource maps
	kSourceWave,			///< External WAVE files, patched in as sound resources
	kSourceMacResourceFork,	///< Mac SCI1.1 and later resource forks
	kSourceChunk,			///< Script chunk resources (*.chk)
	kSourceScummVM			///< Built-in resource patcher
};


class ResourceSource {
protected:
	const ResSourceType _sourceType;
	const Common::Path _name;

public:
	bool _scanned;
	const Common::FSNode * const _resourceFile;
	const int _volumeNumber;

protected:
	ResourceSource(ResSourceType type, const Common::Path &name, int volNum = 0, const Common::FSNode *resFile = 0);
public:
	virtual ~ResourceSource();

	ResSourceType getSourceType() const { return _sourceType; }
	const Common::Path &getLocationName() const { return _name; }

	// Auxiliary method, used by loadResource implementations.
	Common::SeekableReadStream *getVolumeFile(ResourceManager *resMan, Resource *res);

	/**
	 * TODO: Document this
	 */
	virtual ResourceSource *findVolume(ResourceSource *map, int volNum) {
		return NULL;
	}

	/**
	 * Scan this source for TODO.
	 */
	virtual void scanSource(ResourceManager *resMan) {}

	/**
	 * Load a resource.
	 */
	virtual void loadResource(ResourceManager *resMan, Resource *res);

	// FIXME: This audio specific method is a hack. After all, why should a
	// ResourceSource or a Resource (which uses this method) have audio
	// specific methods? But for now we keep this, as it eases transition.
	virtual uint32 getAudioCompressionType() const { return 0; }
};

class DirectoryResourceSource : public ResourceSource {
public:
	DirectoryResourceSource(const Common::Path &name) : ResourceSource(kSourceDirectory, name) {}

	void scanSource(ResourceManager *resMan) override;
};

class PatchResourceSource : public ResourceSource {
public:
	PatchResourceSource(const Common::Path &name) : ResourceSource(kSourcePatch, name) {}

	void loadResource(ResourceManager *resMan, Resource *res) override;
};

class VolumeResourceSource : public ResourceSource {
protected:
	ResourceSource * const _associatedMap;

public:
	VolumeResourceSource(const Common::Path &name, ResourceSource *map, int volNum, ResSourceType type = kSourceVolume)
		: ResourceSource(type, name, volNum), _associatedMap(map) {
	}

	VolumeResourceSource(const Common::Path &name, ResourceSource *map, int volNum, const Common::FSNode *resFile)
		: ResourceSource(kSourceVolume, name, volNum, resFile), _associatedMap(map) {
	}

	ResourceSource *findVolume(ResourceSource *map, int volNum) override {
		if (_associatedMap == map && _volumeNumber == volNum)
			return this;
		return NULL;
	}
};

class ExtMapResourceSource : public ResourceSource {
public:
	ExtMapResourceSource(const Common::Path &name, int volNum, const Common::FSNode *resFile = 0)
		: ResourceSource(kSourceExtMap, name, volNum, resFile) {
	}

	void scanSource(ResourceManager *resMan) override;
};

class IntMapResourceSource : public ResourceSource {
public:
	uint16 _mapNumber;
	IntMapResourceSource(const Common::Path &name, int volNum, int mapNum)
		: ResourceSource(kSourceIntMap, name, volNum), _mapNumber(mapNum) {
	}

	void scanSource(ResourceManager *resMan) override;
};

class AudioVolumeResourceSource : public VolumeResourceSource {
protected:
	struct CompressedTableEntry {
		uint32 offset;
		uint32 size;
	};

	uint32 _audioCompressionType;
	Common::HashMap<uint32, CompressedTableEntry> _compressedOffsets;

public:
	AudioVolumeResourceSource(ResourceManager *resMan, const Common::Path &name, ResourceSource *map, int volNum);

	void loadResource(ResourceManager *resMan, Resource *res) override;

	uint32 getAudioCompressionType() const override;

	bool relocateMapOffset(uint32 &offset, uint32 &size) const {
		if (_audioCompressionType == 0) {
			return true;
		}

		if (!_compressedOffsets.contains(offset)) {
			return false;
		}

		const CompressedTableEntry &entry = _compressedOffsets.getVal(offset);
		offset = entry.offset;
		size = entry.size;
		return true;
	}
};

class ExtAudioMapResourceSource : public ResourceSource {
public:
	ExtAudioMapResourceSource(const Common::Path &name, int volNum)
		: ResourceSource(kSourceExtAudioMap, name, volNum) {
	}

	void scanSource(ResourceManager *resMan) override;
};

class WaveResourceSource : public ResourceSource {
public:
	WaveResourceSource(const Common::Path &name) : ResourceSource(kSourceWave, name) {}

	void loadResource(ResourceManager *resMan, Resource *res) override;
};

/**
 * Reads SCI1.1+ resources from a Mac resource fork.
 */
class MacResourceForkResourceSource : public ResourceSource {
public:
	MacResourceForkResourceSource(const Common::Path &name, int volNum);
	~MacResourceForkResourceSource() override;

	void scanSource(ResourceManager *resMan) override;

	void loadResource(ResourceManager *resMan, Resource *res) override;

protected:
	Common::MacResManager *_macResMan;

	bool isCompressableResource(ResourceType type) const;
	void decompressResource(Common::SeekableReadStream *stream, Resource *resource) const;
};

#ifdef ENABLE_SCI32

/**
 * Reads resources from SCI2.1+ chunk resources
 */
class ChunkResourceSource : public ResourceSource {
public:
	ChunkResourceSource(const Common::Path &name, uint16 number);

	void scanSource(ResourceManager *resMan) override;
	void loadResource(ResourceManager *resMan, Resource *res) override;

	uint16 getNumber() const { return _number; }

protected:
	uint16 _number;

	struct ResourceEntry {
		uint32 offset;
		uint32 length;
	};

	Common::HashMap<ResourceId, ResourceEntry, ResourceIdHash> _resMap;
};

#endif

} // End of namespace Sci

#endif // SCI_RESOURCE_RESOURCE_INTERN_H
