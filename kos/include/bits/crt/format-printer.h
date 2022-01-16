/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_FORMAT_PRINTER_H
#define _BITS_CRT_FORMAT_PRINTER_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __FORMATPRINTER_CC
#define __FORMATPRINTER_CC __LIBKCALL
#define __LIBKCALL_IS_FORMATPRINTER_CC 1
#ifdef __LIBCCALL_IS_LIBKCALL
#define __LIBCCALL_IS_FORMATPRINTER_CC 1
#endif /* __LIBCCALL_IS_LIBKCALL */
#ifdef __LIBDCALL_IS_LIBKCALL
#define __LIBDCALL_IS_FORMATPRINTER_CC 1
#endif /* __LIBDCALL_IS_LIBKCALL */
#endif /* !__FORMATPRINTER_CC */

/* Callback functions prototypes provided to format functions.
 * NOTE: 'pformatprinter' usually returns the number of characters printed, but isn't required to.
 * @param: arg:     The user-defined closure parameter passed alongside this function pointer.
 * @param: data:    The base address of a `datalen' bytes long character vector that should be printed.
 * @param: datalen: The  amount  of  characters  that  should  be  printed,  starting  at  `data'.
 *                  Note  that  this is  an exact  value, meaning  that a  NUL-character appearing
 *                  before then should not terminate printing prematurely, but be printed as well.
 * @return: < 0:    An error occurred and the calling function shall return with this same value.
 * @return: >= 0:   The print was successful.
 *                  Usually,  the return value is added to a sum of values which is then
 *                  returned by the calling function upon success, also meaning that the
 *                  usual return value used to indicate success is `datalen'. */
#if __KOS_VERSION__ >= 400
typedef __SSIZE_TYPE__ (__FORMATPRINTER_CC *__pformatprinter)(void *__arg, /*utf-8*/ char const *__restrict __data, __SIZE_TYPE__ __datalen);
typedef /*utf-32*/ __SSIZE_TYPE__ (__FORMATPRINTER_CC *__pformatgetc)(void *__arg);
typedef __SSIZE_TYPE__ (__FORMATPRINTER_CC *__pformatungetc)(void *__arg, /*utf-32*/ __CHAR32_TYPE__ __ch);
#else /* __KOS_VERSION__ >= 400 */
typedef __SSIZE_TYPE__ (__FORMATPRINTER_CC *__pformatprinter)(/*utf-8*/ char const *__restrict __data, __SIZE_TYPE__ __datalen, void *__arg);
typedef /*utf-32*/ __SSIZE_TYPE__ (__FORMATPRINTER_CC *__pformatgetc)(void *__arg);
typedef __SSIZE_TYPE__ (__FORMATPRINTER_CC *__pformatungetc)(/*utf-32*/ __CHAR32_TYPE__ __ch, void *__arg);
#endif /* __KOS_VERSION__ < 400 */

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_FORMAT_PRINTER_H */
