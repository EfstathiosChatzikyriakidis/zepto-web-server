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

#include <netdb.h>
#include <stdlib.h>

#include "memory-management-helper-macros.h"
#include "server-helper-utilities.h"
#include "logging-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_allocate_memory_for_socket_address_message = N_("Failed to allocate memory for the socket address.");

static const string_t const failed_to_get_socket_name_message = N_("Failed to get the socket name.");

/*
 * functions.
 */

bool_t
get_host_and_service (const int socket_descriptor,
                      socklen_t address_length,
                      const string_t const host,
                      socklen_t host_length,
                      const string_t const service,
                      socklen_t service_length,
                      const unsigned int flags)
{
  struct sockaddr * address = (struct sockaddr *) malloc (address_length);

  if (!address)
  {
    log_error (_(failed_to_allocate_memory_for_socket_address_message));

    return false;
  }

  if (getsockname (socket_descriptor, address, &address_length) < 0)
  {
    safe_free(address);

    log_error (_(failed_to_get_socket_name_message));

    return false;
  }

  const int return_value = getnameinfo (address, address_length, host, host_length, service, service_length, flags);

  safe_free(address);

  if (return_value != 0)
  {
    log_error ("%s", gai_strerror (return_value));

    return false;
  }

  return true;
}
