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

#include "command-line-options-utility.h"
#include "program-information-utility.h"
#include "daemonize-utility.h"
#include "logging-utility.h"
#include "server-utility.h"
#include "i18n-utility.h"
#include "file-utility.h"

/*
 * variables.
 */

static const program_information_t program_information =
{
  .name = "zws",
  .version = "1.0",
  .email = "stathis.chatzikyriakidis@gmail.com",
  .working_directory_path = "/",
  .pid_file_path = "/var/run/zws.pid"
};

/*
 * functions.
 */

int
main (int argc, const string_t const argv [])
{
  set_program_information (&program_information);

  open_logging_for_daemon (program_information.name);

  setup_i18n_support (program_information.name);

  parse_command_line_options (argc, argv);

  const bool_t daemon_success = daemonize (program_information.working_directory_path, program_information.pid_file_path);

  bool_t server_success = true;

  if (daemon_success)
  {
    server_success = server_run ();
  }

  remove_file (program_information.pid_file_path);

  clear_command_line_options ();

  close_logging ();

  exit (daemon_success && server_success ? EXIT_SUCCESS : EXIT_FAILURE);
}
