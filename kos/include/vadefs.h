/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: MSVC  (/include/vadefs.h) */
/* (#) Portability: MinGW (/mingw-w64-headers/crt/vadefs.h) */
#ifndef _VADEFS_H
#define _VADEFS_H 1

#include "__stdinc.h"
#include <features.h>
#ifdef __USE_DOS
#ifndef _INC_CRTDEFS
#include <crtdefs.h>
#endif /* !_INC_CRTDEFS */
#endif /* __USE_DOS */

#ifdef __CC__
__DECL_BEGIN

#ifndef __va_list_defined
#define __va_list_defined
typedef __builtin_va_list va_list;
#endif /* !__va_list_defined */

#ifdef __USE_DOS
#ifndef _ADDRESSOF
#ifdef __cplusplus
#define _ADDRESSOF(v) (&reinterpret_cast<char const &>(v))
#else /* __cplusplus */
#define _ADDRESSOF(v) (&(v))
#endif /* !__cplusplus */
#endif /* !_ADDRESSOF */
#endif /* __USE_DOS */

#define _crt_va_start(ap, start)     __builtin_va_start(ap, start)
#define _crt_va_arg(ap, T)           __builtin_va_arg(ap, T)
#define _crt_va_end(ap)              __builtin_va_end(ap)
#define _crt_va_copy(dst_ap, src_ap) __builtin_va_copy(dst_ap, src_ap)

__DECL_END
#endif /* __CC__ */

#endif /* !_VADEFS_H */
