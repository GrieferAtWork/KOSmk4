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
#ifndef _LIBVIO_ACCESS_H
#define _LIBVIO_ACCESS_H 1

#include "api.h"

#include <kos/anno.h>

#include "vio.h"

#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
#include <hybrid/int128.h>
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */

#ifdef __KERNEL__
#include <kos/bits/types.h>
#endif /* __KERNEL__ */

#ifdef __CC__
__DECL_BEGIN

/* VIO internal functions for dispatching operations. */

/* Invoke VIO callbacks, automatically substituting operators for one-another.
 * If an operation is impossible, these functions will throw a SEGFAULT exception.
 * @param: atomic: Throw an error if the operation cannot be performed atomically. */
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_READB)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_READW)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_READL)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  value) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_CMPXCHB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_CMPXCHW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_CMPXCHL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_XCHB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_XCHW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_XCHL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t newvalue, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_ADDB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_ADDW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_ADDL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_SUBB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_SUBW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_SUBL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_ANDB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_ANDW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_ANDL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_ORB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_ORW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_ORL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint8_t  (LIBVIO_CC *PVIO_XORB)(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_XORW)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_XORL)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) /*__THROWS(...)*/;
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_readb(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_readw(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_readl(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writeb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writew(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writel(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_cmpxchb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_cmpxchw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_cmpxchl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_cmpxch_or_writeb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  oldvalue, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_cmpxch_or_writew(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t oldvalue, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_cmpxch_or_writel(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t oldvalue, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_xchb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_xchw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_xchl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t newvalue, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_addb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_addw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_addl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_subb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_subw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_subl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_andb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_andw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_andl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_orb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_orw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_orl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint8_t  LIBVIO_CC vio_xorb(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t  mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_xorw(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t mask, __BOOL atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_xorl(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t mask, __BOOL atomic) __THROWS(...);
#endif /* LIBVIO_WANT_PROTOTYPES */

/* Copy memory to/from VIO */
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_COPYFROMVIO)(struct vio_args *__restrict args, vio_addr_t offset, __USER __CHECKED void *buf, __size_t num_bytes) /*__THROWS(E_SEGFAULT, ...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_COPYTOVIO)(struct vio_args *__restrict args, vio_addr_t offset, __USER __CHECKED void const *buf, __size_t num_bytes) /*__THROWS(E_SEGFAULT, ...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_MEMSET)(struct vio_args *__restrict args, vio_addr_t offset, int byte, __size_t num_bytes) /*__THROWS(E_SEGFAULT, ...)*/;
#ifdef __KERNEL__
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_COPYFROMVIO_TO_PHYS)(struct vio_args *__restrict args, vio_addr_t offset, __vm_phys_t buf, __size_t num_bytes) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_COPYTOVIO_FROM_PHYS)(struct vio_args *__restrict args, vio_addr_t offset, __vm_phys_t buf, __size_t num_bytes) /*__THROWS(...)*/;
#endif /* __KERNEL__ */
#ifdef LIBVIO_WANT_PROTOTYPES
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copyfromvio(struct vio_args *__restrict args, vio_addr_t offset, __USER __CHECKED void *buf, __size_t num_bytes) __THROWS(E_SEGFAULT, ...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copytovio(struct vio_args *__restrict args, vio_addr_t offset, __USER __CHECKED void const *buf, __size_t num_bytes) __THROWS(E_SEGFAULT, ...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_memset(struct vio_args *__restrict args, vio_addr_t offset, int byte, __size_t num_bytes) __THROWS(E_SEGFAULT, ...);
#ifdef __KERNEL__
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copyfromvio_to_phys(struct vio_args *__restrict args, vio_addr_t offset, __vm_phys_t buf, __size_t num_bytes) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_copytovio_from_phys(struct vio_args *__restrict args, vio_addr_t offset, __vm_phys_t buf, __size_t num_bytes) __THROWS(...);
#endif /* __KERNEL__ */
#endif /* LIBVIO_WANT_PROTOTYPES */

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_CMPXCHQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, bool atomic) /*__THROWS(...)*/;
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
typedef __ATTR_NONNULL((1)) __hybrid_uint128_t (LIBVIO_CC *PVIO_CMPXCHX)(struct vio_args *__restrict args, vio_addr_t addr, __hybrid_uint128_t oldvalue, __hybrid_uint128_t newvalue, bool atomic) /*__THROWS(...)*/;
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_CMPXCH_OR_WRITEQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, bool atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_READQ)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_XCHQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t newvalue, bool atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_ADDQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value, bool atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_SUBQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value, bool atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_ANDQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t mask, bool atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_ORQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t mask, bool atomic) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_XORQ)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t mask, bool atomic) /*__THROWS(...)*/;
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#ifdef LIBVIO_WANT_PROTOTYPES
#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_cmpxchq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, bool atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
LIBVIO_DECL __ATTR_NONNULL((1)) __hybrid_uint128_t LIBVIO_CC vio_cmpxchx(struct vio_args *__restrict args, vio_addr_t addr, __hybrid_uint128_t oldvalue, __hybrid_uint128_t newvalue, bool atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_cmpxch_or_writeq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t oldvalue, __uint64_t newvalue, bool atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_readq(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writeq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_xchq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t newvalue, bool atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_addq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value, bool atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_subq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value, bool atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_andq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t mask, bool atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_orq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t mask, bool atomic) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_xorq(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t mask, bool atomic) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#endif /* LIBVIO_WANT_PROTOTYPES */

/* Same as the function above, but these require the address to be aligned by the data type. */
typedef __ATTR_NONNULL((1)) __uint16_t (LIBVIO_CC *PVIO_READW_ALIGNED)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) __uint32_t (LIBVIO_CC *PVIO_READL_ALIGNED)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEW_ALIGNED)(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEL_ALIGNED)(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value) /*__THROWS(...)*/;
#ifdef LIBVIO_CONFIG_HAVE_QWORD
typedef __ATTR_NONNULL((1)) __uint64_t (LIBVIO_CC *PVIO_READQ_ALIGNED)(struct vio_args *__restrict args, vio_addr_t addr) /*__THROWS(...)*/;
typedef __ATTR_NONNULL((1)) void (LIBVIO_CC *PVIO_WRITEQ_ALIGNED)(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value) /*__THROWS(...)*/;
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#ifdef LIBVIO_WANT_PROTOTYPES
__COMPILER_REDIRECT(LIBVIO_DECL,__ATTR_NONNULL((1)),__uint8_t,__THROWING,LIBVIO_CC,vio_readb_aligned,(struct vio_args *__restrict args, vio_addr_t addr),vio_readb,(args,addr))
LIBVIO_DECL __ATTR_NONNULL((1)) __uint16_t LIBVIO_CC vio_readw_aligned(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) __uint32_t LIBVIO_CC vio_readl_aligned(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
__COMPILER_REDIRECT_VOID(LIBVIO_DECL,__ATTR_NONNULL((1)),__THROWING,LIBVIO_CC,vio_writeb_aligned,(struct vio_args *__restrict args, vio_addr_t addr, __uint8_t value),vio_writeb,(args,addr,value))
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writew_aligned(struct vio_args *__restrict args, vio_addr_t addr, __uint16_t value) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writel_aligned(struct vio_args *__restrict args, vio_addr_t addr, __uint32_t value) __THROWS(...);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
LIBVIO_DECL __ATTR_NONNULL((1)) __uint64_t LIBVIO_CC vio_readq_aligned(struct vio_args *__restrict args, vio_addr_t addr) __THROWS(...);
LIBVIO_DECL __ATTR_NONNULL((1)) void LIBVIO_CC vio_writeq_aligned(struct vio_args *__restrict args, vio_addr_t addr, __uint64_t value) __THROWS(...);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */
#endif /* LIBVIO_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBVIO_ACCESS_H */
