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

#ifndef _HTTP_RESPONSE_UTILITY_H_
#define _HTTP_RESPONSE_UTILITY_H_

#include "http-response-types.h"

http_response_t * const create_http_response (void);

void set_http_response_status_code (http_response_t * const http_response, const http_response_status_code_t http_response_status_code);

bool_t add_http_response_header_field (http_response_t * const http_response, const string_t const field_name, const string_t const field_value);

bool_t write_http_response (const int file_descriptor, const http_response_t * const http_response);

void clear_http_response (http_response_t * http_response);

#endif // _HTTP_RESPONSE_UTILITY_H_
