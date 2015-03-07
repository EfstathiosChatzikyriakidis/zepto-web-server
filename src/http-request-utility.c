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
#include <string.h>
#include <stdlib.h>

#include "interruption-wrapper-helper-macros.h"
#include "memory-management-helper-macros.h"
#include "http-request-utility.h"

/*
 * function prototypes.
 */

static string_t read_line_from_file_descriptor (const int file_descriptor);

/*
 * functions.
 */

http_request_t * const
read_http_request (const int file_descriptor)
{
  http_request_t * const http_request = (http_request_t *) calloc (1, sizeof (http_request_t));

  if (!http_request)
  {
    return NULL;
  }

  string_t request_line = read_line_from_file_descriptor (file_descriptor);

  if (!request_line)
  {
    clear_http_request (http_request);

    return NULL;
  }

  string_t p = request_line;

  size_t length = strcspn (p, " \t\r\n");

  http_request->method = strndup (request_line, length);

  if (!http_request->method)
  {
    clear_http_request (http_request);

    safe_free(request_line);

    return NULL;
  }

  p += length + strspn (p + length, " \t\r\n");

  length = strcspn (p, "? \t\r\n");

  http_request->uri = strndup (p, length);

  if (!http_request->uri)
  {
    clear_http_request (http_request);

    safe_free(request_line);

    return NULL;
  }

  p += length + strspn (p + length, " \t\r\n");

  if (*p == '?')
  {
    length = strcspn (++p, " \t\r\n");

    http_request->query = strndup (p, length);

    if (!http_request->query)
    {
      clear_http_request (http_request);

      safe_free(request_line);

      return NULL;
    }

    p += length + strspn (p + length, " \t\r\n");
  }

  length = strcspn (p, " \t\r\n");

  http_request->protocol_version = strndup (p, length);

  if (!http_request->protocol_version)
  {
    clear_http_request (http_request);

    safe_free(request_line);

    return NULL;
  }

  p += length + strspn(p + length, " \t\r\n");

  safe_free(request_line);

  while (true)
  {
    string_t header_line = read_line_from_file_descriptor (file_descriptor);

    if (!header_line)
    {
      clear_http_request (http_request);

      return NULL;
    }

    if (!strlen (header_line))
    {
      safe_free(header_line);

      break;
    }

    http_header_field_t * const http_header_field = (http_header_field_t *) calloc (1, sizeof (http_header_field_t));

    if (!http_header_field)
    {
      clear_http_request (http_request);

      safe_free(header_line);

      return NULL;
    }

    http_header_field->next = http_request->headers;

    http_request->headers = http_header_field;

    p = header_line;

    length = strcspn (p, ": \t\r\n");

    http_header_field->name = strndup (p, length);

    if (!http_header_field->name)
    {
      clear_http_request (http_request);

      safe_free(header_line);

      return NULL;
    }

    p += length + strspn (p + length, ": \t\r\n");

    length = strcspn (p, " \t\r\n");

    http_header_field->value = strdup (p);

    if (!http_header_field->value)
    {
      clear_http_request (http_request);

      safe_free(header_line);

      return NULL;
    }

    safe_free(header_line);
  }

  return http_request;
}

void
clear_http_request (http_request_t * http_request)
{
  if (http_request)
  {
    safe_free(http_request->method);

    safe_free(http_request->uri);

    safe_free(http_request->query);

    safe_free(http_request->protocol_version);

    while (http_request->headers)
    {
      http_header_field_t * http_header_field = http_request->headers;

      safe_free(http_header_field->name);

      safe_free(http_header_field->value);

      http_request->headers = http_header_field->next;

      safe_free(http_header_field);
    }
  }

  safe_free(http_request);
}

static string_t
read_line_from_file_descriptor (const int file_descriptor)
{
  static const size_t initial_string_length = 64;

  size_t length = initial_string_length, count = 0;

  string_t line = (string_t) malloc (length + 1);

  if (!line)
  {
    return NULL;
  }

  while (true)
  {
    if (length <= count)
    {
      length *= 2;

      string_t extended_line = (string_t) realloc (line, length + 1);

      if (!extended_line)
      {
        safe_free(line);

        return NULL;
      }

      line = extended_line;
    }

    const ssize_t fetched = HANDLE_EINTR_EAGAIN(read (file_descriptor, line + count, 1));

    if (fetched < 0)
    {
      safe_free(line);

      return NULL;
    }
    else if (fetched != 1)
    {
      break;
    }

    if (line[count] == '\n')
    {
      if (count > 0 && line[count - 1] == '\r')
      {
        count--;
      }

      break;
    }

    count++;
  }

  line[count] = '\0';

  return line;
}
