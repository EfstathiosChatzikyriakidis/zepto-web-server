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
#include "server-signal-handlers-utility.h"
#include "shared-types.h"

/*
 * variables.
 */

extern volatile sig_atomic_t server_keep_running;

extern volatile sig_atomic_t current_number_of_server_workers;

/*
 * functions.
 */

void
server_signal_term_handler (void)
{
  server_keep_running = false;
}

void
server_signal_child_handler (void)
{
  while (HANDLE_EINTR(waitpid (WAIT_ANY, NULL, WNOHANG)) > 0)
  {
    --current_number_of_server_workers;
  }
}
