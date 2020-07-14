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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _BITS_UFORMAT_PRINTER_H
#define _BITS_UFORMAT_PRINTER_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/format-printer.h>

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __C16FORMATPRINTER_CC
#define __C16FORMATPRINTER_CC __LIBDCALL
#endif /* !__C16FORMATPRINTER_CC */

#ifndef __C32FORMATPRINTER_CC
#define __C32FORMATPRINTER_CC __LIBKCALL
#endif /* !__C32FORMATPRINTER_CC */

typedef __SSIZE_TYPE__ (__C16FORMATPRINTER_CC *__pc16formatprinter)(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen);
typedef __SSIZE_TYPE__ (__C32FORMATPRINTER_CC *__pc32formatprinter)(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen);

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BITS_UFORMAT_PRINTER_H */
