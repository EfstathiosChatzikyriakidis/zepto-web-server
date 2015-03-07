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

#include <unistd.h>
#include <stdlib.h>

#include "interruption-wrapper-helper-macros.h"
#include "memory-management-helper-macros.h"
#include "dynamic-string-helper-utility.h"
#include "http-response-constants.h"
#include "http-response-utility.h"
#include "http-constants.h"

/*
 * function prototypes.
 */

static ssize_t write_to_file_descriptor (const int file_descriptor, const void * buffer, size_t count);

/*
 * functions.
 */

http_response_t * const
create_http_response (void)
{
  http_response_t * const http_response = (http_response_t *) calloc (1, sizeof (http_response_t));

  if (!http_response)
  {
    return NULL;
  }

  http_response->protocol_version = NULL;
  http_response->status_code = NULL;
  http_response->reason_phrase = NULL;
  http_response->headers = NULL;
  http_response->body = NULL;

  return http_response;
}

void
set_http_response_status_code (http_response_t * const http_response, const http_response_status_code_t http_response_status_code)
{
  http_response->status_code = http_response_status_codes_numbers[http_response_status_code];

  http_response->reason_phrase = http_response_status_codes_names[http_response_status_code];
}

bool_t
add_http_response_header_field (http_response_t * const http_response, const string_t const field_name, const string_t const field_value)
{
  http_header_field_t * const http_header_field = (http_header_field_t *) calloc (1, sizeof (http_header_field_t));

  if (!http_header_field)
  {
    return false;
  }

  http_header_field->name = field_name;

  http_header_field->value = field_value;

  http_header_field->next = http_response->headers;

  http_response->headers = http_header_field;

  return true;
}

bool_t
write_http_response (const int file_descriptor, const http_response_t * const http_response)
{
  dynamic_string_t * const response = dynamic_string_create (http_response_initial_buffer_length);

  if (!response)
  {
    return false;
  }

  if (!dynamic_string_append (response, http_response->protocol_version) ||
      !dynamic_string_append (response, " ") ||
      !dynamic_string_append (response, http_response->status_code) ||
      !dynamic_string_append (response, " ") ||
      !dynamic_string_append (response, http_response->reason_phrase) ||
      !dynamic_string_append (response, http_line_end_delimiter))
  {
    dynamic_string_clear (response);

    return false;
  }

  const http_header_field_t * headers = http_response->headers;

  while (headers)
  {
    if (!dynamic_string_append (response, headers->name) ||
        !dynamic_string_append (response, http_header_field_name_value_delimiter) ||
        !dynamic_string_append (response, headers->value) ||
        !dynamic_string_append (response, http_line_end_delimiter))
    {
      dynamic_string_clear (response);

      return false;
    }

    headers = headers->next;
  }

  if (!dynamic_string_append (response, http_line_end_delimiter) ||
      !dynamic_string_append (response, http_response->body->string))
  {
    dynamic_string_clear (response);

    return false;
  }

  const bool_t written = write_to_file_descriptor (file_descriptor, response->string, dynamic_string_length (response));

  dynamic_string_clear (response);

  return written != -1;
}

void
clear_http_response (http_response_t * http_response)
{
  if (http_response)
  {
    while (http_response->headers)
    {
      http_header_field_t * http_header_field = http_response->headers;

      http_response->headers = http_header_field->next;

      safe_free(http_header_field);
    }

    if(http_response->body)
    {
      dynamic_string_clear (http_response->body);
    }
  }

  safe_free(http_response);
}

static ssize_t
write_to_file_descriptor (const int file_descriptor, const void * buffer, size_t count)
{
  ssize_t total_written = 0;

  while (count > 0)
  {
    const ssize_t written = HANDLE_EINTR_EAGAIN(write (file_descriptor, buffer, count));

    if (written < 0)
    {
      return -1;
    }

    total_written += written;

    buffer = (const char *) buffer + written;

    count -= (size_t) written;
  }

  return total_written;
}
