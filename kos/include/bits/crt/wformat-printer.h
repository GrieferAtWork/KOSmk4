/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_CRT_WFORMAT_PRINTER_H
#define _BITS_CRT_WFORMAT_PRINTER_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/crt/format-printer.h>

#ifdef __CC__
__DECL_BEGIN

#ifndef __WFORMATPRINTER_CC
#ifdef __PE__
#define __WFORMATPRINTER_CC __LIBDCALL
#elif defined(__ELF__)
#define __WFORMATPRINTER_CC __LIBKCALL
#else /* ... */
#define __WFORMATPRINTER_CC __LIBCCALL
#endif /* !... */
#endif /* !__WFORMATPRINTER_CC */

typedef __SSIZE_TYPE__ (__WFORMATPRINTER_CC *__pwformatprinter)(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen);

__DECL_END
#endif /* __CC__ */

#endif /* !_BITS_CRT_WFORMAT_PRINTER_H */
