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

#include "memory-management-helper-macros.h"
#include "server-worker-helper-utilities.h"
#include "dynamic-string-helper-utility.h"
#include "command-line-options-utility.h"
#include "http-response-constants.h"
#include "content-types-constants.h"
#include "http-request-constants.h"
#include "http-response-utility.h"
#include "server-module-utility.h"
#include "http-request-utility.h"
#include "content-types-types.h"
#include "http-constants.h"

/*
 * functions.
 */

bool_t
handle_accepted_client (const int client_socket_descriptor)
{
  http_response_t * const http_response = create_http_response();

  if (!http_response)
  {
    return false;
  }

  http_response->protocol_version = http_version_1_1;

  if (!add_http_response_header_field (http_response, http_header_field_name_for_connection, http_header_field_close_value_for_connection))
  {
    clear_http_response (http_response);

    return false;
  }

  http_response->body = dynamic_string_create (http_response_initial_body_buffer_length);

  if (!http_response->body)
  {
    clear_http_response (http_response);

    return false;
  }

  http_request_t * const http_request = read_http_request (client_socket_descriptor);

  if (!http_request)
  {
    clear_http_response (http_response);

    return false;
  }

  if (strcmp (http_request->protocol_version, http_version_1_0) &&
      strcmp (http_request->protocol_version, http_version_1_1))
  {
    set_http_response_status_code (http_response, HTTP_RESPONSE_STATUS_CODE_BAD_REQUEST);

    if (!add_http_response_header_field (http_response, http_header_field_name_for_content_type, content_types[TEXT_PLAIN]) ||
        !dynamic_string_append (http_response->body, http_response_status_codes_names[HTTP_RESPONSE_STATUS_CODE_BAD_REQUEST]))
    {
      clear_http_request (http_request);

      clear_http_response (http_response);

      return false;
    }
  }
  else if (strcmp (http_request->method, http_request_get_method))
  {
    set_http_response_status_code (http_response, HTTP_RESPONSE_STATUS_CODE_NOT_IMPLEMENTED);

    if (!add_http_response_header_field (http_response, http_header_field_name_for_content_type, content_types[TEXT_PLAIN]) ||
        !dynamic_string_append (http_response->body, http_response_status_codes_names[HTTP_RESPONSE_STATUS_CODE_NOT_IMPLEMENTED]))
    {
      clear_http_request (http_request);

      clear_http_response (http_response);

      return false;
    }
  }
  else
  {
    server_module_t * server_module = NULL;

    if (http_request->uri[0] == http_uri_separator)
    {
      const string_t const server_module_name = http_request->uri + 1;

      if (strlen (server_module_name) && !strchr (server_module_name, http_uri_separator))
      {
        const options_t * const options = get_command_line_options();

        string_t server_module_file_path = get_server_module_file_path (options->server_modules_path, server_module_name);

        if (!server_module_file_path)
        {
          clear_http_request (http_request);

          clear_http_response (http_response);

          return false;
        }

        server_module = server_module_open (server_module_file_path);

        safe_free (server_module_file_path);
      }
    }

    if (server_module)
    {
      set_http_response_status_code (http_response, HTTP_RESPONSE_STATUS_CODE_OK);

      if (!add_http_response_header_field (http_response, http_header_field_name_for_content_type, content_types[TEXT_HTML]) ||
          !dynamic_string_append (http_response->body, (*server_module->get_output) ()))
      {
        clear_http_request (http_request);

        clear_http_response (http_response);

        server_module_clear (server_module);

        return false;
      }

      server_module_clear (server_module);
    }
    else
    {
      set_http_response_status_code (http_response, HTTP_RESPONSE_STATUS_CODE_NOT_FOUND);

      if (!add_http_response_header_field (http_response, http_header_field_name_for_content_type, content_types[TEXT_PLAIN]) ||
          !dynamic_string_append (http_response->body, http_response_status_codes_names[HTTP_RESPONSE_STATUS_CODE_NOT_FOUND]))
      {
        clear_http_request (http_request);

        clear_http_response (http_response);

        return false;
      }
    }
  }

  const bool_t written = write_http_response (client_socket_descriptor, http_response);

  clear_http_request (http_request);

  clear_http_response (http_response);

  return written != false;
}
