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

#ifndef _PID_FILE_UTILITY_H_
#define _PID_FILE_UTILITY_H_

#include <sys/types.h>

#include "shared-types.h"

/*
 * function prototypes.
 */

pid_t read_pid_from_file (const string_t const file_path);

bool_t write_pid_to_file (const string_t const file_path, const pid_t pid);

bool_t pid_exists (const pid_t pid);

#endif // _PID_FILE_UTILITY_H_
