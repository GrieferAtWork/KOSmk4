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
%(c_prefix){
/* (#) Portability: GNU C Library (/libio/libio.h) */
/* (#) Portability: libc4/5       (/include/libio.h) */
}

%[define_replacement(fd_t = __fd_t)]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%[insert:prefix(
#include <asm/os/stdio.h>
)]%[insert:prefix(
#include <asm/crt/stdio.h>
)]%{

#if !defined(EOF) && defined(__EOF)
#define EOF __EOF
#endif /* !EOF && __EOF */

#ifndef NULL
#define NULL __NULLPTR
#endif /* !NULL */

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

}%[push_macro @undef { read write seek close }]%{

/* Container for user-defined I/O Callback functions. */
typedef struct {
	__io_read_fn  *read;   /* [0..1] Read callback. */
	__io_write_fn *write;  /* [0..1] Write callback. */
	__io_seek_fn  *seek;   /* [0..1] Seek/tell callback. */
	__io_close_fn *close;  /* [0..1] Close callback. */
} _IO_cookie_io_functions_t;

}%[pop_macro]%{

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

}

%[define_type_class(_IO_cookie_io_functions_t = "TS(__SIZEOF_COOKIE_IO_FUNCTIONS_T)")]
%[define_type_class(cookie_io_functions_t     = "TS(__SIZEOF_COOKIE_IO_FUNCTIONS_T)")]

/* ... */

%{

__SYSDECL_END
#endif /* __CC__ */

}
