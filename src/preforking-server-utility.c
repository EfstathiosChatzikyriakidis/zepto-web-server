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

#include <signal.h>
#include <unistd.h>

#include "server-workers-cleaning-utility.h"
#include "preforking-server-utility.h"
#include "server-worker-utility.h"
#include "logging-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_create_new_server_service_worker_message = N_("Failed to create a new service worker in the server.");

static const string_t const failed_to_clean_server_service_workers_message = N_("Failed to clean the service workers of the server.");

static const string_t const failed_to_initialize_blocked_signals_set_message = N_("Failed to initialize the set of the blocked signals.");

static const string_t const failed_to_add_sigchld_to_blocked_signals_set_message = N_("Failed to add the SIGCHLD signal in the set of the blocked signals.");

static const string_t const failed_to_enable_blocked_signals_set_message = N_("Failed to enable the set of the blocked signals.");

static const string_t const failed_to_disable_blocked_signals_set_message = N_("Failed to disable the set of the blocked signals.");

/*
 * variables.
 */

static const unsigned int server_idle_time_in_seconds = 1;

volatile sig_atomic_t server_keep_running = true;

volatile sig_atomic_t current_number_of_server_workers = 0;

/*
 * functions.
 */

bool_t
create_preforking_server (const unsigned char server_workers,
                          const unsigned short int server_worker_requests,
                          const int server_socket_descriptor)
{
  sigset_t blocked_signals_mask;

  if (sigemptyset (&blocked_signals_mask) < 0)
  {
    log_error (_(failed_to_initialize_blocked_signals_set_message));

    return false;
  }

  if (sigaddset (&blocked_signals_mask, SIGCHLD) < 0)
  {
    log_error (_(failed_to_add_sigchld_to_blocked_signals_set_message));

    return false;
  }

  while (server_keep_running)
  {
    sleep (server_idle_time_in_seconds);

    if (sigprocmask(SIG_BLOCK, &blocked_signals_mask, NULL) < 0)
    {
      log_error (_(failed_to_enable_blocked_signals_set_message));

      break;
    }

    while (current_number_of_server_workers < server_workers)
    {
      if (create_preforked_worker (server_worker_requests, server_socket_descriptor) < 0)
      {
        log_warning (_(failed_to_create_new_server_service_worker_message));

        continue; 
      }

      ++current_number_of_server_workers;
    }

    if (sigprocmask(SIG_UNBLOCK, &blocked_signals_mask, NULL) < 0)
    {
      log_error (_(failed_to_disable_blocked_signals_set_message));

      break;
    }
  }

  if (sigprocmask(SIG_BLOCK, &blocked_signals_mask, NULL) < 0)
  {
    log_error (_(failed_to_enable_blocked_signals_set_message));

    return false;
  }

  if (!clean_server_workers ())
  {
    log_error (_(failed_to_clean_server_service_workers_message));

    return false;
  }

  return true;
}
