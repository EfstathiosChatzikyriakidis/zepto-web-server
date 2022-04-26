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

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>

#include "information-validation-utility.h"

/*
 * functions.
 */

bool_t
validate_directory_path_as_accessible (const string_t const directory_path)
{
  if (access (directory_path, F_OK) != 0)
  {
    return false;
  }

  if (access (directory_path, R_OK | X_OK) != 0)
  {
    return false;
  }

  struct stat directory_info;

  if (stat (directory_path, &directory_info) != 0 || !S_ISDIR (directory_info.st_mode))
  {
    return false;
  }

  return true;
}

bool_t
parse_unsigned_long_long_number (const string_t const number_to_parse,
                                 const unsigned long long minimum,
                                 const unsigned long long maximum,
                                 unsigned long long * const returned_number)
{
  const int preserve_errno = errno;

  string_t end;

  errno = 0;

  static const int decimal_base = 10;

  const unsigned long long number = strtoull (number_to_parse, &end, decimal_base);

  bool_t success = false;

  if (!errno && !strlen (end) && end != number_to_parse && minimum <= number && number <= maximum)
  {
    *returned_number = number;

    success = true;
  }

  errno = preserve_errno;

  return success;
}

bool_t
parse_unsigned_char_number (const string_t const number_to_parse, unsigned char * const returned_number)
{
  unsigned long long number;

  if (parse_unsigned_long_long_number (number_to_parse, 0, UCHAR_MAX, &number))
  {
    *returned_number = (unsigned char) number;

    return true;
  }

  return false;
}

bool_t
parse_unsigned_short_int_number (const string_t const number_to_parse, unsigned short int * const returned_number)
{
  unsigned long long number;

  if (parse_unsigned_long_long_number (number_to_parse, 0, USHRT_MAX, &number))
  {
    *returned_number = (unsigned short int) number;

    return true;
  }

  return false;
}
