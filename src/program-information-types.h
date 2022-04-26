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

#ifndef _PROGRAM_INFORMATION_TYPES_H_
#define _PROGRAM_INFORMATION_TYPES_H_

#include "shared-types.h"

/*
 * type definitions.
 */

// program information type definition.
typedef struct program_information_t
{
  // the program name.
  string_t name;

  // the program version.
  string_t version;

  // the program email.
  string_t email;

  // the program working directory path.
  string_t working_directory_path;

  // the program pid file path.
  string_t pid_file_path;
} program_information_t;

#endif // _PROGRAM_INFORMATION_TYPES_H_
