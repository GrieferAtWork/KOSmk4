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
/* (#) Portability: Cygwin (/newlib/libc/include/machine/_endian.h) */
/* (#) Portability: Newlib (/newlib/libc/include/machine/_endian.h) */
#ifndef _MACHINE__ENDIAN_H
#define _MACHINE__ENDIAN_H 1

#include <__stdinc.h>
#include <_ansi.h>
#include <hybrid/byteorder.h> /* __BYTE_ORDER__, __ORDER_..._ENDIAN__ */

#ifdef _SYS_ISA_DEFS_H
/*[[[warning(warn_or_error("
	Both [<machine/endian.h>, <machine/_endian.h>, <sys/endian.h>] and [<sys/isa_defs.h>]
	define the macros `_LITTLE_ENDIAN' and `_BIG_ENDIAN', however assign entirely different
	meanings (and values). - Please change your code to only include one of either
"))]]]*/
#ifndef __NO_WARNINGS
#ifdef __PREPROCESSOR_HAVE_WARNING
#warning "\
Both [<machine/endian.h>, <machine/_endian.h>, <sys/endian.h>] and [<sys/isa_defs.h>] \
define the macros `_LITTLE_ENDIAN' and `_BIG_ENDIAN', however assign entirely different \
meanings (and values). - Please change your code to only include one of either"
#elif defined(__PREPROCESSOR_HAVE_PRAGMA_WARNING)
#pragma warning("\
Both [<machine/endian.h>, <machine/_endian.h>, <sys/endian.h>] and [<sys/isa_defs.h>] \
define the macros `_LITTLE_ENDIAN' and `_BIG_ENDIAN', however assign entirely different \
meanings (and values). - Please change your code to only include one of either")
#else /* ... */
#error "\
Both [<machine/endian.h>, <machine/_endian.h>, <sys/endian.h>] and [<sys/isa_defs.h>] \
define the macros `_LITTLE_ENDIAN' and `_BIG_ENDIAN', however assign entirely different \
meanings (and values). - Please change your code to only include one of either"
#endif /* !... */
#endif /* !__NO_WARNINGS */
/*[[[end]]]*/
#endif /* _SYS_ISA_DEFS_H */

#undef _LITTLE_ENDIAN
#undef _BIG_ENDIAN
#undef _PDB_ENDIAN
#define _LITTLE_ENDIAN __ORDER_LITTLE_ENDIAN__
#define _BIG_ENDIAN    __ORDER_BIG_ENDIAN__
#define _PDP_ENDIAN    __ORDER_PDP_ENDIAN__
#ifndef _BYTE_ORDER
#define _BYTE_ORDER __BYTE_ORDER__
#endif /* !_BYTE_ORDER */
#ifndef __BYTE_ORDER
#define __BYTE_ORDER __BYTE_ORDER__
#endif /* !__BYTE_ORDER */

#endif /* !_MACHINE__ENDIAN_H */
