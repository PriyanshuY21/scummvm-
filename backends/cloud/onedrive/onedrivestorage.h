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

#ifndef BACKENDS_CLOUD_ONEDRIVE_ONEDRIVESTORAGE_H
#define BACKENDS_CLOUD_ONEDRIVE_ONEDRIVESTORAGE_H

#include "backends/cloud/basestorage.h"
#include "backends/networking/curl/curljsonrequest.h"

namespace Cloud {
namespace OneDrive {

class OneDriveStorage: public Cloud::BaseStorage {
	/** This private constructor is called from loadFromConfig(). */
	OneDriveStorage(const Common::String &token, const Common::String &refreshToken, bool enabled);

	/** Constructs StorageInfo based on JSON response from cloud. */
	void infoInnerCallback(StorageInfoCallback outerCallback, const Networking::JsonResponse &json);

	void fileInfoCallback(Networking::NetworkReadStreamCallback outerCallback, const Networking::JsonResponse &response);

protected:
	/**
	 * @return "onedrive"
	 */
	Common::String cloudProvider() override;

	/**
	 * @return kStorageOneDriveId
	 */
	uint32 storageIndex() override;

	bool needsRefreshToken() override;

	bool canReuseRefreshToken() override;

public:
	/** This constructor uses OAuth code flow to get tokens. */
	OneDriveStorage(const Common::String &code, Networking::ErrorCallback cb);

	/** This constructor extracts tokens from JSON acquired via OAuth code flow. */
	OneDriveStorage(const Networking::JsonResponse &codeFlowJson, Networking::ErrorCallback cb);

	~OneDriveStorage() override;

	/**
	 * Storage methods, which are used by CloudManager to save
	 * storage in configuration file.
	 */

	/**
	 * Save storage data using ConfMan.
	 * @param keyPrefix all saved keys must start with this prefix.
	 * @note every Storage must write keyPrefix + "type" key
	 *       with common value (e.g. "Dropbox").
	 */
	void saveConfig(const Common::String &keyPrefix) override;

	/**
	* Return unique storage name.
	* @returns  some unique storage name (for example, "Dropbox (user@example.com)")
	*/
	Common::String name() const override;

	/** Public Cloud API comes down there. */

	/** Returns ListDirectoryStatus struct with list of files. */
	Networking::Request *listDirectory(const Common::String &path, ListDirectoryCallback callback, Networking::ErrorCallback errorCallback, bool recursive = false) override;

	/** Returns UploadStatus struct with info about uploaded file. */
	Networking::Request *upload(const Common::String &path, Common::SeekableReadStream *contents, UploadCallback callback, Networking::ErrorCallback errorCallback) override;

	/** Returns pointer to Networking::NetworkReadStream. */
	Networking::Request *streamFileById(const Common::String &path, Networking::NetworkReadStreamCallback callback, Networking::ErrorCallback errorCallback) override;

	/** Calls the callback when finished. */
	Networking::Request *createDirectory(const Common::String &path, BoolCallback callback, Networking::ErrorCallback errorCallback) override;

	/** Returns the StorageInfo struct. */
	Networking::Request *info(StorageInfoCallback callback, Networking::ErrorCallback errorCallback) override;

	/** Returns storage's saves directory path with the trailing slash. */
	Common::String savesDirectoryPath() override;

	/**
	 * Load token and user id from configs and return OneDriveStorage for those.
	 * @return pointer to the newly created OneDriveStorage or 0 if some problem occurred.
	 */
	static OneDriveStorage *loadFromConfig(const Common::String &keyPrefix);

	/**
	 * Remove all OneDriveStorage-related data from config.
	 */
	static void removeFromConfig(const Common::String &keyPrefix);

	Common::String accessToken() const { return _token; }
};

} // End of namespace OneDrive
} // End of namespace Cloud

#endif
