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

#include "scummvm_file.h"
#include "common/config-manager.h"
#include "common/language.h"

namespace Lua {

LuaFileProxy *LuaFileProxy::create(const Common::String &filename, const Common::String &mode) {
	if (filename.contains("config.lua"))
		return new LuaFileConfig(filename, mode);

	return new LuaFileRead(Common::Path(filename, '/'), mode);
}

LuaFileConfig::LuaFileConfig(const Common::String &filename, const Common::String &mode) : _readPos(0) {
	assert(filename.contains("config.lua"));
	if (mode == "r")
		setupConfigFile();
}

Common::String LuaFileConfig::formatDouble(double value) {
	// This is a bit hackish. The point of it is that it's important that
	// we ignore the locale decimal mark and force it to be a point. If it
	// would happen to be a comma instead, it seems that it's seen as two
	// comma-separated integers rather than one floating-point value. Or
	// something like that.

	bool negative = value < 0.0;
	value = fabs(value);
	double integerPart = floor(value);
	double fractionalPart = (value - integerPart) * 1000000.0;

	return Common::String::format("%s%.0f.%.0f", negative ? "-" : "", integerPart, fractionalPart);
}

void LuaFileConfig::setupConfigFile() {
	double sfxVolume = !ConfMan.hasKey("sfx_volume") ? 1.0 : 1.0 * ConfMan.getInt("sfx_volume") / 255.0;
	double musicVolume = !ConfMan.hasKey("music_volume") ? 0.5 : 1.0 * ConfMan.getInt("music_volume") / 255.0;
	double speechVolume = !ConfMan.hasKey("speech_volume") ? 1.0 : 1.0 * ConfMan.getInt("speech_volume") / 255.0;
	bool subtitles = !ConfMan.hasKey("subtitles") ? true : ConfMan.getBool("subtitles");

	_readData = Common::String::format(
"GAME_LANGUAGE = \"%s\"\r\n\
GAME_SUBTITLES = %s\r\n\
MAX_MEMORY_USAGE = 256000000\r\n\
GFX_VSYNC_ACTIVE = true\r\n\
SFX_SAMPLING_RATE = 44100\r\n\
SFX_CHANNEL_COUNT = 32\r\n\
SFX_SOUND_VOLUME = %s\r\n\
SFX_MUSIC_VOLUME = %s\r\n\
SFX_SPEECH_VOLUME = %s\r\n",
		getLanguage().c_str(), subtitles ? "true" : "false",
		formatDouble(sfxVolume).c_str(),
		formatDouble(musicVolume).c_str(),
		formatDouble(speechVolume).c_str());

	_readPos = 0;
}

LuaFileConfig::~LuaFileConfig() {
	if (!_settings.empty())
		writeSettings();
}

size_t LuaFileConfig::read(void *ptr, size_t size, size_t count) {
	size_t bytesRead = MIN<size_t>(_readData.size() - _readPos, size * count);
	memmove(ptr, &_readData.c_str()[_readPos], bytesRead);
	_readPos += bytesRead;
	return bytesRead / size;
}

size_t LuaFileConfig::write(const char *ptr, size_t count) {
	// Loop through the provided line(s)
	while (*ptr) {
		if ((*ptr == '-') && (*(ptr + 1) == '-')) {
			// Comment line to skip over
			while ((*ptr != '\r') && (*ptr != '\n'))
				++ptr;
		} else {
			// Legitimate data
			const char *p = strchr(ptr, '\n');
			if (!p) p = ptr + strlen(ptr);
			while ((*p == '\r') || (*p == '\n'))
				++p;

			_settings += Common::String(ptr, p - ptr);
			ptr = p;
		}

		while ((*ptr == '\r') || (*ptr == '\n'))
			++ptr;
	}

	return count;
}

void LuaFileConfig::writeSettings() {
	// Loop through the setting lines
	const char *pSrc = _settings.c_str();
	while (*pSrc) {
		if ((*pSrc != '\r') && (*pSrc != '\n')) {
			const char *p = strchr(pSrc, '=');
			assert(p);

			// Get the setting name
			const char *pEnd = p - 1;
			while (*pEnd == ' ')
				--pEnd;
			Common::String settingName(pSrc, pEnd - pSrc + 1);

			// Get the setting value
			const char *pStart = p + 1;
			while (*pStart == ' ')
				++pStart;

			pEnd = pStart + 1;
			while ((*pEnd != '\r') && (*pEnd != '\n') && (*pEnd != '\0'))
				++pEnd;
			Common::String value(pStart + (*pStart == '"' ? 1 : 0), pEnd - pStart - (*pStart == '"' ? 2 : 0));

			// Update the setting
			updateSetting(settingName, value);
			pSrc = pEnd;
		}

		// Move to next line
		while ((*pSrc == '\r') || (*pSrc == '\n'))
			++pSrc;
	}

	ConfMan.flushToDisk();
}

void LuaFileConfig::updateSetting(const Common::String &setting, const Common::String &value) {
	if (setting == "GAME_LANGUAGE")
		setLanguage(value);
	else if (setting == "GAME_SUBTITLES")
		ConfMan.setBool("subtitles", value == "true");
	else if (setting == "SFX_SOUND_VOLUME") {
		double v = strtod(value.c_str(), NULL);
		ConfMan.setInt("sfx_volume", (int)(v * 255));
	} else if (setting == "SFX_MUSIC_VOLUME") {
		double v = strtod(value.c_str(), NULL);
		ConfMan.setInt("music_volume", (int)(v * 255));
	} else if (setting == "SFX_SPEECH_VOLUME") {
		double v = strtod(value.c_str(), NULL);
		ConfMan.setInt("speech_volume", (int)(v * 255));
	} else {
		// All other settings are ignored
	}
}

/**
 * Get the language code used by the game for each language it supports
 */
Common::String LuaFileConfig::getLanguage() {
	Common::Language lang = Common::parseLanguage(ConfMan.get("language"));
	switch (lang) {
	case Common::EN_ANY:
		return "en";
	case Common::DE_DEU:
		return "de";
	case Common::ES_ESP:
		return "es";
	case Common::FR_FRA:
		return "fr";
	case Common::HR_HRV:
		return "hr";
	case Common::HU_HUN:
		return "hu";
	case Common::IT_ITA:
		return "it";
	case Common::PL_POL:
		return "pl";
	case Common::PT_BRA:
		return "pt";
	case Common::RU_RUS:
		return "ru";
	case Common::HE_ISR:
		return "he";
	default:
		error("Unknown language '%s' encountered", ConfMan.get("language").c_str());
		break;
	}
}

/**
 * Set the language code fro the game
 */
void LuaFileConfig::setLanguage(const Common::String &lang) {
	if (lang == "en")
		ConfMan.set("language", Common::getLanguageCode(Common::EN_ANY));
	else if (lang == "de")
		ConfMan.set("language", Common::getLanguageCode(Common::DE_DEU));
	else if (lang == "es")
		ConfMan.set("language", Common::getLanguageCode(Common::ES_ESP));
	else if (lang == "fr")
		ConfMan.set("language", Common::getLanguageCode(Common::FR_FRA));
	else if (lang == "hr")
		ConfMan.set("language", Common::getLanguageCode(Common::HR_HRV));
	else if (lang == "hu")
		ConfMan.set("language", Common::getLanguageCode(Common::HU_HUN));
	else if (lang == "it")
		ConfMan.set("language", Common::getLanguageCode(Common::IT_ITA));
	else if (lang == "pl")
		ConfMan.set("language", Common::getLanguageCode(Common::PL_POL));
	else if (lang == "pt")
		ConfMan.set("language", Common::getLanguageCode(Common::PT_BRA));
	else if (lang == "ru")
		ConfMan.set("language", Common::getLanguageCode(Common::RU_RUS));
	else if (lang == "he")
		ConfMan.set("language", Common::getLanguageCode(Common::HE_ISR));
	else
		error("Unknown language encountered: %s", lang.c_str());
}


LuaFileRead::LuaFileRead(const Common::Path &filename, const Common::String &mode) {
	assert(mode == "r");
	if (!_file.open(filename))
		error("Could not open file %s", filename.toString().c_str());

	_size = _file.size();
}

bool LuaFileRead::eof() const {
	return _file.eos();
}

size_t LuaFileRead::read(void *ptr, size_t size, size_t count) {
	assert(size == 1);
	byte *dataPtr = (byte *)ptr;

	while (count > 0) {
		byte c = _file.readByte();
		if (_file.eos())
			break;
		if (c == '\r')
			continue;

		*dataPtr++ = c;
		--count;
	}

	return dataPtr - (byte *)ptr;
}

size_t LuaFileRead::write(const char *ptr, size_t count) {
	// Unsupported
	return 0;
}

} // End of namespace Lua
