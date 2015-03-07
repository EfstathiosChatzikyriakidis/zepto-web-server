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

#ifndef _INFORMATION_VALIDATION_UTILITY_H_
#define _INFORMATION_VALIDATION_UTILITY_H_

#include "shared-types.h"

/*
 * function prototypes.
 */

bool_t validate_directory_path_as_accessible (const string_t const directory_path);

bool_t parse_unsigned_char_number (const string_t const number_to_parse, unsigned char * const returned_number);

bool_t parse_unsigned_short_int_number (const string_t const number_to_parse, unsigned short int * const returned_number);

bool_t parse_unsigned_long_long_number (const string_t const number_to_parse,
                                        const unsigned long long minimum,
                                        const unsigned long long maximum,
                                        unsigned long long * const returned_number);

#endif // _INFORMATION_VALIDATION_UTILITY_H_
