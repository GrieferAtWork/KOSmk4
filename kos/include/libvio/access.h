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
#ifndef _LIBVIO_ACCESS_H
#define _LIBVIO_ACCESS_H 1

#include "api.h"
/**/

#include <bits/types.h>
#include <kos/anno.h>

#include "vio.h"

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#include <hybrid/int128.h>
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

#ifdef __CC__
__DECL_BEGIN

/* VIO internal functions for dispatching operations. */

/* Invoke  VIO  callbacks, automatically  substituting operators  for one-another.
 * If an operation is impossible, these functions will throw a SEGFAULT exception.
 * @param: atomic: Throw an error if the operation cannot be performed atomically. */
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_READB)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_READW)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_READL)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  value) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_CMPXCHB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_CMPXCHW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_CMPXCHL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_XCHB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_XCHW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_XCHL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_ADDB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_ADDW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_ADDL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_SUBB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_SUBW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_SUBL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_ANDB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_ANDW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_ANDL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_ORB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_ORW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_ORL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint8_t  (LIBVIO_CC *PVIO_XORB)(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_XORW)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_XORL)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_readb(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_readw(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_readl(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writeb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writew(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writel(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_cmpxchb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_cmpxchw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_cmpxchl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_cmpxch_or_writeb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_cmpxch_or_writew(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_cmpxch_or_writel(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_xchb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_xchw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_xchl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_addb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_addw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_addl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_subb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_subw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_subl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_andb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_andw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_andl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_orb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_orw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_orl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_xorb(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_xorw(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_xorl(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_WANT_PROTOTYPES */

/* Copy memory to/from VIO, or exchange memory with VIO
 * NOTE: `oldbuf' and `newbuf' may no overlap, though with the exception that they are allowed to be identical */
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_XCHWITHVIO)(struct vioargs *__restrict args, vio_addr_t offset, __USER __CHECKED void *oldbuf, __USER __CHECKED void const *newbuf, __size_t num_bytes, __BOOL atomic) /*__THROWS(E_SEGFAULT, ...)*/;
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_COPYFROMVIO)(struct vioargs *__restrict args, vio_addr_t offset, __USER __CHECKED void *buf, __size_t num_bytes) /*__THROWS(E_SEGFAULT, ...)*/;
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_COPYTOVIO)(struct vioargs *__restrict args, vio_addr_t offset, __USER __CHECKED void const *buf, __size_t num_bytes) /*__THROWS(E_SEGFAULT, ...)*/;
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_MEMSET)(struct vioargs *__restrict args, vio_addr_t offset, int byte, __size_t num_bytes) /*__THROWS(E_SEGFAULT, ...)*/;
#ifdef __KERNEL__
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_COPYFROMVIO_TO_PHYS)(struct vioargs *__restrict args, vio_addr_t offset, __physaddr_t buf, __size_t num_bytes) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_COPYTOVIO_FROM_PHYS)(struct vioargs *__restrict args, vio_addr_t offset, __physaddr_t buf, __size_t num_bytes) __THROWS(...);
#endif /* __KERNEL__ */
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_xchwithvio(struct vioargs *__restrict args, vio_addr_t offset, __USER __CHECKED void *oldbuf, __USER __CHECKED void const *newbuf, __size_t num_bytes, __BOOL atomic) __THROWS(E_SEGFAULT, ...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copyfromvio(struct vioargs *__restrict args, vio_addr_t offset, __USER __CHECKED void *buf, __size_t num_bytes) __THROWS(E_SEGFAULT, ...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copytovio(struct vioargs *__restrict args, vio_addr_t offset, __USER __CHECKED void const *buf, __size_t num_bytes) __THROWS(E_SEGFAULT, ...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_memset(struct vioargs *__restrict args, vio_addr_t offset, int byte, __size_t num_bytes) __THROWS(E_SEGFAULT, ...);
#ifdef __KERNEL__
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copyfromvio_to_phys(struct vioargs *__restrict args, vio_addr_t offset, __physaddr_t buf, __size_t num_bytes) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copytovio_from_phys(struct vioargs *__restrict args, vio_addr_t offset, __physaddr_t buf, __size_t num_bytes) __THROWS(...);
#endif /* __KERNEL__ */
#endif /* LIBVIO_WANT_PROTOTYPES */

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_CMPXCHQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
typedef __ATTR_NONNULL_T((1)) __hybrid_uint128_t (LIBVIO_CC *PVIO_CMPXCHX)(struct vioargs *__restrict args, vio_addr_t addr, __hybrid_uint128_t oldvalue, __hybrid_uint128_t newvalue, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_READQ)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_XCHQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t newvalue, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_ADDQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_SUBQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_ANDQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_ORQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_XORQ)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#ifdef LIBVIO_WANT_PROTOTYPES
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_cmpxchq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
LIBVIO_DECL __ATTR_NONNULL((1)) __hybrid_uint128_t LIBVIO_CC vio_cmpxchx(struct vioargs *__restrict args, vio_addr_t addr, __hybrid_uint128_t oldvalue, __hybrid_uint128_t newvalue, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_cmpxch_or_writeq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_readq(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writeq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_xchq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_addq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_subq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_andq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_orq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_xorq(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t mask, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#endif /* LIBVIO_WANT_PROTOTYPES */

/* Same as the function above, but these require the address to be aligned by the data type. */
typedef __ATTR_NONNULL_T((1)) __uint16_t (LIBVIO_CC *PVIO_READW_ALIGNED)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) __uint32_t (LIBVIO_CC *PVIO_READL_ALIGNED)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEW_ALIGNED)(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEL_ALIGNED)(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value) __THROWS(...);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
typedef __ATTR_NONNULL_T((1)) __uint64_t (LIBVIO_CC *PVIO_READQ_ALIGNED)(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
typedef __ATTR_NONNULL_T((1)) void (LIBVIO_CC *PVIO_WRITEQ_ALIGNED)(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#ifdef LIBVIO_WANT_PROTOTYPES
__COMPILER_REDIRECT(LIBVIO_DECL,__ATTR_NONNULL((1)),__uint8_t,__THROWING,LIBVIO_CC,vio_readb_aligned,(struct vioargs *__restrict args, vio_addr_t addr),vio_readb,(args,addr))
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_readw_aligned(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_readl_aligned(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
__COMPILER_REDIRECT_VOID(LIBVIO_DECL,__ATTR_NONNULL((1)),__THROWING,LIBVIO_CC,vio_writeb_aligned,(struct vioargs *__restrict args, vio_addr_t addr, __uint8_t value),vio_writeb,(args,addr,value))
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writew_aligned(struct vioargs *__restrict args, vio_addr_t addr, __uint16_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writel_aligned(struct vioargs *__restrict args, vio_addr_t addr, __uint32_t value) __THROWS(...);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_readq_aligned(struct vioargs *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writeq_aligned(struct vioargs *__restrict args, vio_addr_t addr, __uint64_t value) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#endif /* LIBVIO_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIO_ACCESS_H */
