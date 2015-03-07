/*
 *  Copyright (C) 2014  Efstathios Chatzikyriakidis (contact@efxa.org).
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PREFORKING_SERVER_UTILITY_H_
#define _PREFORKING_SERVER_UTILITY_H_

#include "shared-types.h"

/*
 * function prototypes.
 */

bool_t create_preforking_server (const unsigned char server_workers,
                                 const unsigned short int server_worker_requests,
                                 const int server_socket_descriptor);

#endif // _PREFORKING_SERVER_UTILITY_H_
