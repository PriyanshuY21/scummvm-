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

#ifndef NUVIE_MISC_CALLBACK_H
#define NUVIE_MISC_CALLBACK_H

#include "ultima/nuvie/core/nuvie_defs.h"

namespace Ultima {
namespace Nuvie {

class CallBack;

// general messages
typedef enum {
	CB_TIMED,                /* timer fired (data=uint32:time) */

	ANIM_CB_DONE,            /* animation has finished */
	ANIM_CB_HIT,             /* animation hit a MapEntity (data=MapEntity) */
	ANIM_CB_HIT_WORLD,       /* animation hit some other tile on the map (data=MapCoord) */

	EFFECT_CB_COMPLETE,      /* effect has finished */

	CB_DATA_READY,           /* some data is ready to be retrieved (data=char)*/
	MSGSCROLL_CB_TEXT_READY, /* text is ready to be retrieved (data=Std::string)*/
	CB_INPUT_CANCELED        /* input canceled by user */
} CallbackMessage;


/* Classes inheriting this can send & receive callback messages.
 */
class CallBack {
protected:
	char *callback_user_data; // data set by Caller
	CallBack *callback_target; // Caller: default CallBack that message() sends to

public:
	CallBack()  {
		callback_user_data = nullptr;
		callback_target = nullptr;
	}
	virtual ~CallBack() { }

	// receive message
	virtual uint16 callback(uint16 msg, CallBack *caller, void *data = nullptr) {
		DEBUG(0, LEVEL_WARNING, "Unhandled callback. msg (%x)\n", msg);
		return 0;
	}
	// send message
	uint16 message(uint16 msg, void *msg_data = nullptr, void *my_data = nullptr) {
		if (my_data)
			set_user_data(my_data);
		callback_target->set_user_data(callback_user_data);

		return (callback_target->callback(msg, this, msg_data));
	}

	void set_user_data(void *user_data) {
		callback_user_data = (char *)user_data;
	}
	void set_target(CallBack *t) {
		callback_target = t;
	}
};

} // End of namespace Nuvie
} // End of namespace Ultima

#endif
