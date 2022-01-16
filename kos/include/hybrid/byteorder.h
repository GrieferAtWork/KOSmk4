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
#ifndef __GUARD_HYBRID_BYTEORDER_H
#define __GUARD_HYBRID_BYTEORDER_H 1

#include "../__stdinc.h"

#ifndef __ORDER_LITTLE_ENDIAN__
#define __ORDER_LITTLE_ENDIAN__ 1234
#endif /* !__ORDER_LITTLE_ENDIAN__ */
#ifndef __ORDER_BIG_ENDIAN__
#define __ORDER_BIG_ENDIAN__ 4321
#endif /* !__ORDER_BIG_ENDIAN__ */
#ifndef __ORDER_PDP_ENDIAN__
#define __ORDER_PDP_ENDIAN__ 3412
#endif /* !__ORDER_PDP_ENDIAN__ */

#ifndef __BYTE_ORDER__
#ifdef __BYTEORDER__
#define __BYTE_ORDER__ __BYTEORDER__
#elif defined(__BYTE_ORDER)
#define __BYTE_ORDER__ __BYTE_ORDER
#elif defined(__BYTEORDER)
#define __BYTE_ORDER__ __BYTEORDER
#elif defined(__ENDIAN__)
#define __BYTE_ORDER__ __ENDIAN__
#elif (defined(__BIG_ENDIAN__) || defined(__big_endian__) ||          \
       defined(__ARM_BIG_ENDIAN) || defined(__ARMEB__) ||             \
       defined(__MIPSEB__) || defined(_BIG_ENDIAN) ||                 \
       defined(__ckcoreBE__) || defined(__cskyBE__) ||                \
       defined(__cskybe__) || defined(__CSKYBE__) ||                  \
       defined(__MCOREBE__) || defined(__MICROBLAZEEB__) ||           \
       defined(__MIPSEB) || defined(__MIPSEB__) ||                    \
       defined(_MIPSEB) || defined(__MOXIE_BIG_ENDIAN__) ||           \
       defined(__NDS32_EB__) || defined(__nios2_big_endian) ||        \
       defined(__nios2_big_endian__) || defined(__RX_BIG_ENDIAN__) || \
       defined(__XTENSA_EB__))
#define __BYTE_ORDER__ 4321
#elif (defined(__LITTLE_ENDIAN__) || defined(__little_endian__) ||          \
       defined(__ARMEL__) || defined(__MIPSEL__) ||                         \
       defined(_LITTLE_ENDIAN) || defined(__ckcoreLE__) ||                  \
       defined(__cskyLE__) || defined(__cskyle__) ||                        \
       defined(__CSKYLE__) || defined(__LITTLEENDIAN__) ||                  \
       defined(__MCORELE__) || defined(__MICROBLAZEEL__) ||                 \
       defined(__MIPSEL) || defined(__MIPSEL__) ||                          \
       defined(_MIPSEL) || defined(__MOXIE_LITTLE_ENDIAN__) ||              \
       defined(__NDS32_EL__) || defined(__nios2_little_endian) ||           \
       defined(__nios2_little_endian__) || defined(__RX_LITTLE_ENDIAN__) || \
       defined(__XTENSA_EL__))
#define __BYTE_ORDER__ 1234
#else /* ... */
#if !defined(__NO_has_include) && !defined(__KOS_SYSTEM_HEADERS__)
#if __has_include(<endian.h>)
#include <endian.h>
#elif __has_include(<sys/endian.h>)
#include <sys/endian.h>
#elif __has_include(<machine/endian.h>)
#include <machine/endian.h>
#elif __has_include(<machine/_endian.h>)
#include <machine/_endian.h>
#endif /* ... */
#ifndef __BYTE_ORDER__
#ifdef __BYTE_ORDER
#define __BYTE_ORDER__ __BYTE_ORDER
#elif defined(_BYTE_ORDER)
#define __BYTE_ORDER__ _BYTE_ORDER
#elif defined(BYTE_ORDER)
#define __BYTE_ORDER__ BYTE_ORDER
#else /* ... */
#if __has_include(<sys/isa_defs.h>)
#include <sys/isa_defs.h>
#endif /* __has_include(<sys/isa_defs.h>) */
#if defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN) && !defined(_PDB_ENDIAN)
#define __BYTE_ORDER__ 1234
#elif !defined(_LITTLE_ENDIAN) && defined(_BIG_ENDIAN) && !defined(_PDB_ENDIAN)
#define __BYTE_ORDER__ 4321
#elif !defined(_LITTLE_ENDIAN) && !defined(_BIG_ENDIAN) && defined(_PDB_ENDIAN)
#define __BYTE_ORDER__ 3412
#endif /* ... */
#ifndef __BYTE_ORDER__
/* Can't figure out w/ system headers. -> Try to figure out from CPU macros... */
#endif /* !__BYTE_ORDER__ */
#endif /* !... */
#endif /* !__BYTE_ORDER__ */
#endif /* !__NO_has_include && !__KOS_SYSTEM_HEADERS__ */

/* Fallback: Figure out based on host defines */
#ifndef __BYTE_ORDER__
#include "host.h"
#if (defined(__arm__) && defined(ARMEB))
#define __BYTE_ORDER__ 4321
#elif (defined(__arm__) && defined(ARMEL))
#define __BYTE_ORDER__ 1234
#elif (defined(__mips__) && defined(MIPSEB))
#define __BYTE_ORDER__ 4321
#elif (defined(__mips__) && defined(MIPSEL))
#define __BYTE_ORDER__ 1234
#elif (defined(__nios2__) && defined(nios2_big_endian))
#define __BYTE_ORDER__ 1234
#elif (defined(__nios2__) && defined(nios2_little_endian))
#define __BYTE_ORDER__ 1234
#elif defined(__pdp11__)
#define __BYTE_ORDER__ 3412
#elif (defined(__hppa__) || defined(__m68k__) || \
       defined(__powerpc__) || defined(__sparc__))
#define __BYTE_ORDER__ 4321
#else /* ... */
#define __BYTE_ORDER__ 1234
#endif /* !... */
#endif /* !__BYTE_ORDER__ */
#endif /* !... */
#endif /* !__BYTE_ORDER__ */

#ifndef __FLOAT_WORD_ORDER__
#ifdef __FLOAT_WORD_ORDER
#define __FLOAT_WORD_ORDER__ __FLOAT_WORD_ORDER
#else /* __FLOAT_WORD_ORDER */
#define __FLOAT_WORD_ORDER__ __BYTE_ORDER__
#endif /* !__FLOAT_WORD_ORDER */
#endif /* !__FLOAT_WORD_ORDER__ */

#endif /* !__GUARD_HYBRID_BYTEORDER_H */
