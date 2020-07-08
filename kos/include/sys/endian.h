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
#ifndef _SYS_ENDIAN_H
#define _SYS_ENDIAN_H 1

#include <__stdinc.h>

#include <hybrid/__byteorder.h>
#include <hybrid/__unaligned.h>
#include <hybrid/typecore.h>

#include <endian.h>

#ifdef _SYS_ISA_DEFS_H
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

/* Helper functions to encode/decode fixed-width integers using explicit endian */
#ifdef __CC__
#ifdef __INTELLISENSE__
__DECL_BEGIN
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(be16dec)(const void *__pp);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(be32dec)(const void *__pp);
#ifdef __hybrid_unaligned_getbe64
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(be64dec)(const void *__pp);
#endif /* __hybrid_unaligned_getbe64 */
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT16_TYPE__ __NOTHROW_NCX(le16dec)(const void *__pp);
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT32_TYPE__ __NOTHROW_NCX(le32dec)(const void *__pp);
#ifdef __hybrid_unaligned_getle64
__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __UINT64_TYPE__ __NOTHROW_NCX(le64dec)(const void *__pp);
#endif /* __hybrid_unaligned_getle64 */
__ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(be16enc)(void *__pp, __UINT16_TYPE__ __val);
__ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(be32enc)(void *__pp, __UINT32_TYPE__ __val);
#ifdef __hybrid_unaligned_setbe64
__ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(be64enc)(void *__pp, __UINT64_TYPE__ __val);
#endif /* __hybrid_unaligned_setbe64 */
__ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(le16enc)(void *__pp, __UINT16_TYPE__ __val);
__ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(le32enc)(void *__pp, __UINT32_TYPE__ __val);
#ifdef __hybrid_unaligned_setle64
__ATTR_LEAF __ATTR_NONNULL((1)) void __NOTHROW_NCX(le64enc)(void *__pp, __UINT64_TYPE__ __val);
#endif /* __hybrid_unaligned_setle64 */
__DECL_END
#else /* __INTELLISENSE__ */
#define be16dec(pp) __hybrid_unaligned_getbe16(pp)
#define be32dec(pp) __hybrid_unaligned_getbe32(pp)
#ifdef __hybrid_unaligned_getbe64
#define be64dec(pp) __hybrid_unaligned_getbe64(pp)
#endif /* __hybrid_unaligned_getbe64 */
#define le16dec(pp) __hybrid_unaligned_getle16(pp)
#define le32dec(pp) __hybrid_unaligned_getle32(pp)
#ifdef __hybrid_unaligned_getle64
#define le64dec(pp) __hybrid_unaligned_getle64(pp)
#endif /* __hybrid_unaligned_getle64 */
#define be16enc(pp, val) __hybrid_unaligned_setbe16(pp, val)
#define be32enc(pp, val) __hybrid_unaligned_setbe32(pp, val)
#ifdef __hybrid_unaligned_setbe64
#define be64enc(pp, val) __hybrid_unaligned_setbe64(pp, val)
#endif /* __hybrid_unaligned_setbe64 */
#define le16enc(pp, val) __hybrid_unaligned_setle16(pp, val)
#define le32enc(pp, val) __hybrid_unaligned_setle32(pp, val)
#ifdef __hybrid_unaligned_setle64
#define le64enc(pp, val) __hybrid_unaligned_setle64(pp, val)
#endif /* __hybrid_unaligned_setle64 */
#endif /* !__INTELLISENSE__ */
#endif /* __CC__ */


#endif /* !_SYS_ENDIAN_H */
