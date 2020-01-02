/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
#ifndef _BITS_FORMAT_PRINTER_H
#define _BITS_FORMAT_PRINTER_H 1

#include <__stdinc.h>
#include <__crt.h>
#include <hybrid/typecore.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if __KOS_VERSION__ >= 400
typedef __SSIZE_TYPE__ (__LIBCCALL *__pformatprinter)(void *__arg, /*utf-8*/ char const *__restrict __data, __SIZE_TYPE__ __datalen);
typedef /*utf-32*/ __SSIZE_TYPE__ (__LIBCCALL *__pformatgetc)(void *__arg);
typedef __SSIZE_TYPE__ (__LIBCCALL *__pformatungetc)(void *__arg, /*utf-32*/ __CHAR32_TYPE__ __ch);
#else /* __KOS_VERSION__ >= 400 */
typedef __SSIZE_TYPE__ (__LIBCCALL *__pformatprinter)(/*utf-8*/ char const *__restrict __data, __SIZE_TYPE__ __datalen, void *__arg);
typedef /*utf-32*/ __SSIZE_TYPE__ (__LIBCCALL *__pformatgetc)(void *__arg);
typedef __SSIZE_TYPE__ (__LIBCCALL *__pformatungetc)(/*utf-32*/ __CHAR32_TYPE__ __ch, void *__arg);
#endif /* __KOS_VERSION__ < 400 */

/* Read up to `NUM_BYTES' bytes into `BUF', returning the actual number of
 * read bytes, or a negative error value to-be propagated up the call-stack. */
typedef __SSIZE_TYPE__ (__LIBCCALL *__pformatreader)(void *__arg, void *__restrict __buf, __SIZE_TYPE__ __num_bytes);


__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_FORMAT_PRINTER_H */
