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

#include <stdlib.h>

#include "program-information-utility.h"
#include "usage-information-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const usage_part_a_message = N_("Usage:");

static const string_t const usage_part_b_message = N_("[OPTIONS] -m PATH");

static const string_t const usage_part_c_message = N_(
  "  -a, --address=ADDRESS  The address of the server.                       \n"
  "  -p, --port=NUMBER      The port of the server.                          \n"
  "  -w, --workers=NUMBER   The number of the service workers of the server. \n"
  "  -r, --requests=NUMBER  The number of the requests per service worker.   \n"
  "  -m, --modules=PATH     The modules path of the server.                  \n"
  "                                                                          \n"
  "      --help             Display help and exit.                           \n"
  "      --version          Display version and exit.                        \n");

static const string_t const usage_part_d_message = N_("Report bugs to");

/*
 * functions.
 */

void
print_help (FILE * const stream, const int exit_code)
{
  const program_information_t * const program_information = get_program_information();

  fprintf (stream, "%s %s %s\n\n%s\n%s <%s>\n", _(usage_part_a_message),
                                                program_information->name,
                                                _(usage_part_b_message),
                                                _(usage_part_c_message),
                                                _(usage_part_d_message),
                                                program_information->email);

  exit (exit_code);
}

void
print_version (FILE * const stream, const int exit_code)
{
  const program_information_t * const program_information = get_program_information();

  fprintf (stream, "%s\n", program_information->version);

  exit (exit_code);
}
