/* HASH CRC-32:0x8920fc43 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/libio/libio.h) */
/* (#) Portability: libc4/5       (/include/libio.h) */
#ifndef _LIBIO_H
#define _LIBIO_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <bits/types.h>
#include <asm/os/stdio.h>
#include <asm/crt/stdio.h>

#ifndef _STDIO_H
#ifdef __INTELLISENSE__
#include <bits/types/NULL.h>
#ifndef __USE_ISOC_PURE
#include <bits/types/wint_t.h>
#endif /* !__USE_ISOC_PURE */
#endif /* __INTELLISENSE__ */

#if !defined(EOF) && defined(__EOF)
#define EOF __EOF
#endif /* !EOF && __EOF */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */
#endif /* !_STDIO_H */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __USE_ISOC_PURE
#ifndef __wint_t_defined
#define __wint_t_defined
typedef __WINT_TYPE__ wint_t;
#endif /* !__wint_t_defined */
#endif /* !__USE_ISOC_PURE */

/* Prototypes for user-defined FILE I/O functions. */

/* User-defined read function:
 * @param: cookie:   Pointer to custom user-data.
 * @param: buf:      Output buffer for where read data should be put.
 * @param: num_byts: The max # of bytes to read.
 * @return: * :      The actual # of bytes read.
 * @return: 0 :      Error. */
typedef __ssize_t (__LIBKCALL __io_read_fn)(void *__cookie, char *__buf, __size_t __num_bytes);

/* User-defined write function:
 * @param: cookie:   Pointer to custom user-data.
 * @param: buf:      Input buffer of data to write.
 * @param: num_byts: The max # of bytes to write.
 * @return: * :      The actual # of bytes written.
 * @return: 0 :      Error. */
typedef __ssize_t (__LIBKCALL __io_write_fn)(void *__cookie, char const *__buf, __size_t __num_bytes);

/* User-defined seek function:
 * @param: cookie:   Pointer to custom user-data.
 * @param: pos:      [in] The position/offset by which to move the R/W pointer:
 *                        `whence == SEEK_SET': Let R/W be <BASE> + pos
 *                        `whence == SEEK_CUR': Let R/W be <R/W>  + pos
 *                        `whence == SEEK_END': Let R/W be <END>  + pos
 *                   [out] The new R/W pointer position (offset from <BASE>)
 * @param: num_byts: The max # of bytes to write.
 * @return: == 0:    Success.
 * @return: != 0:    Error. */
#ifdef __USE_KOS_ALTERATIONS
typedef int (__LIBKCALL __io_seek_fn)(void *__cookie, __pos64_t *__pos, int __whence);
#else /* __USE_KOS_ALTERATIONS */
typedef int (__LIBKCALL __io_seek_fn)(void *__cookie, __off64_t *__pos, int __whence);
#endif /* !__USE_KOS_ALTERATIONS */

/* User-defined file close function:
 * @param: cookie:   Pointer to custom user-data.
 * @return: == 0:    Success.
 * @return: != 0:    Error. */
typedef int (__LIBKCALL __io_close_fn)(void *__cookie);

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

/* Container for user-defined I/O Callback functions. */
typedef struct {
	__io_read_fn  *read;   /* [0..1] Read callback. */
	__io_write_fn *write;  /* [0..1] Write callback. */
	__io_seek_fn  *seek;   /* [0..1] Seek/tell callback. */
	__io_close_fn *close;  /* [0..1] Close callback. */
} _IO_cookie_io_functions_t;

#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("close")
#pragma pop_macro("seek")
#pragma pop_macro("write")
#pragma pop_macro("read")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __USE_GNU
/* Public API name aliases. */
typedef __io_read_fn cookie_read_function_t;
typedef __io_write_fn cookie_write_function_t;
typedef __io_seek_fn cookie_seek_function_t;
typedef __io_close_fn cookie_close_function_t;
#ifndef __cookie_io_functions_t_defined
#define __cookie_io_functions_t_defined
typedef _IO_cookie_io_functions_t cookie_io_functions_t;
#endif /* !__cookie_io_functions_t_defined */
#endif /* __USE_GNU */


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_LIBIO_H */
