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

#include "server-signals-support-utility.h"
#include "server-signal-handlers-utility.h"
#include "signal-dispatcher-utility.h"

/*
 * variables.
 */

static const signal_configuration_t signals_table [] =
{
  // ignored signals.

  { SIGTSTP, true, SA_RESTART, NULL },
  { SIGINT,  true, SA_RESTART, NULL },
  { SIGTTOU, true, SA_RESTART, NULL },
  { SIGTTIN, true, SA_RESTART, NULL },
  { SIGHUP,  true, SA_RESTART, NULL },
  { SIGQUIT, true, SA_RESTART, NULL },
  { SIGPIPE, true, SA_RESTART, NULL },

  // non-ignored signals.

  { SIGTERM, false, SA_RESTART, server_signal_term_handler },
  { SIGCHLD, false, SA_RESTART | SA_NOCLDSTOP, server_signal_child_handler },

  // end of signals configuration.

  { -1, true, 0, NULL }
};

/*
 * functions.
 */

bool_t
setup_server_signals_support (void)
{
  set_signals_configuration (signals_table);

  return setup_signals_support ();
}
