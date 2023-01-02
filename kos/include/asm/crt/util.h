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
#ifndef _ASM_CRT_UTIL_H
#define _ASM_CRT_UTIL_H 1

#include <__crt.h>

#if defined(__CRT_KOS) || 1

/* Options for the `dflags' argument to `opendev(3)' */
#define __OPENDEV_PART 0x01 /* Attempt to open a raw partition during expansion. */
#define __OPENDEV_BLCK 0x02 /* Open a block device (rather than a character device). */

/* Options for the `flags' argument to `fparseln(3)' */
#define __FPARSELN_UNESCESC  0x01 /* Remove escape before an escaped escape. */
#define __FPARSELN_UNESCCONT 0x02 /* Remove escape before an escaped continuation. */
#define __FPARSELN_UNESCCOMM 0x04 /* Remove escape before an escaped comment. */
#define __FPARSELN_UNESCREST 0x08 /* Remove escape before some other character.*/
#define __FPARSELN_UNESCALL \
	(__FPARSELN_UNESCESC | __FPARSELN_UNESCCONT | __FPARSELN_UNESCCOMM | __FPARSELN_UNESCREST)

#endif /* __CRT_KOS */


/* If not supported by the CRT, then it's emulated by local headers,
 * meaning that we can unconditionally  support _all_ of the  flags! */
#ifndef __CRT_HAVE_fparseln
#if (!defined(__FPARSELN_UNESCESC) ||  \
     !defined(__FPARSELN_UNESCCONT) || \
     !defined(__FPARSELN_UNESCCOMM) || \
     !defined(__FPARSELN_UNESCREST) || \
     !defined(__FPARSELN_UNESCALL))
#undef __FPARSELN_UNESCESC
#undef __FPARSELN_UNESCCONT
#undef __FPARSELN_UNESCCOMM
#undef __FPARSELN_UNESCREST
#undef __FPARSELN_UNESCALL
#define __FPARSELN_UNESCESC  0x01 /* Remove escape before an escaped escape. */
#define __FPARSELN_UNESCCONT 0x02 /* Remove escape before an escaped continuation. */
#define __FPARSELN_UNESCCOMM 0x04 /* Remove escape before an escaped comment. */
#define __FPARSELN_UNESCREST 0x08 /* Remove escape before some other character.*/
#define __FPARSELN_UNESCALL \
	(__FPARSELN_UNESCESC | __FPARSELN_UNESCCONT | __FPARSELN_UNESCCOMM | __FPARSELN_UNESCREST)
#endif /* !defined(__FPARSELN_UNESC...) */
#endif /* !__CRT_HAVE_fparseln */


#endif /* !_ASM_CRT_UTIL_H */
