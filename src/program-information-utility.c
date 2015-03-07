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

#include <stddef.h>

#include "program-information-utility.h"

/*
 * variables.
 */

static const program_information_t * internal_program_information = NULL;

/*
 * functions.
 */

const program_information_t * const
get_program_information (void)
{
  return internal_program_information;
}

void
set_program_information (const program_information_t * const program_information)
{
  internal_program_information = program_information;
}
