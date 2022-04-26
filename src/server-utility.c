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

#include <unistd.h>
#include <netdb.h>

#include "server-signals-support-utility.h"
#include "command-line-options-utility.h"
#include "preforking-server-utility.h"
#include "server-helper-utilities.h"
#include "file-descriptor-utility.h"
#include "socket-utility.h"
#include "logging-utility.h"
#include "server-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_connect_server_socket_message = N_("Failed to connect the server socket.");

static const string_t const failed_to_instruct_server_socket_to_listen_for_incoming_requests_message = N_("Failed to instruct the server socket to listen for incoming requests.");

static const string_t const failed_to_disable_io_blocking_of_server_socket_descriptor_message = N_("Failed to disable the I/O blocking of the server socket descriptor.");

static const string_t const failed_to_setup_server_signals_support_message = N_("Failed to setup the signals support of the server.");

static const string_t const failed_to_close_server_socket_descriptor_message = N_("Failed to close the server socket descriptor.");

static const string_t const failed_to_get_server_host_name_and_service_message = N_("Failed to get the host name and the service of the server.");

static const string_t const server_listens_on_following_socket_message = N_("The server listens on the following socket:");

/*
 * variables.
 */

static const string_t const default_server_port = "0";

static const int default_listen_backlog = 128;

/*
 * functions.
 */

bool_t
server_run (void)
{
  const options_t * const options = get_command_line_options();

  string_t server_port = default_server_port;

  if (options->server_port)
  {
    server_port = options->server_port;
  }

  socklen_t server_address_length;

  const int server_socket_descriptor = create_server_socket (options->server_address, server_port, AI_PASSIVE | AI_NUMERICSERV, AF_UNSPEC, IPPROTO_TCP, SOCK_STREAM, &server_address_length);

  if (server_socket_descriptor < 0)
  {
    log_error (_(failed_to_connect_server_socket_message));
    return false;
  }

  char host[NI_MAXHOST], service[NI_MAXSERV];

  if (!get_host_and_service (server_socket_descriptor, server_address_length, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV))
  {
    log_error (_(failed_to_get_server_host_name_and_service_message));
    return false;
  }

  log_info ("%s [%s - %s]", _(server_listens_on_following_socket_message), host, service);

  if (listen (server_socket_descriptor, default_listen_backlog) < 0)
  {
    log_error (_(failed_to_instruct_server_socket_to_listen_for_incoming_requests_message));
    return false;
  }

  if (!disable_io_blocking_for_file_descriptor (server_socket_descriptor))
  {
    log_error (_(failed_to_disable_io_blocking_of_server_socket_descriptor_message));
    return false;
  }

  if (!setup_server_signals_support ())
  {
    log_error (_(failed_to_setup_server_signals_support_message));
    return false;
  }

  const bool_t server_status = create_preforking_server (options->server_workers, options->server_worker_requests, server_socket_descriptor);

  if (close (server_socket_descriptor) < 0)
  {
    log_error (_(failed_to_close_server_socket_descriptor_message));
    return false;
  }

  return server_status;
}
