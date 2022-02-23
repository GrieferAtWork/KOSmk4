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
#ifndef _PARTS_PRINTF_CONFIG_H
#define _PARTS_PRINTF_CONFIG_H 1

#include <__crt.h>
#include <__stdinc.h>

/* Disable unsupported/unwanted/unneeded printf() features */

/* #define __NO_PRINTF_ESCAPE         -- "%q" */
/* #define __NO_PRINTF_UNICODE_CHARS  -- "%I16c", "%I32c" */
/* #define __NO_PRINTF_UNICODE_STRING -- "%I16s", "%I32s" */
/* #define __NO_PRINTF_STRERROR       -- "%m" */
/* #define __NO_PRINTF_HEX            -- "%[hex]" */
/* #define __NO_PRINTF_GEN            -- "%[gen]" */
/* #define __NO_PRINTF_DISASM         -- "%[disasm]" */
/* #define __NO_PRINTF_VINFO          -- "%[vinfo]" */
/* #define __NO_PRINTF_FLOATING_POINT -- "%f" */
/* #define __NO_PRINTF_POSITIONAL     -- "%1$s" */
/* #define __NO_SCANF_FLOATING_POINT  -- "%f" */

#if defined(__KOS__) && defined(__KERNEL__)
#undef __NO_PRINTF_UNICODE_STRING
#define __NO_PRINTF_UNICODE_STRING
#undef __NO_PRINTF_STRERROR
#define __NO_PRINTF_STRERROR
#undef __NO_PRINTF_UNICODE_CHARS
#define __NO_PRINTF_UNICODE_CHARS
#undef __NO_PRINTF_DISASM
#define __NO_PRINTF_DISASM
//#undef __NO_PRINTF_POSITIONAL
//#define __NO_PRINTF_POSITIONAL
#elif !defined(__CRT_KOS) || !defined(__KOS__)
#undef __NO_PRINTF_GEN
#define __NO_PRINTF_GEN
#undef __NO_PRINTF_DISASM
#define __NO_PRINTF_DISASM
#undef __NO_PRINTF_VINFO
#define __NO_PRINTF_VINFO
#undef __NO_PRINTF_HEX
#define __NO_PRINTF_HEX
#ifndef __CRT_GLC
#undef __NO_PRINTF_POSITIONAL
#define __NO_PRINTF_POSITIONAL
#endif /* !__CRT_GLC */
#endif /* !__CRT_KOS || !__KOS__ */

#ifdef __NO_FPU
#undef __NO_PRINTF_FLOATING_POINT
#define __NO_PRINTF_FLOATING_POINT
#undef __NO_SCANF_FLOATING_POINT
#define __NO_SCANF_FLOATING_POINT
#endif /* __NO_FPU */


#endif /* !_PARTS_PRINTF_CONFIG_H */
