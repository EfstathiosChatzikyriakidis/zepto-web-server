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

#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "logging-utility.h"
#include "socket-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_close_server_socket_descriptor_message = N_("Failed to close the server socket descriptor.");

/*
 * functions.
 */

int
create_server_socket (const string_t const server_address,
                      const string_t const server_port,
                      const int ai_flags,
                      const int ai_family,
                      const int ai_protocol,
                      const int ai_socktype,
                      socklen_t * const server_address_length)
{
  struct addrinfo hints;

  memset (&hints, 0, sizeof (hints));

  hints.ai_family = ai_family;
  hints.ai_socktype = ai_socktype;
  hints.ai_protocol = ai_protocol;
  hints.ai_flags = ai_flags;

  struct addrinfo * server_addresses = NULL;

  const int return_value = getaddrinfo (server_address, server_port, &hints, &server_addresses);

  if (return_value != 0)
  {
    log_error ("%s", gai_strerror (return_value));

    return -1;
  }

  bool_t server_socket_found = false;

  int server_socket_descriptor = -1;

  const int reuse_address_on = 1;

  for (struct addrinfo * address = server_addresses; address; address = address->ai_next)
  {
    server_socket_descriptor = socket (address->ai_family, address->ai_socktype, address->ai_protocol);

    if (server_socket_descriptor < 0)
    {
      continue;
    }

    if (setsockopt (server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, &reuse_address_on, sizeof (reuse_address_on)) != -1)
    {
      if (bind (server_socket_descriptor, address->ai_addr, address->ai_addrlen) != -1)
      {
        *server_address_length = address->ai_addrlen;

        server_socket_found = true;

        break;
      }
    }

    if (close (server_socket_descriptor) < 0)
    {
      log_error (_(failed_to_close_server_socket_descriptor_message));

      break;
    }
  } 

  freeaddrinfo (server_addresses);

  return server_socket_found ? server_socket_descriptor : -1;
}
