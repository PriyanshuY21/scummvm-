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


#ifndef TEENAGENT_PACK_H
#define TEENAGENT_PACK_H

#include "common/file.h"
#include "common/array.h"

namespace TeenAgent {

class Pack {
protected:
	uint32 _fileCount;
public:
	Pack(): _fileCount(0) {}
	virtual ~Pack() {}
	virtual bool open(const Common::Path &filename) = 0;
	virtual void close() = 0;

	virtual uint32 fileCount() const { return _fileCount; }
	virtual uint32 getSize(uint32 id) const = 0;
	virtual uint32 read(uint32 id, byte *dst, uint32 size) const = 0;
	virtual Common::SeekableReadStream *getStream(uint32 id) const = 0;
};

///FilePack keeps opened file and returns substream for each request.
class FilePack : public Pack {
	mutable Common::File file;
	uint32 *offsets;

public:
	FilePack();
	~FilePack() override;

	bool open(const Common::Path &filename) override;
	void close() override;

	uint32 getSize(uint32 id) const override;
	uint32 read(uint32 id, byte *dst, uint32 size) const override;
	Common::SeekableReadStream *getStream(uint32 id) const override;
};

/** Pack file which reopens file each request. Do not keep file descriptor open.
 ** Useful for minimizing file descriptors opened at the same time. Critical for PSP backend.
 **/
class TransientFilePack : public Pack {
	uint32 *offsets;
	Common::Path _filename;

public:
	TransientFilePack();
	~TransientFilePack() override;

	bool open(const Common::Path &filename) override;
	void close() override;

	uint32 getSize(uint32 id) const override;
	uint32 read(uint32 id, byte *dst, uint32 size) const override;
	Common::SeekableReadStream *getStream(uint32 id) const override;
};

///MemoryPack loads whole pack in memory, currently unused.
class MemoryPack : public Pack {
	struct Chunk {
		byte *data;
		uint32 size;
		inline Chunk(): data(0), size(0) {}
		inline Chunk(const Chunk &c) : data(c.data), size(c.size) { c.reset(); }
		inline Chunk &operator=(const Chunk &c) {
			data = c.data;
			size = c.size;
			c.reset();
			return *this;
		}
		inline ~Chunk() { delete[] data; }
		inline void reset() const {
			Chunk *c = const_cast<Chunk *>(this);
			c->data = 0;
			c->size = 0;
		}
	};
	Common::Array<Chunk> chunks;

public:
	bool open(const Common::Path &filename) override;
	void close() override;

	uint32 getSize(uint32 id) const override;
	uint32 read(uint32 id, byte *dst, uint32 size) const override;
	Common::SeekableReadStream *getStream(uint32 id) const override;
};

} // End of namespace TeenAgent

#endif
