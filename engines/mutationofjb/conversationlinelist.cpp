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

#include "mutationofjb/conversationlinelist.h"
#include "mutationofjb/encryptedfile.h"
#include "mutationofjb/util.h"

namespace MutationOfJB {

ConversationLineList::ConversationLineList(const Common::Path &fileName) {
	parseFile(fileName);
}

const ConversationLineList::Line *ConversationLineList::getLine(uint index) const {
	if (index > _lines.size()) {
		return nullptr;
	}

	return &_lines[index - 1];
}

bool ConversationLineList::parseFile(const Common::Path &fileName) {
	EncryptedFile file;
	file.open(fileName);
	if (!file.isOpen()) {
		reportFileMissingError(fileName.toString(Common::Path::kNativeSeparator).c_str());
		return false;
	}

	while (!file.eos()) {
		Common::String lineStr = file.readLine();
		if (lineStr.empty()) {
			continue;
		}

		Line line;

		Common::String::iterator endIt = Common::find(lineStr.begin(), lineStr.end(), '|');
		if (endIt != lineStr.end()) {
			endIt++;
			if (endIt != lineStr.end() && *endIt == 'X') {
				line._extra = Common::String(endIt + 1, lineStr.end()); // Skip 'X' char.
			}
		}

		Common::String::iterator startSpeechIt = lineStr.begin();
		Common::String::iterator endSpeechIt = startSpeechIt;

		while (startSpeechIt < endIt) {
			endSpeechIt = Common::find(startSpeechIt, endIt, '\\');
			Common::String::iterator voiceFileIt = Common::find(startSpeechIt, endSpeechIt, '<');
			Speech speech;

			if (voiceFileIt != endSpeechIt) {
				if (*voiceFileIt == 'S') {
					speech._voiceFile = Common::String(voiceFileIt + 1, endSpeechIt);
				}
			}

			speech._text = Common::String(startSpeechIt, voiceFileIt);
			line._speeches.push_back(speech);

			startSpeechIt = endSpeechIt + 1;
		}

		_lines.push_back(line);
	}

	return true;
}

}
