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

#ifndef _HTTP_RESPONSE_CONSTANTS_H_
#define _HTTP_RESPONSE_CONSTANTS_H_

#include <stddef.h>

#include "shared-types.h"

/*
 * constants.
 */

// HTTP response status codes.

static const string_t const http_response_status_codes_numbers [] =
{
  "200", // OK
  "400", // Bad Request
  "404", // Not Found
  "501"  // Not Implemented
};

static const string_t const http_response_status_codes_names [] =
{
  "OK",
  "Bad Request",
  "Not Found",
  "Not Implemented"
};

// HTTP response buffer lengths.

static const size_t http_response_initial_buffer_length = 512;

static const size_t http_response_initial_body_buffer_length = 2048;

#endif // _HTTP_RESPONSE_CONSTANTS_H_
