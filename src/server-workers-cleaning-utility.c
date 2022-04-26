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

#include <sys/wait.h>

#include "interruption-wrapper-helper-macros.h"
#include "server-workers-cleaning-utility.h"
#include "logging-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_kill_server_service_workers_message = N_("Failed to kill the service workers of the server.");

/*
 * functions.
 */

bool_t
clean_server_workers (void)
{
  if (kill (0, SIGQUIT) < 0)
  {
    log_error (_(failed_to_kill_server_service_workers_message));

    return false;
  }

  while (HANDLE_EINTR(wait (NULL)) > 0) ;

  return true;
}
