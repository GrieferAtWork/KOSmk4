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
/* (#) Portability: FreeBSD (/include/xlocale.h) */
/* (#) Portability: Newlib  (/newlib/libc/include/xlocale.h) */
/* (#) Portability: uClibc  (/include/xlocale.h) */
#ifndef _XLOCALE_H
#define _XLOCALE_H 1

#include "__stdinc.h"
#include "__crt.h"

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __locale_t_defined
#define __locale_t_defined 1
typedef __locale_t locale_t;
#endif /* !__locale_t_defined */
#ifdef __USE_DOS
/*typedef __locale_t __locale_t; * ??? */
#endif /* __USE_DOS */
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_XLOCALE_H */
