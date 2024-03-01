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

#include "common/endian.h"
#include "common/memstream.h"
#include "common/textconsole.h"
#include "graphics/fonts/amigafont.h"

#include "parallaction/parallaction.h"

namespace Parallaction {


class BraFont : public Font {

protected:
	byte	*_cp;
	uint	_bufPitch;

	uint32	_height;
	byte	_numGlyphs;

	byte	*_widths;
	uint	*_offsets;

	byte	*_data;
	const byte	*_charMap;

	byte mapChar(byte c) {
		return (_charMap == nullptr) ? c : _charMap[c];
	}

public:
	BraFont(Common::ReadStream &stream, const byte *charMap = nullptr) {
		_charMap = charMap;

		_numGlyphs = stream.readByte();
		_height = stream.readUint32BE();

		_widths = (byte *)malloc(_numGlyphs);
		stream.read(_widths, _numGlyphs);

		_offsets = (uint *)malloc(_numGlyphs * sizeof(uint));
		_offsets[0] = 0;
		for (uint i = 1; i < _numGlyphs; i++)
			_offsets[i] = _offsets[i-1] + _widths[i-1] * _height;

		uint size = _offsets[_numGlyphs-1] + _widths[_numGlyphs-1] * _height;

		_data = (byte *)malloc(size);
		stream.read(_data, size);

		_cp = nullptr;
		_bufPitch = 0;
	}

	~BraFont() override {
		free(_widths);
		free(_offsets);
		free(_data);
	}


	uint32 getStringWidth(const char *s) override {
		uint32 len = 0;

		while (*s) {
			byte c = mapChar(*s);
			len += (_widths[c] + 2);
			s++;
		}

		return len;
	}

	uint16 height() override {
		return (uint16)_height;
	}

	uint16 drawChar(unsigned char c) {
		assert(c < _numGlyphs);

		byte *src = _data + _offsets[c];
		byte *dst = _cp;
		uint16 w = _widths[c];

		for (uint16 j = 0; j < height(); j++) {
			for (uint16 k = 0; k < w; k++) {

				if (*src) {
					*dst = (_color) ? _color : *src;
				}

				dst++;
				src++;
			}

			dst += (_bufPitch - w);
		}

		return w + 2;

	}

	void drawString(Graphics::Surface *src, int x, int y, const char *s) override {
		if (src == nullptr)
			return;

		_bufPitch = src->pitch;

		_cp = (byte *)src->getBasePtr(x, y);
		while (*s) {
			byte c = mapChar(*s);
			_cp += drawChar(c);
			s++;
		}
	}

};

const byte _braDosFullCharMap[256] = {
// 0
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 1
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 2
	0x34, 0x49, 0x48, 0x34, 0x34, 0x34, 0x34, 0x47, 0x34, 0x34, 0x34, 0x34, 0x40, 0x34, 0x3F, 0x34,
// 3
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x46, 0x45, 0x34, 0x34, 0x34, 0x42,
// 4
	0x34, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
// 5
	0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x34, 0x34, 0x34, 0x34, 0x34,
// 6
	0x34, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
// 7
	0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x34, 0x34, 0x34, 0x34,
// 8
	0x5E, 0x5D, 0x4E, 0x4B, 0x4D, 0x4C, 0x34, 0x5E, 0x4F, 0x51, 0x50, 0x34, 0x34, 0x34, 0x34, 0x34,
// 9
	0x34, 0x34, 0x34, 0x57, 0x59, 0x58, 0x5B, 0x5C, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// A
	0x4A, 0x52, 0x34, 0x5A, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// B
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// C
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// D
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// E
	0x34, 0x5F, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// F
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34
};

const byte _braDosDemoComicCharMap[] = {
// 0
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 1
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 2
	0x34, 0x49, 0x48, 0x34, 0x34, 0x34, 0x34, 0x47, 0x34, 0x34, 0x34, 0x34, 0x40, 0x34, 0x3F, 0x34,
// 3
	0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x46, 0x45, 0x34, 0x34, 0x34, 0x42,
// 4
	0x34, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
// 5
	0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x34, 0x34, 0x34, 0x34, 0x34,
// 6
	0x34, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
// 7
	0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x34, 0x34, 0x34, 0x34,
// 8
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 9
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// A
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// B
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// C
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// D
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// E
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// F
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34
};

const byte _braDosDemoRussiaCharMap[] = {
// 0
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 1
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 2
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 3
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 4
	0x34, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
// 5
	0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x34, 0x34, 0x34, 0x34, 0x34,
// 6
	0x34, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
// 7
	0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x34, 0x34, 0x34, 0x34,
// 8
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// 9
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// A
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// B
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// C
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// D
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// E
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34,
// F
	0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34
};

class BraInventoryObjects : public BraFont, public Frames {

public:
	BraInventoryObjects(Common::ReadStream &stream) : BraFont(stream) {
	}

