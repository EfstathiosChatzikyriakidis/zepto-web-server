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

#ifndef _HTTP_REQUEST_TYPES_H_
#define _HTTP_REQUEST_TYPES_H_

#include "http-types.h"

/*
 * type definitions.
 */

// HTTP request type definition.
typedef struct http_request_t
{
  string_t method;

  string_t uri;

  string_t query;

  string_t protocol_version;

  http_header_field_t * headers;
} http_request_t;

#endif // _HTTP_REQUEST_TYPES_H_
