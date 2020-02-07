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
#ifndef _ASM_PRINTF_CONFIG_H
#define _ASM_PRINTF_CONFIG_H 1

#include <__stdinc.h>
#include <__crt.h>

/* Disable unsupported/unwanted/unneeded printf() features */

/* #define __NO_PRINTF_ESCAPE 1 */
/* #define __NO_PRINTF_UNICODE_CHARS 1 */
/* #define __NO_PRINTF_UNICODE_STRING 1 */
/* #define __NO_PRINTF_HEX 1 */
/* #define __NO_PRINTF_GEN 1 */
/* #define __NO_PRINTF_DISASM 1 */
/* #define __NO_PRINTF_VINFO 1 */
/* #define __NO_PRINTF_FLOATING_POINT 1 */

#if defined(__KOS__) && defined(__KERNEL__)
#undef __NO_PRINTF_UNICODE_STRING
#define __NO_PRINTF_UNICODE_STRING 1
#undef __NO_PRINTF_UNICODE_CHARS
#define __NO_PRINTF_UNICODE_CHARS 1
#undef __NO_PRINTF_FLOATING_POINT
#define __NO_PRINTF_FLOATING_POINT 1
#undef __NO_PRINTF_DISASM
#define __NO_PRINTF_DISASM 1
#elif !defined(__CRT_KOS) || !defined(__KOS__)
#undef __NO_PRINTF_DISASM
#define __NO_PRINTF_DISASM 1
#undef __NO_PRINTF_VINFO
#define __NO_PRINTF_VINFO 1
#endif /* !__CRT_KOS || !__KOS__ */


#endif /* !_ASM_PRINTF_CONFIG_H */
