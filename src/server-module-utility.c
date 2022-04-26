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

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "memory-management-helper-macros.h"
#include "dynamic-string-helper-utility.h"
#include "file-system-constants.h"
#include "server-module-utility.h"

/*
 * variables.
 */

static const string_t const symbol_name_for_getting_server_module_name = "get_name";

static const string_t const symbol_name_for_getting_server_module_output = "get_output";

static const string_t const server_module_file_name_extension = ".so";

/*
 * functions.
 */

server_module_t * const
server_module_open (const string_t const server_module_file_path)
{
  server_module_t * const module = (server_module_t *) calloc (1, sizeof (server_module_t));

  if (!module)
  {
    return NULL;
  }

  module->handle = dlopen (server_module_file_path, RTLD_NOW);

  if (!module->handle)
  {
    server_module_clear (module);

    return NULL;
  }

  module->get_output = (string_t (*) (void)) dlsym (module->handle, symbol_name_for_getting_server_module_output);

  if (!module->get_output)
  {
    server_module_clear (module);

    return NULL;
  }

  string_t (* get_name) (void) = (string_t (*) (void)) dlsym (module->handle, symbol_name_for_getting_server_module_name);

  module->name = strdup (get_name ());

  if (!module->name)
  {
    server_module_clear (module);

    return NULL;
  }

  return module;
}

void
server_module_clear (server_module_t * server_module)
{
  if (server_module)
  {
    if (server_module->handle)
    {
      dlclose (server_module->handle);
    }

    safe_free(server_module->name);
  }

  safe_free(server_module);
}

const string_t const
get_server_module_file_path (const string_t const server_modules_path, const string_t const server_module_name)
{
  dynamic_string_t * const server_module_file_path = dynamic_string_create (strlen (server_modules_path));

  if (!server_module_file_path)
  {
    return NULL;
  }

  if (!dynamic_string_append (server_module_file_path, server_modules_path) ||
      !dynamic_string_append (server_module_file_path, file_system_directory_separator) ||
      !dynamic_string_append (server_module_file_path, server_module_name) ||
      !dynamic_string_append (server_module_file_path, server_module_file_name_extension))
  {
    dynamic_string_clear (server_module_file_path);

    return NULL;
  }

  const string_t const file_path = strdup (server_module_file_path->string);

  if (!file_path)
  {
    dynamic_string_clear (server_module_file_path);

    return NULL;
  }

  dynamic_string_clear (server_module_file_path);

  return file_path;
}
