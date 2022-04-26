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

#include <string.h>
#include <signal.h>
#include <errno.h>

#include "signal-dispatcher-utility.h"
#include "logging-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_initialize_all_signals_set_message = N_("Failed to initialize the set of all signals.");

static const string_t const failed_to_change_action_of_signal_message = N_("Failed to change the action of the signal:");

/*
 * variables.
 */

static const signal_configuration_t * internal_signals_table = NULL;

/*
 * function prototypes.
 */

static void signal_handler_dispatcher (const int signal);

/*
 * functions.
 */

bool_t
setup_signals_support (void)
{
  struct sigaction signal_action;

  memset (&signal_action, 0, sizeof (signal_action));

  if (sigfillset (&signal_action.sa_mask) < 0)
  {
    log_error (_(failed_to_initialize_all_signals_set_message));
    return false;
  }

  for (int i = 0; internal_signals_table[i].signal != -1; i++)
  {
    const signal_configuration_t configuration = internal_signals_table[i];

    signal_action.sa_flags = configuration.flags;

    signal_action.sa_handler = configuration.ignore ? SIG_IGN : signal_handler_dispatcher;

    if (sigaction (configuration.signal, &signal_action, NULL) < 0)
    {
      log_error ("%s '%s'.", _(failed_to_change_action_of_signal_message), strsignal (configuration.signal));
      return false;
    }
  }

  return true;
}

void
set_signals_configuration (const signal_configuration_t * const signals_table)
{
  internal_signals_table = signals_table;
}

static void
signal_handler_dispatcher (const int signal)
{
  const int preserve_errno = errno;

  for (int i = 0; internal_signals_table[i].signal != -1; i++)
  {
    const signal_configuration_t configuration = internal_signals_table[i];

    if (configuration.signal == signal)
    {
      if (configuration.handler)
      {
        configuration.handler ();
      }

      break;
    }
  }

  errno = preserve_errno;
}