	// Frames implementation
	uint16	getNum() override {
		return _numGlyphs;
	}

	byte*	getData(uint16 index) override {
		assert(index < _numGlyphs);
		return _data + (_height * _widths[index]) * index;
	}

	void	getRect(uint16 index, Common::Rect &r) override {
		assert(index < _numGlyphs);
		r.left = 0;
		r.top = 0;
		r.setWidth(_widths[index]);
		r.setHeight(_height);
	}

	uint	getRawSize(uint16 index) override {
		assert(index < _numGlyphs);
		return _widths[index] * _height;
	}

	uint	getSize(uint16 index) override {
		assert(index < _numGlyphs);
		return _widths[index] * _height;
	}

};

class DosFont : public Font {

protected:
	// drawing properties
	byte		*_cp;

	Cnv			*_data;
	byte		_pitch;
	uint32		_bufPitch;

protected:
	virtual uint16 drawChar(char c) = 0;
	virtual uint16 width(byte c) = 0;
	uint16 height() override = 0;

	byte mapChar(byte c) {
		if (c == 0xA5) return 0x5F;
		if (c == 0xDF) return 0x60;

		if (c > 0x7F) return c - 0x7F;

		return c - 0x20;
	}

public:
	DosFont(Cnv *cnv) : _data(cnv), _pitch(cnv->_width), _cp(nullptr), _bufPitch(0) {
	}

	~DosFont() override {
		delete _data;
	}

	void setData() {

	}

	uint32 getStringWidth(const char *s) override {
		uint32 len = 0;

		while (*s) {
			byte c = mapChar(*s);
			len += width(c);
			s++;
		}

		return len;
	}

	void drawString(Graphics::Surface *src, int x, int y, const char *s) override {
		if (src == nullptr)
			return;

		_bufPitch = src->pitch;

		_cp = (byte *)src->getBasePtr(x, y);
		while (*s) {
			byte c = mapChar(*s);
			_cp += drawChar(c);
			s++;
		}
	}
};

class DosDialogueFont : public DosFont {

private:
	static const byte	_glyphWidths[126];

protected:
	uint16 width(byte c) override {
		return _glyphWidths[c];
	}

	uint16 height() override {
		return _data->_height;
	}

public:
	DosDialogueFont(Cnv *cnv) : DosFont(cnv) {
	}

protected:
	uint16 drawChar(char c) override {

		byte *src = _data->getFramePtr(c);
		byte *dst = _cp;
		uint16 w = width(c);

		for (uint16 j = 0; j < height(); j++) {
			for (uint16 k = 0; k < w; k++) {

				if (!*src)
					*dst = _color;

				dst++;
				src++;
			}

			src += (_pitch - w);
			dst += (_bufPitch - w);
		}

		return w;

	}

};

const byte DosDialogueFont::_glyphWidths[126] = {
  0x04, 0x03, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x04, 0x04, 0x06, 0x06, 0x03, 0x05, 0x03, 0x05,
  0x06, 0x06, 0x06, 0x06, 0x07, 0x06, 0x06, 0x06, 0x06, 0x06, 0x03, 0x03, 0x05, 0x04, 0x05, 0x05,
  0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07,
  0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x07, 0x07, 0x07, 0x05, 0x06, 0x05, 0x08, 0x07,
  0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x03, 0x04, 0x05, 0x05, 0x06, 0x06, 0x05,
  0x05, 0x06, 0x05, 0x05, 0x05, 0x05, 0x06, 0x07, 0x05, 0x05, 0x05, 0x05, 0x02, 0x05, 0x05, 0x07,
  0x08, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04,
  0x05, 0x06, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x06, 0x05, 0x05, 0x05, 0x05
};


class DosMonospacedFont : public DosFont {

protected:
	uint16	_width;

protected:
	uint16 width(byte c) override {
		return _width;
	}

