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

#ifndef _COMMAND_LINE_OPTIONS_UTILITY_H_
#define _COMMAND_LINE_OPTIONS_UTILITY_H_

#include "command-line-options-types.h"

/*
 * function prototypes.
 */

void parse_command_line_options (const int argc, const string_t const argv []);

void clear_command_line_options (void);

const options_t * const get_command_line_options (void);

#endif // _COMMAND_LINE_OPTIONS_UTILITY_H_
