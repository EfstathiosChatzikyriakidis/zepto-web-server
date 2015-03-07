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

#include <string.h>
#include <stdlib.h>

#include "memory-management-helper-macros.h"
#include "dynamic-string-helper-utility.h"

/*
 * function prototypes.
 */

static bool_t dynamic_string_extend (dynamic_string_t * const dynamic_string, const size_t extra_buffer_length);

static unsigned int get_next_power_of_buffer_length (unsigned int current_buffer_length);

/*
 * functions.
 */

dynamic_string_t * const
dynamic_string_create (size_t buffer_length)
{
  static const size_t initial_buffer_length = 32;

  if (buffer_length < 0)
  {
    buffer_length = initial_buffer_length;
  }

  dynamic_string_t * dynamic_string = (dynamic_string_t *) calloc (1, sizeof (dynamic_string_t));

  if (!dynamic_string)
  {
    return NULL;
  }

  dynamic_string->string = NULL;

  dynamic_string->string_length = 0;

  dynamic_string->buffer_length = buffer_length;

  if (dynamic_string->buffer_length > 0)
  {
    dynamic_string->string = (string_t) malloc (dynamic_string->buffer_length);

    if (!dynamic_string->string)
    {
      safe_free (dynamic_string);

      return NULL;
    }
  }

  return dynamic_string;
}

void
dynamic_string_clear (dynamic_string_t * dynamic_string)
{
  if (dynamic_string)
  {
    safe_free(dynamic_string->string);
  }

  safe_free(dynamic_string);
}

size_t
dynamic_string_length (const dynamic_string_t * const dynamic_string)
{
  return dynamic_string->string_length;
}

bool_t
dynamic_string_append (dynamic_string_t * const dynamic_string, const string_t const string)
{
  const size_t string_length = strlen (string);

  if (!dynamic_string_extend (dynamic_string, string_length + 1))
  {
    return false;
  }

  memcpy (&dynamic_string->string[dynamic_string->string_length], string, string_length);

  dynamic_string->string_length += string_length;

  dynamic_string->string[dynamic_string->string_length] = '\0';

  return true;
}

static bool_t
dynamic_string_extend (dynamic_string_t * const dynamic_string, const size_t extra_buffer_length)
{
  const size_t total_buffer_length = dynamic_string->string_length + extra_buffer_length;

  if (total_buffer_length <= dynamic_string->buffer_length)
  {
    return true;
  }

  const unsigned int next_power_of_buffer_length = get_next_power_of_buffer_length (total_buffer_length);

  const string_t const string = (string_t) realloc (dynamic_string->string, next_power_of_buffer_length);

  if (!string)
  {
    return false;
  }

  dynamic_string->buffer_length = next_power_of_buffer_length;

  dynamic_string->string = string;

  return true;
}

static unsigned int
get_next_power_of_buffer_length (unsigned int current_buffer_length)
{
  --current_buffer_length;

  current_buffer_length |= current_buffer_length >> 0x01;
  current_buffer_length |= current_buffer_length >> 0x02;
  current_buffer_length |= current_buffer_length >> 0x04;
  current_buffer_length |= current_buffer_length >> 0x08;
  current_buffer_length |= current_buffer_length >> 0x10;

  return ++current_buffer_length;
}
