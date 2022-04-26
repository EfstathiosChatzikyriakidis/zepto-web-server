/*
 *  Copyright (C) 2014  Efstathios Chatzikyriakidis (stathis.chatzikyriakidis@gmail.com).
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

#ifndef _SERVER_MODULE_UTILITY_H_
#define _SERVER_MODULE_UTILITY_H_

#include "server-module-types.h"

/*
 * function prototypes.
 */

server_module_t * const server_module_open (const string_t const server_module_file_path);

void server_module_clear (server_module_t * server_module);

const string_t const get_server_module_file_path (const string_t const server_modules_path, const string_t const server_module_name);

#endif // _SERVER_MODULE_UTILITY_H_
