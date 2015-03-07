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

const char * const
get_name (void)
{
  return "module-a";
}

const char * const
get_output (void)
{
  return "<!DOCTYPE html>\n"
         "<html lang='en'>\n"
         " <head>\n"
         "  <meta charset='utf-8' />\n"
         "  <title>Module A</title>\n"
         " </head>\n"
         " <body>\n"
         "  <p>Output from module A.</p>\n"
         " </body>\n"
         "</html>\n";
}
