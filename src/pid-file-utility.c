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

#include <errno.h>
#include <signal.h>
#include <stdio.h>

#include "pid-file-utility.h"

/*
 * functions.
 */

pid_t
read_pid_from_file (const string_t const file_path)
{
  const pid_t pid_error = -1;

  FILE * const file = fopen (file_path, "r");

  if (!file)
  {
    return pid_error;
  }

  pid_t pid = pid_error;

  fscanf (file, "%d", &pid);

  if (fclose(file) == EOF)
  {
    return pid_error;
  }

  return pid;
}

bool_t
write_pid_to_file (const string_t const file_path, const pid_t pid)
{
  FILE * const file = fopen (file_path, "w");

  if (!file)
  {
    return false;
  }

  fprintf (file, "%d\n", pid);

  if (fclose(file) == EOF)
  {
    return false;
  }

  return true;
}

bool_t
pid_exists (const pid_t pid)
{
  if (pid <= 0)
  {
    return false;
  }

  if (kill (pid, 0) < 0 && errno == ESRCH)
  {
    return false;
  }

  return true;
}
