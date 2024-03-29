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

#ifndef GLK_COMPREHEND_COMPREHEND_H
#define GLK_COMPREHEND_COMPREHEND_H

#include "common/scummsys.h"
#include "glk/comprehend/game.h"
#include "glk/glk_api.h"
#include "glk/window_graphics.h"
#include "glk/window_text_buffer.h"
#include "glk/window_text_grid.h"

namespace Glk {
namespace Comprehend {

class DrawSurface;
class Pics;

#define EXTRA_STRING_TABLE(x) (0x8200 | (x))

struct GameStrings {
	uint16 game_restart;
};

/**
 * Comprehend engine
 */
class Comprehend : public GlkAPI {
private:
	int _saveSlot; ///< Save slot when loading savegame from launcher
	bool _graphicsEnabled;
	bool _disableSaves;
public:
	GraphicsWindow *_topWindow;
	TextGridWindow *_roomDescWindow;
	TextBufferWindow *_bottomWindow;
	DrawSurface *_drawSurface;
	ComprehendGame *_game;
	Pics *_pics;
	uint _drawFlags;

private:
	/**
	 * Initialization code
	 */
	void initialize();

	/**
	 * Deinitialization
	 */
	void deinitialize();

	/**
	 * Create the debugger
	 */
	void createDebugger() override;

	/**
	 * Creates the appropriate game class
	 */
	void createGame();

protected:
	/**
	 * Loads the configuration
	 */
	void createConfiguration() override;
public:
	/**
	 * Constructor
	 */
	Comprehend(OSystem *syst, const GlkGameDescription &gameDesc);

	~Comprehend() override;

	/**
	 * Returns the running interpreter type
	 */
	InterpreterType getInterpreterType() const override {
		return INTERPRETER_SCOTT;
	}

	/**
	 * Initialize the graphics
	 */
	void initGraphicsMode() override;

	/**
	 * Execute the game
	 */
	void runGame() override;

	/**
	 * Handles loading a savegame selected from the launcher
	 */
	bool loadLauncherSavegameIfNeeded();

	/**
	 * Load a savegame from the passed Quetzal file chunk stream
	 */
	Common::Error readSaveData(Common::SeekableReadStream *rs) override;

	/**
	 * Save the game. The passed write stream represents access to the UMem chunk
	 * in the Quetzal save file that will be created
	 */
	Common::Error writeGameData(Common::WriteStream *ws) override;

	/**
	 * Print string to the buffer window
	 */
	void print(const char *fmt, ...);

	/**
	 * Print unicode-string to the buffer window
	 */
	template<class... TParam>
	void print(const Common::U32String &fmt, TParam... param);

	/**
	 * Prints the room description in the room description window
	 */
	void printRoomDesc(const Common::String &desc);

	/**
	 * Read an input line
	 */
	void readLine(char *buffer, size_t maxLen);

	/**
	 * Read in a character
	 */
	int readChar();

	/**
	 * Draw a picture
	 */
	void drawPicture(uint pictureNum);

	/**
	 * Draw a location image
	 */
	void drawLocationPicture(int pictureNum, bool clearBg = true);

	/**
	 * Draw an item image
	 */
	void drawItemPicture(int pictureNum);

	/**
	 * Clear the picture area
	 */
	void clearScreen(bool isBright);

	/**
	 * Toggles whether the picture window is visible
	 */
	bool toggleGraphics();

	/**
	 * Ensures the picture window is visible
	 */
	void showGraphics();

	/**
	 * Returns true if the graphics area is visible
	 */
	bool isGraphicsEnabled() const {
		return _graphicsEnabled;
	}

	ComprehendGame *getGame() const {
		return _game;
	}

	/**
	 * Returns true if a savegame can be loaded
	 */
	bool canLoadGameStateCurrently(Common::U32String *msg = nullptr) override {
		return !_disableSaves && GlkAPI::canLoadGameStateCurrently();
	}

	/**
	 * Returns true if the game can be saved
	 */
	bool canSaveGameStateCurrently(Common::U32String *msg = nullptr) override {
		return !_disableSaves && GlkAPI::canSaveGameStateCurrently();
	}

	/**
	 * Set whether saving and loading is currently available
	 */
	void setDisableSaves(bool flag) {
		_disableSaves = flag;
	}

	/**
	 * Returns true if an input line is currently active
	 */
	bool isInputLineActive() const;

private:
	void print_u32_internal(const Common::U32String *fmt, ...);
};

template<class... TParam>
void Comprehend::print(const Common::U32String &fmt, TParam... param) {
	print_u32_internal(&fmt, Common::forward<TParam>(param)...);
}

extern Comprehend *g_comprehend;

} // End of namespace Comprehend
} // End of namespace Glk

#endif
