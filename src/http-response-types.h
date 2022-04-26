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

#ifndef _HTTP_RESPONSE_TYPES_H_
#define _HTTP_RESPONSE_TYPES_H_

#include "http-types.h"

/*
 * type definitions.
 */

// HTTP response status code type definition.
typedef enum http_response_status_code_t
{
  HTTP_RESPONSE_STATUS_CODE_OK,
  HTTP_RESPONSE_STATUS_CODE_BAD_REQUEST,
  HTTP_RESPONSE_STATUS_CODE_NOT_FOUND,
  HTTP_RESPONSE_STATUS_CODE_NOT_IMPLEMENTED
} http_response_status_code_t;

// HTTP response type definition.
typedef struct http_response_t
{
  string_t protocol_version;

  string_t status_code;

  string_t reason_phrase;

  http_header_field_t * headers;

  dynamic_string_t * body;
} http_response_t;

#endif // _HTTP_RESPONSE_TYPES_H_
