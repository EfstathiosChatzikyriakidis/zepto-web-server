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

#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "server-worker-signals-support-utility.h"
#include "interruption-wrapper-helper-macros.h"
#include "server-worker-helper-utilities.h"
#include "server-worker-utility.h"
#include "logging-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_setup_server_service_worker_signals_support_message = N_("Failed to setup the signals support for a service worker of the server.");

static const string_t const failed_to_close_client_socket_descriptor_message = N_("Failed to close the client socket descriptor.");

/*
 * variables.
 */

static const unsigned int server_worker_idle_time_in_microseconds = 100000;

static unsigned short int current_number_of_server_worker_requests = 0;

volatile sig_atomic_t server_worker_keep_running = true;

/*
 * functions.
 */

pid_t
create_preforked_worker (const unsigned short int server_worker_requests, const int server_socket_descriptor)
{
  const pid_t pid = HANDLE_EAGAIN(fork ());

  if (pid != 0)
  {
    return pid;
  }

  if (!setup_server_worker_signals_support ())
  {
    log_error (_(failed_to_setup_server_service_worker_signals_support_message));

    _exit (EXIT_FAILURE);
  }

  while (server_worker_keep_running && current_number_of_server_worker_requests < server_worker_requests)
  {
    const int client_socket_descriptor = HANDLE_EINTR(accept (server_socket_descriptor, NULL, NULL));

    if (client_socket_descriptor < 0)
    {
      HANDLE_EINTR(usleep(server_worker_idle_time_in_microseconds));

      continue;
    }

    ++current_number_of_server_worker_requests;

    handle_accepted_client (client_socket_descriptor);

    if (close (client_socket_descriptor) < 0)
    {
      log_error (_(failed_to_close_client_socket_descriptor_message));

      _exit (EXIT_FAILURE);
    }
  }

  _exit (EXIT_SUCCESS);
}
