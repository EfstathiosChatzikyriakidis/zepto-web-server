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

#include <unistd.h>

#include "file-utility.h"

/*
 * functions.
 */

bool_t
remove_file (const string_t const file_path)
{
  return (unlink (file_path) ? false : true);
}

bool_t
file_exists (const string_t const file_path)
{
  return (access (file_path, F_OK) ? false : true);
}

bool_t
file_is_readable (const string_t const file_path)
{
  return (access (file_path, R_OK) ? false : true);
}
