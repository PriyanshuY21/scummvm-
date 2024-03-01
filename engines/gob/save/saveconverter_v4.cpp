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

#include "common/endian.h"
#include "common/savefile.h"

#include "gob/gob.h"
#include "gob/save/saveconverter.h"
#include "gob/save/savefile.h"
#include "gob/save/savehandler.h"

namespace Gob {

SaveConverter_v4::SaveConverter_v4(GobEngine *vm, const Common::String &fileName) :
	SaveConverter(vm, fileName) {
}

SaveConverter_v4::~SaveConverter_v4() {
}

int SaveConverter_v4::isOldSave(Common::InSaveFile **save) const {
	uint32 varSize = SaveHandler::getVarSize(_vm);
	if (varSize == 0)
		return 0;

	uint32 saveSize = getActualSize(save);
	if (saveSize == 0)
		return 0;

	// The size of the old save always follows that rule
	if (saveSize == (varSize * 2 + kSlotNameLength + 1000 + 512000))
		return 1;

	// Not an old save, clean up
	if (save) {
		delete *save;
		*save = nullptr;
	}

	return 0;
}

char *SaveConverter_v4::getDescription(Common::SeekableReadStream &save) const {
	// The description starts at 1000
	if (!save.seek(1000))
		return nullptr;

	char *desc = new char[kSlotNameLength];

	// Read the description
	if (save.read(desc, kSlotNameLength) != kSlotNameLength) {
		delete[] desc;
		return nullptr;
	}

	return desc;
}

bool SaveConverter_v4::loadFail(SavePartInfo *info, SavePartVars *vars,
		SavePartMem *props, Common::InSaveFile *save) {

	delete info;
	delete vars;
	delete props;
	delete save;

	clear();

	return false;
}

// Loads the old save by constructing a new save containing the old save's data
bool SaveConverter_v4::load() {
	clear();

	uint32 varSize = SaveHandler::getVarSize(_vm);
	if (varSize == 0)
		return false;

	Common::InSaveFile *save;

	// Test if it's an old savd
	if (!isOldSave(&save) || !save)
		return false;

	displayWarning();

	SaveWriter writer(3, 0);

	SavePartInfo *info = readInfo(*save, kSlotNameLength, false);
	if (!info)
		return loadFail(nullptr, nullptr, nullptr, save);

	SavePartVars *vars = readVars(*save, varSize, true);
	if (!vars)
		return loadFail(info, nullptr, nullptr, save);

	SavePartMem *props = readMem(*save, 256000, true);
	if (!props)
		return loadFail(info, vars, nullptr, save);

	// We don't need the save anymore
	delete save;

	// Write all parts
	if (!writer.writePart(0, info))
		return loadFail(info, vars, props, nullptr);
	if (!writer.writePart(1, vars))
		return loadFail(info, vars, props, nullptr);
	if (!writer.writePart(2, props))
		return loadFail(info, vars, props, nullptr);

	// We don't need those anymore
	delete info;
	delete vars;
	delete props;

	// Create the final read stream
	if (!createStream(writer))
		return loadFail(nullptr, nullptr, nullptr, nullptr);

	return true;
}

} // End of namespace Gob
