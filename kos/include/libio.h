/* HASH CRC-32:0xb7d00753 */
/* Copyright (c) 2019 Griefer@Work                                            *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _LIBIO_H
#define _LIBIO_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>

/* Partially derived from GNU C /usr/include/libio.h */

/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Written by Per Bothner <bothner@cygnus.com>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License. This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  */


#ifndef EOF
#define EOF (-1)
#endif

#ifndef NULL
#define NULL __NULLPTR
#endif

__SYSDECL_BEGIN

#ifdef __CC__

#ifndef __wint_t_defined
#define __wint_t_defined 1
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */

/* Functions to do I/O and file management for a stream. */

/* Read NBYTES bytes from COOKIE into a buffer pointed to by BUF.
 * Return number of bytes read. */
typedef __ssize_t (__LIBCCALL __io_read_fn)(void *__cookie, char *__buf, __size_t __nbytes);

/* Write N bytes pointed to by BUF to COOKIE. Write all N bytes
 * unless there is an error. Return number of bytes written. If
 * there is an error, return 0 and do not write anything. If the file
 * has been opened for append (__mode.__append set), then set the file
 * pointer to the end of the file and then do the write; if not, just
 * write at the current file pointer. */
typedef __ssize_t (__LIBCCALL __io_write_fn)(void *__cookie, const char *__buf, __size_t __n);

/* Move COOKIE's file position to *POS bytes from the
 * beginning of the file (if W is SEEK_SET),
 * the current position (if W is SEEK_CUR),
 * or the end of the file (if W is SEEK_END).
 * Set *POS to the new file position.
 * Returns zero if successful, nonzero if not. */
typedef int (__LIBCCALL __io_seek_fn)(void *__cookie, __off64_t *__pos, int __w);

/* Close COOKIE. */
typedef int (__LIBCCALL __io_close_fn)(void *__cookie);

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("read")
#pragma push_macro("write")
#pragma push_macro("seek")
#pragma push_macro("close")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef read
#undef write
#undef seek
#undef close

/* The structure with the cookie function pointers.  */
typedef struct {
	__io_read_fn  *read;   /* Read bytes.  */
	__io_write_fn *write;  /* Write bytes.  */
	__io_seek_fn  *seek;   /* Seek/tell file position.  */
	__io_close_fn *close;  /* Close file.  */
} _IO_cookie_io_functions_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("close")
#pragma pop_macro("seek")
#pragma pop_macro("write")
#pragma pop_macro("read")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __USE_GNU
/* User-visible names for the above.  */
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
#endif /* __USE_GNU */


#endif /* __CC__ */

__SYSDECL_END

#endif /* !_LIBIO_H */
