/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: OpenSolaris (/usr/src/uts/common/sys/isa_defs.h) */
#ifndef _SYS_ISA_DEFS_H
#define _SYS_ISA_DEFS_H 1

#include <__stdinc.h>

#include <hybrid/byteorder.h>
#include <hybrid/host.h>
#include <hybrid/limitcore.h>
#include <hybrid/typecore.h>

/* This header is documented here:
 * http://www.sde.cs.titech.ac.jp/~gondow/dwarf2-xml/HTML-rxref/usr/include/sys/isa_defs.h.html
 * I would copy the documentation, but I don't think
 * the source's copyright allows that... */

#if defined(_MACHINE__ENDIAN_H) || defined(_SYS_ENDIAN_H)
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
#endif /* _MACHINE__ENDIAN_H || _SYS_ENDIAN_H */

#undef _LITTLE_ENDIAN
#undef _BIG_ENDIAN
#undef _PDB_ENDIAN
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define _LITTLE_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define _BIG_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define _PDB_ENDIAN 1
#endif /* __BYTE_ORDER__ == ... */

#if (!defined(_STACK_GROWS_DOWNWARD) && !defined(_STACK_GROWS_UPWARD))
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#define _STACK_GROWS_DOWNWARD 1
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#define _STACK_GROWS_UPWARD 1
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
#endif /* !_STACK_GROWS_DOWNWARD && !_STACK_GROWS_UPWARD */


#if !defined(_LONG_LONG_LTOH) && !defined(_LONG_LONG_HTOL)
#ifdef _LITTLE_ENDIAN
#define _LONG_LONG_LTOH 1
#else /* _LITTLE_ENDIAN */
#define _LONG_LONG_HTOL 1
#endif /* !_LITTLE_ENDIAN */
#endif /* !_LONG_LONG_LTOH && !_LONG_LONG_HTOL */

#if !defined(_BIT_FIELDS_HTOL) && !defined(_BIT_FIELDS_LTOH)
#define _BIT_FIELDS_LTOH 1
#endif /* !_BIT_FIELDS_HTOL && !_BIT_FIELDS_LTOH */


#ifndef _IEEE_754
#include <ieee754.h>
/* Define `_IEEE_754' if all of `float', `double' (and if
 * defined by the  compiler `long double')  map to  types
 * that are compatible with the `ieee[78]54' standard. */
#if ((defined(__IEEE754_FLOAT_TYPE_IS_FLOAT__) ||         \
      defined(__IEEE754_DOUBLE_TYPE_IS_FLOAT__) ||        \
      defined(__IEEE854_LONG_DOUBLE_TYPE_IS_FLOAT__)) &&  \
     (defined(__IEEE754_FLOAT_TYPE_IS_DOUBLE__) ||        \
      defined(__IEEE754_DOUBLE_TYPE_IS_DOUBLE__) ||       \
      defined(__IEEE854_LONG_DOUBLE_TYPE_IS_DOUBLE__)) && \
     (!defined(__COMPILER_HAVE_LONGDOUBLE) ||             \
      defined(__IEEE754_FLOAT_TYPE_IS_LONG_DOUBLE__) ||   \
      defined(__IEEE754_DOUBLE_TYPE_IS_LONG_DOUBLE__) ||  \
      defined(__IEEE854_LONG_DOUBLE_TYPE_IS_LONG_DOUBLE__)))
#define _IEEE_754 1
#endif /* ... */
#endif /* !_IEEE_754 */

#if !defined(_CHAR_IS_UNSIGNED) && !defined(_CHAR_IS_SIGNED)
#ifdef __CHAR_UNSIGNED__
#define _CHAR_IS_UNSIGNED 1
#else /* __CHAR_UNSIGNED__ */
#define _CHAR_IS_SIGNED 1
#endif /* !__CHAR_UNSIGNED__ */
#endif /* !_CHAR_IS_UNSIGNED && !_CHAR_IS_SIGNED */

#ifndef _CHAR_ALIGNMENT
#define _CHAR_ALIGNMENT __ALIGNOF_CHAR__
#endif /* !_CHAR_ALIGNMENT */

#ifndef _SHORT_ALIGNMENT
#define _SHORT_ALIGNMENT __ALIGNOF_SHORT__
#endif /* !_SHORT_ALIGNMENT */

#ifndef _INT_ALIGNMENT
#define _INT_ALIGNMENT __ALIGNOF_INT__
#endif /* !_INT_ALIGNMENT */

#ifndef _LONG_ALIGNMENT
#define _LONG_ALIGNMENT __ALIGNOF_LONG__
#endif /* !_LONG_ALIGNMENT */

#if !defined(_LONG_LONG_ALIGNMENT) && defined(__ALIGNOF_LONG_LONG__)
#define _LONG_LONG_ALIGNMENT __ALIGNOF_LONG_LONG__
#endif /* !_LONG_LONG_ALIGNMENT && __ALIGNOF_LONG_LONG__ */

#if !defined(_DOUBLE_ALIGNMENT) && defined(__ALIGNOF_DOUBLE__)
#define _DOUBLE_ALIGNMENT __ALIGNOF_DOUBLE__
#endif /* !_DOUBLE_ALIGNMENT && __ALIGNOF_DOUBLE__ */

#if !defined(_LONG_DOUBLE_ALIGNMENT) && defined(__ALIGNOF_LONG_DOUBLE__)
#define _LONG_DOUBLE_ALIGNMENT __ALIGNOF_LONG_DOUBLE__
#endif /* !_LONG_DOUBLE_ALIGNMENT && __ALIGNOF_LONG_DOUBLE__ */

#ifndef _POINTER_ALIGNMENT
#define _POINTER_ALIGNMENT __ALIGNOF_POINTER__
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


#if !defined(_ILP32) && (defined(__ILP32__) || (__SIZEOF_INT__ == 4 && __SIZEOF_LONG__ == 4 && __SIZEOF_POINTER__ == 4))
#define _ILP32 1
#endif /* _ILP32... */

#if !defined(_LP64) && (defined(__LP64__) || (__SIZEOF_LONG__ == 8 && __SIZEOF_POINTER__ == 8))
#define _LP64 1
#endif /* _LP64... */

#if !defined(_I32LPx) && (defined(___I32LPx__) || (__SIZEOF_INT__ == 4 && __SIZEOF_LONG__ == __SIZEOF_POINTER__))
#define _I32LPx 1
#endif /* _I32LPx... */



/* I get all  of the other  options, but from  this point on,  it gets _extremely_  specific.
 * And even more though: This really doesn't have too much to do with the arch ISA anymore...
 * (Well... DMA addressing maybe, but not that fdisk/console stuff further below!) */
#undef _DMA_USES_PHYSADDR
#undef _DMA_USES_VIRTADDR
#if defined(__i386__) || defined(__x86_64__)
#define _DMA_USES_PHYSADDR 1
#endif /* __i386__ || __x86_64__ */

/* Cannot be determined at compile-time (I mean: how could you even determine this?) */
#undef _FIRMWARE_NEEDS_FDISK
#undef _NO_FDISK_PRESENT

/* Again: this is device-dependent and what would knowing this even accomplish? */
#undef _CONSOLE_OUTPUT_VIA_FIRMWARE
#undef _CONSOLE_OUTPUT_VIA_SOFTWARE


#endif /* !_SYS_ISA_DEFS_H */
