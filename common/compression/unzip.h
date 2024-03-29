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

#ifndef COMMON_UNZIP_H
#define COMMON_UNZIP_H

#include "common/str.h"

namespace Common {

/**
 * @defgroup common_unzip ZIP decompressor
 * @ingroup common
 *
 * @brief API related to ZIP archive files.
 *
 * @{
 */

class Archive;
class FSNode;
class SeekableReadStream;

/**
 * This factory method creates an Archive instance corresponding to the content
 * of the ZIP compressed file with the given name.
 *
 * May return 0 in case of a failure.
 */
Archive *makeZipArchive(const Path &name, bool flattenTree = false);

/**
 * This factory method creates an Archive instance corresponding to the content
 * of the ZIP compressed file with the given name.
 *
 * May return 0 in case of a failure.
 */
Archive *makeZipArchive(const FSNode &node, bool flattenTree = false);

/**
 * This factory method creates an Archive instance corresponding to the content
 * of the given ZIP compressed datastream.
 * This takes ownership of the stream,  in particular, it is deleted when the
 * ZipArchive is deleted.
 *
 * May return 0 in case of a failure. In this case stream will still be deleted.
 */
Archive *makeZipArchive(SeekableReadStream *stream, bool flattenTree = false);

/** @} */

} // End of namespace Common

#endif
