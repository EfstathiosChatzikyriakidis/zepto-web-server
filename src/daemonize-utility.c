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

#include <sys/stat.h>
#include <sys/file.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "interruption-wrapper-helper-macros.h"
#include "daemonize-utility.h"
#include "pid-file-utility.h"
#include "logging-utility.h"
#include "file-utility.h"
#include "i18n-macros.h"

/*
 * messages.
 */

static const string_t const failed_to_create_new_process_message = N_("Failed to create a new process.");

static const string_t const failed_to_create_new_session_message = N_("Failed to create a new session.");

static const string_t const failed_to_open_virtual_null_device_file_message = N_("Failed to open the virtual null device file.");

static const string_t const failed_to_redirect_standard_io_streams_message = N_("Failed to redirect the standard I/O streams.");

static const string_t const failed_to_change_working_directory_message = N_("Failed to change the working directory.");

static const string_t const failed_to_write_pid_file_message = N_("Failed to write the pid file.");

static const string_t const failed_to_remove_pid_file_message = N_("Failed to remove the pid file.");

static const string_t const failed_to_close_file_descriptor_message = N_("Failed to close the file descriptor:");

static const string_t const failed_to_close_virtual_null_device_file_descriptor_message = N_("Failed to close the descriptor of the virtual null device file.");

static const string_t const pid_file_is_not_readable_message = N_("The pid file is not readable.");

static const string_t const another_instance_probably_running_message = N_("Another instance probably is running.");

/*
 * variables.
 */

static const mode_t file_mode_creation_mask = 027;

static const string_t const virtual_null_device_file_path = "/dev/null";

/*
 * functions.
 */

bool_t
daemonize (const string_t const working_directory_path, const string_t const pid_file_path)
{
  // is it already a daemon process?
  if (getppid () == 1)
  {
    return true;
  }

  // try to create a new process.
  pid_t pid = HANDLE_EAGAIN(fork ());

  // failed to create a new process?
  if (pid < 0)
  {
    log_error (_(failed_to_create_new_process_message));
    return false;
  }
  // parent continues in this code section.
  else if (pid > 0)
  {
    // forget the parent process.
    exit (EXIT_SUCCESS);
  }

  /* try to make new session to ensure that
     we do not have a controlling terminal. */
  if (setsid () < 0)
  {
    log_error (_(failed_to_create_new_session_message));
    return false;
  }

  /* double fork again to ensure that we
     can't regain a controlling terminal. */
  pid = HANDLE_EAGAIN(fork ());

  // failed to create a new process?
  if (pid < 0)
  {
    log_error (_(failed_to_create_new_process_message));
    return false;
  }
  // parent continues in this code section.
  else if (pid > 0)
  {
    // forget the parent process.
    exit (EXIT_SUCCESS);
  }

  // try to change the working directory.
  if (chdir (working_directory_path) < 0)
  {
    log_error (_(failed_to_change_working_directory_message));
    return false;
  }

  // change file creation mask.
  umask (file_mode_creation_mask);

  // try to open the virtual null device file.
  const int virtual_null_device_file_descriptor = HANDLE_EINTR(open (virtual_null_device_file_path, O_RDWR));

  // failed to open the virtual null device file?
  if (virtual_null_device_file_descriptor < 0)
  {
    log_error (_(failed_to_open_virtual_null_device_file_message));
    return false;
  }

  // try to redirect standard I/O streams to virtual null device file.
  if (HANDLE_EINTR(dup2 (virtual_null_device_file_descriptor, STDIN_FILENO)) < 0 ||
      HANDLE_EINTR(dup2 (virtual_null_device_file_descriptor, STDOUT_FILENO)) < 0 ||
      HANDLE_EINTR(dup2 (virtual_null_device_file_descriptor, STDERR_FILENO)) < 0)
  {
    // try to close the virtual null device file descriptor.
    if (close (virtual_null_device_file_descriptor) < 0)
    {
      log_error (_(failed_to_close_virtual_null_device_file_descriptor_message));
      return false;
    }

    log_error (_(failed_to_redirect_standard_io_streams_message));
    return false;
  }

  // try to close the virtual null device file descriptor.
  if (close (virtual_null_device_file_descriptor) < 0)
  {
    log_error (_(failed_to_close_virtual_null_device_file_descriptor_message));
    return false;
  }

  // try to close all inherited file descriptors.
  for (int fd = getdtablesize() - 1; fd >= 0; fd--)
  {
    if (close (fd) < 0 && errno != EBADF)
    {
      log_error ("%s '%d'.", _(failed_to_close_file_descriptor_message), fd);
      return false;
    }
  }

  // in case the pid file already exists.
  if (file_exists (pid_file_path))
  {
    // try to check if the pid file is readable.
    if (!file_is_readable (pid_file_path))
    {
      log_error (_(pid_file_is_not_readable_message));
      return false;
    }

    // try to read the pid from the pid file.
    const pid_t pid_from_pid_file = read_pid_from_file (pid_file_path);

    // if there is a pid that really exists in the system.
    if (pid_from_pid_file != -1 && pid_exists (pid_from_pid_file))
    {
      log_error (_(another_instance_probably_running_message));
      return false;
    }

    // try to remove the pid file since it is garbage.
    if (!remove_file (pid_file_path))
    {
      log_error (_(failed_to_remove_pid_file_message));
      return false;
    }
  }

  // try to create the pid file and write the pid of the daemon to it.
  if (!write_pid_to_file (pid_file_path, getpid ()))
  {
    log_error (_(failed_to_write_pid_file_message));
    return false;
  }

  // the program runs as a daemon.
  return true;
}
