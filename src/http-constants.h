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

#ifndef _HTTP_CONSTANTS_H_
#define _HTTP_CONSTANTS_H_

#include "shared-types.h"

/*
 * constants.
 */

// HTTP versions.

static const string_t const http_version_1_0 = "HTTP/1.0";

static const string_t const http_version_1_1 = "HTTP/1.1";

// HTTP separators.

static const char http_uri_separator = '/';

// HTTP delimiters.

static const string_t const http_line_end_delimiter = "\r\n";

static const string_t const http_header_field_name_value_delimiter = ": ";

// HTTP header field names.

static const string_t const http_header_field_name_for_content_type = "Content-Type";

static const string_t const http_header_field_name_for_connection = "Connection";

// HTTP header field values.

static const string_t const http_header_field_close_value_for_connection = "close";

#endif // _HTTP_CONSTANTS_H_
