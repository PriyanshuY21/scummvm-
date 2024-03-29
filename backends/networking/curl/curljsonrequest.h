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

#ifndef BACKENDS_NETWORKING_CURL_CURLJSONREQUEST_H
#define BACKENDS_NETWORKING_CURL_CURLJSONREQUEST_H

#include "backends/networking/curl/curlrequest.h"
#include "common/memstream.h"
#include "common/formats/json.h"

namespace Networking {

typedef Response<const Common::JSONValue *> JsonResponse;
typedef Common::BaseCallback<const JsonResponse &> *JsonCallback;
typedef Common::BaseCallback<const Common::JSONValue *> *JSONValueCallback;

#define CURL_JSON_REQUEST_BUFFER_SIZE 512 * 1024

class CurlJsonRequest: public CurlRequest {
protected:
	JsonCallback _jsonCallback;
	Common::MemoryWriteStreamDynamic _contentsStream;
	byte *_buffer;

	/** Sets FINISHED state and passes the JSONValue * into user's callback in JsonResponse. */
	virtual void finishJson(const Common::JSONValue *json);

public:
	CurlJsonRequest(JsonCallback cb, ErrorCallback ecb, const Common::String &url);
	~CurlJsonRequest() override;

	void handle() override;
	void restart() override;

	static bool jsonIsObject(const Common::JSONValue *item, const char *warningPrefix);
	static bool jsonContainsObject(const Common::JSONObject &item, const char *key, const char *warningPrefix, bool isOptional = false);
	static bool jsonContainsString(const Common::JSONObject &item, const char *key, const char *warningPrefix, bool isOptional = false);
	static bool jsonContainsIntegerNumber(const Common::JSONObject &item, const char *key, const char *warningPrefix, bool isOptional = false);
	static bool jsonContainsArray(const Common::JSONObject &item, const char *key, const char *warningPrefix, bool isOptional = false);
	static bool jsonContainsStringOrIntegerNumber(const Common::JSONObject &item, const char *key, const char *warningPrefix, bool isOptional = false);
	static bool jsonContainsAttribute(const Common::JSONObject &item, const char *key, const char *warningPrefix, bool isOptional = false);
};

} // End of namespace Networking

#endif
