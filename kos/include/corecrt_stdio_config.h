/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: Windows Kits (/ucrt/corecrt_stdio_config.h) */
#ifndef _CORECRT_STDIO_CONFIG_H
#define _CORECRT_STDIO_CONFIG_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#ifndef _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS
#define _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS 0
#endif /* !_CRT_INTERNAL_LOCAL_PRINTF_OPTIONS */
#ifndef _CRT_INTERNAL_LOCAL_SCANF_OPTIONS
#define _CRT_INTERNAL_LOCAL_SCANF_OPTIONS 0
#endif /* !_CRT_INTERNAL_LOCAL_SCANF_OPTIONS */

#define _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION __UINT64_C(1)
#define _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR       __UINT64_C(2)
#define _CRT_INTERNAL_PRINTF_LEGACY_WIDE_SPECIFIERS           __UINT64_C(4)
#define _CRT_INTERNAL_PRINTF_LEGACY_MSVCRT_COMPATIBILITY      __UINT64_C(8)
#define _CRT_INTERNAL_PRINTF_LEGACY_THREE_DIGIT_EXPONENTS     __UINT64_C(16)

#define _CRT_INTERNAL_SCANF_SECURECRT                   __UINT64_C(1)
#define _CRT_INTERNAL_SCANF_LEGACY_WIDE_SPECIFIERS      __UINT64_C(2)
#define _CRT_INTERNAL_SCANF_LEGACY_MSVCRT_COMPATIBILITY __UINT64_C(4)

#endif /* !_CORECRT_STDIO_CONFIG_H */
