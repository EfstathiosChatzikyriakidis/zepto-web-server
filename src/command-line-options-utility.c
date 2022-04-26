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

#include <stdlib.h>
#include <getopt.h>

#include "memory-management-helper-macros.h"
#include "information-validation-utility.h"
#include "command-line-options-utility.h"
#include "standard-wrapped-utilities.h"
#include "usage-information-utility.h"

/*
 * variables.
 */

static options_t options =
{
  .server_address = NULL,
  .server_port = NULL,
  .server_modules_path = NULL,
  .server_worker_requests = 1,
  .server_workers = 1
};

/*
 * functions.
 */

void
parse_command_line_options (const int argc, const string_t const argv [])
{
  // short options.
  const string_t const short_options = "a:p:w:r:m:";

  // long options.
  const struct option long_options [] =
  {
    { "address"  , 1, NULL, 'a' },
    { "port"     , 1, NULL, 'p' },
    { "workers"  , 1, NULL, 'w' },
    { "requests" , 1, NULL, 'r' },
    { "modules"  , 1, NULL, 'm' },
    { "version"  , 0, NULL, 'v' },
    { "help"     , 0, NULL, 'h' },
    { NULL       , 0, NULL, 0 }
  };

  // next option in command line.
  int next_option;

  // start scanning.
  do
  {
    // get next option.
    next_option = getopt_long (argc, argv, short_options, long_options, NULL);

    switch (next_option)
    {
      // print help and exit.
      case 'h':
        print_help (stdout, EXIT_SUCCESS);
        break;

      // print version and exit.
      case 'v':
        print_version (stdout, EXIT_SUCCESS);
        break;

      // server address.
      case 'a':
        {
          options.server_address = estrdup (optarg);
        }
        break;

      // server port.
      case 'p':
        {
          unsigned short int value;

          if (!parse_unsigned_short_int_number (optarg, &value))
          {
            print_help (stderr, EXIT_FAILURE);
          }

          options.server_port = estrdup (optarg);
        }
        break;

      // server modules path.
      case 'm':
        {
          if (!validate_directory_path_as_accessible (optarg))
          {
            print_help (stderr, EXIT_FAILURE);
          }

          options.server_modules_path = estrdup (optarg);
        }
        break;

      // server workers.
      case 'w':
        {
          if (!parse_unsigned_char_number (optarg, &options.server_workers) || options.server_workers < 1)
          {
            print_help (stderr, EXIT_FAILURE);
          }
        }
        break;

      // server worker requests.
      case 'r':
        {
          if (!parse_unsigned_short_int_number (optarg, &options.server_worker_requests) || options.server_worker_requests < 1)
          {
            print_help (stderr, EXIT_FAILURE);
          }
        }
        break;

      // unknown option.
      case '?':
        print_help (stderr, EXIT_FAILURE);
        break;

      // eop.
      case -1:
        break;

      default:
        abort ();
    }
  }
  while (next_option != -1);

  // the server modules path option is necessary.
  if (!options.server_modules_path)
  {
    print_help (stderr, EXIT_FAILURE);
  }

  // the program does not take extra arguments.
  if (optind != argc)
  {
    print_help (stderr, EXIT_FAILURE);
  }
}

const options_t * const
get_command_line_options (void)
{
  return &options;
}

void
clear_command_line_options (void)
{
  safe_free(options.server_modules_path);
  safe_free(options.server_address);
  safe_free(options.server_port);
}
