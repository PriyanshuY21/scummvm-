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

#ifndef MYST_SCRIPTS_DNI_H
#define MYST_SCRIPTS_DNI_H

#include "common/scummsys.h"
#include "common/util.h"
#include "mohawk/myst_scripts.h"

namespace Mohawk {

struct MystScriptEntry;

namespace MystStacks {

#define DECLARE_OPCODE(x) void x(uint16 var, const ArgumentsArray &args)

class Dni : public MystScriptParser {
public:
	explicit Dni(MohawkEngine_Myst *vm);
	~Dni() override;

	void disablePersistentScripts() override;
	void runPersistentScripts() override;

private:
	void setupOpcodes();
	uint16 getVar(uint16 var) override;

	void atrus_run();
	void loopVideo_run();
	void atrusLeft_run();

	DECLARE_OPCODE(o_handPage);

	DECLARE_OPCODE(o_atrus_init);

	bool _atrusRunning;
	bool _notSeenAtrus; // 56
	uint32 _atrusLeftTime; // 60

	Common::String _video; // 64
	Common::Point _videoPos;

	bool _waitForLoop;
	uint32 _loopStart; // 72
	uint32 _loopEnd; // 76
	bool _atrusLeft; // 80
};

} // End of namespace MystStacks
} // End of namespace Mohawk

#undef DECLARE_OPCODE

#endif