	uint16 height() override {
		return _data->_height;
	}

	uint16 drawChar(char c) override {

		byte *src = _data->getFramePtr(c);
		byte *dst = _cp;

		for (uint16 i = 0; i < height(); i++) {
			for (uint16 j = 0; j < _width; j++) {
				if (*src)
					*dst = *src;
				src++;
				dst++;
			}

			dst += (_bufPitch - _width);
			src += (_pitch - _width);
		}

		return _width;
	}

public:
	DosMonospacedFont(Cnv *cnv) : DosFont(cnv) {
		_width = 8;
	}

};

class AmigaFont : public Font {
	Graphics::AmigaFont *_font;

public:
	AmigaFont(Common::SeekableReadStream *stream = nullptr) {
		_font = new Graphics::AmigaFont(stream);
	}
	~AmigaFont() override {
		delete _font;
	}

	uint32 getStringWidth(const char *s) override {
		return _font->getStringWidth(s);
	}
	void drawString(Graphics::Surface *src, int x, int y, const char *s) override {
		_font->drawString(src, s, x, y, src->w, _color);
	}

protected:
	uint16 height() override {
		return _font->getFontHeight();
	}
};

Font *DosDisk_ns::createFont(const char *name, Cnv* cnv) {
	Font *f = nullptr;

	if (!scumm_stricmp(name, "comic"))
		f = new DosDialogueFont(cnv);
	else
	if (!scumm_stricmp(name, "topaz"))
		f = new DosMonospacedFont(cnv);
	else
	if (!scumm_stricmp(name, "slide"))
		f = new DosMonospacedFont(cnv);
	else
		error("unknown dos font '%s'", name);

	return f;
}

Font *AmigaDisk_ns::createFont(const char *name, Common::SeekableReadStream &stream) {
	// TODO: implement AmigaLabelFont for labels
	return new AmigaFont(&stream);
}

Font *DosDisk_br::createFont(const char *name, Common::ReadStream &stream) {
//	debug("DosDisk_br::createFont(%s)", name);
	Font *font;

	if (_vm->getFeatures() & GF_DEMO) {
		if (!scumm_stricmp(name, "russia")) {
			font = new BraFont(stream, _braDosDemoRussiaCharMap);
		} else {
			font = new BraFont(stream, _braDosDemoComicCharMap);
		}
	} else {
		font = new BraFont(stream, _braDosFullCharMap);
	}

	return font;
}

Font *AmigaDisk_br::createFont(const char *name, Common::SeekableReadStream &stream) {
	// TODO: implement AmigaLabelFont for labels
	return new AmigaFont(&stream);
}

GfxObj* DosDisk_br::createInventoryObjects(Common::SeekableReadStream &stream) {
	Frames *frames = new BraInventoryObjects(stream);
	return new GfxObj(0, frames, "inventoryobjects");
}


void Parallaction_ns::initFonts() {
	if (getPlatform() == Common::kPlatformDOS) {
		_dialogueFont = _disk->loadFont("comic");
		_labelFont = _disk->loadFont("topaz");
		_menuFont = _disk->loadFont("slide");
		_introFont = _disk->loadFont("slide");
	} else {
		_dialogueFont = _disk->loadFont("comic");
		_labelFont = new AmigaFont();
		_menuFont = _disk->loadFont("slide");
		_introFont = _disk->loadFont("intro");
	}
}

void Parallaction_br::initFonts() {
	if (getPlatform() == Common::kPlatformDOS) {
		_menuFont = _disk->loadFont("russia");
		_dialogueFont = _disk->loadFont("comic");
		_labelFont = _menuFont;
	} else {
		// TODO: Where is vanya used?
		// fonts/vanya/16

		_menuFont = _disk->loadFont("sonya");
		_dialogueFont = _disk->loadFont("natasha");
		_labelFont = _menuFont;
	}
}

} // End of namespace Parallaction
