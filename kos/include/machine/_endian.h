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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _MACHINE__ENDIAN_H
#define _MACHINE__ENDIAN_H 1

#include <__stdinc.h>
#include <_ansi.h>
#include <bits/endian.h>

#ifdef _SYS_ISA_DEFS_H
#warning "\
Both <machine/endian.h> (<machine/_endian.h>) and <sys/isa_defs.h> define the \
macros `_LITTLE_ENDIAN' and `_BIG_ENDIAN', however assign entirely different \
meanings (and values). - Please change your code to only include one of either"
#endif

#undef _LITTLE_ENDIAN
#undef _BIG_ENDIAN
#undef _PDB_ENDIAN
#define _LITTLE_ENDIAN __LITTLE_ENDIAN__
#define _BIG_ENDIAN    __ORDER_BIG_ENDIAN__
#define _PDP_ENDIAN    __ORDER_PDP_ENDIAN__
#define _BYTE_ORDER    __BYTE_ORDER__

#endif /* !_MACHINE__ENDIAN_H */
