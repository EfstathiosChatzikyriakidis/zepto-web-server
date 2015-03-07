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

#ifndef _DYNAMIC_STRING_HELPER_UTILITY_H_
#define _DYNAMIC_STRING_HELPER_UTILITY_H_

#include <stddef.h>

#include "dynamic-string-helper-types.h"

dynamic_string_t * const dynamic_string_create (size_t buffer_length);

void dynamic_string_clear (dynamic_string_t * dynamic_string);

bool_t dynamic_string_append (dynamic_string_t * const dynamic_string, const string_t const string);

size_t dynamic_string_length (const dynamic_string_t * const dynamic_string);

#endif // _DYNAMIC_STRING_HELPER_UTILITY_H_
