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

#ifndef _DYNAMIC_STRING_HELPER_TYPES_H_
#define _DYNAMIC_STRING_HELPER_TYPES_H_

#include <stddef.h>

#include "shared-types.h"

/*
 * type definitions.
 */

// dynamic string type definition.
typedef struct dynamic_string_t
{
  string_t string;

  size_t string_length;

  size_t buffer_length;
} dynamic_string_t;

#endif // _DYNAMIC_STRING_HELPER_TYPES_H_
