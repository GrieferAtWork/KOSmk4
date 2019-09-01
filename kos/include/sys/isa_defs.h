/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef _SYS_ISA_DEFS_H
#define _SYS_ISA_DEFS_H 1

#include <__stdinc.h>
#include <hybrid/__byteorder.h>
#include <hybrid/typecore.h>
#include <hybrid/limitcore.h>
#include <hybrid/host.h>

/* This header is documented here:
 * http://www.sde.cs.titech.ac.jp/~gondow/dwarf2-xml/HTML-rxref/usr/include/sys/isa_defs.h.html
 * I would copy the documentation, but I don't think
 * the source's copyright allows that... */


#ifdef _MACHINE__ENDIAN_H
#ifndef __NO_WARNINGS
#warning "\
Both <machine/endian.h> (<machine/_endian.h>) and <sys/isa_defs.h> define the \
macros `_LITTLE_ENDIAN' and `_BIG_ENDIAN', however assign entirely different \
meanings (and values). - Please change your code to only include one of either"
#endif /* !__NO_WARNINGS */
#endif

#undef _LITTLE_ENDIAN
#undef _BIG_ENDIAN
#undef _PDB_ENDIAN
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _LITTLE_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define _BIG_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define _PDB_ENDIAN 1
#endif

#if !defined(_STACK_GROWS_DOWNWARD) && \
    !defined(_STACK_GROWS_UPWARD)
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define _STACK_GROWS_DOWNWARD 1
#else
#define _STACK_GROWS_UPWARD 1
#endif
#endif


#if !defined(_LONG_LONG_LTOH) && !defined(_LONG_LONG_HTOL)
#ifdef _LITTLE_ENDIAN
#define _LONG_LONG_LTOH 1
#else
#define _LONG_LONG_HTOL 1
#endif
#endif

#if !defined(_BIT_FIELDS_HTOL) && !defined(_BIT_FIELDS_LTOH)
#define _BIT_FIELDS_LTOH 1
#endif


#ifndef _IEEE_754
#define _IEEE_754
#endif /* !_IEEE_754 */

#if !defined(_CHAR_IS_UNSIGNED) && !defined(_CHAR_IS_SIGNED)
#ifdef __CHAR_UNSIGNED__
#define _CHAR_IS_UNSIGNED 1
#else
#define _CHAR_IS_SIGNED 1
#endif
#endif

#ifndef _CHAR_ALIGNMENT
#define _CHAR_ALIGNMENT  __SIZEOF_CHAR__
#endif /* !_CHAR_ALIGNMENT */

#ifndef _SHORT_ALIGNMENT
#define _SHORT_ALIGNMENT __SIZEOF_SHORT__
#endif /* !_SHORT_ALIGNMENT */

#ifndef _INT_ALIGNMENT
#define _INT_ALIGNMENT  __SIZEOF_INT__
#endif /* !_INT_ALIGNMENT */

#ifndef _LONG_ALIGNMENT
#define _LONG_ALIGNMENT  __SIZEOF_LONG__
#endif /* !_LONG_ALIGNMENT */

#ifndef _LONG_LONG_ALIGNMENT
#define _LONG_LONG_ALIGNMENT __SIZEOF_LONG_LONG__
#endif /* !_LONG_LONG_ALIGNMENT */

#ifndef _DOUBLE_ALIGNMENT
#define _DOUBLE_ALIGNMENT __SIZEOF_DOUBLE__
#endif /* !_DOUBLE_ALIGNMENT */

#ifndef _LONG_DOUBLE_ALIGNMENT
#define _LONG_DOUBLE_ALIGNMENT __SIZEOF_LONG_DOUBLE__
#endif /* !_LONG_DOUBLE_ALIGNMENT */

#ifndef _POINTER_ALIGNMENT
#define _POINTER_ALIGNMENT __SIZEOF_POINTER__
#endif /* !_POINTER_ALIGNMENT */

#ifndef _MAX_ALIGNMENT
#define _MAX_ALIGNMENT __ALIGNOF_MAX_ALIGN_T__
#endif /* !_MAX_ALIGNMENT */

#ifndef _ALIGNMENT_REQUIRED
#ifdef __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS
#define _ALIGNMENT_REQUIRED 0
#else /* __ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#define _ALIGNMENT_REQUIRED 1
#endif /* !__ARCH_HAVE_UNALIGNED_MEMORY_ACCESS */
#endif /* !_ALIGNMENT_REQUIRED */


#if !defined(_ILP32) && defined(__ILP32__)
#define _ILP32 1
#endif

#if !defined(_LP64) && defined(__LP64__)
#define _LP64 1
#endif

#if !defined(_I32LPx) && defined(___I32LPx__)
#define _I32LPx 1
#endif


/* I get all of the other options, but from this point on, it gets _extremely_ specific.
 * And even more though: This really doesn't have too much to do with the arch ISA anymore...
 * (Well... DMA addressing maybe, but not that fdisk/console stuff further below!) */
#undef _DMA_USES_PHYSADDR
#undef _DMA_USES_VIRTADDR
#if defined(__i386__) || defined(__x86_64__)
#define _DMA_USES_PHYSADDR 1
#endif

/* Cannot be determined at compile-time (I mean: how could you even determine this?) */
#undef _FIRMWARE_NEEDS_FDISK
#undef _NO_FDISK_PRESENT

/* Again: this is device-dependent and what would knowing this even acomplish? */
#undef _CONSOLE_OUTPUT_VIA_FIRMWARE
#undef _CONSOLE_OUTPUT_VIA_SOFTWARE


#endif /* !_SYS_ISA_DEFS_H */
