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
#ifndef GUARD_LIBVIO_ACCESS_H
#define GUARD_LIBVIO_ACCESS_H 1

#include "api.h"
/**/

#include <kos/anno.h>
#include <kos/kernel/memory.h>
#include <kos/kernel/types.h>
#include <kos/types.h>

#include <int128.h>

#include <libvio/access.h>

DECL_BEGIN

#ifdef LIBVIO_CONFIG_ENABLED

/* VIO internal functions for dispatching operations. */

/* Invoke  VIO  callbacks, automatically  substituting operators  for one-another.
 * If an operation is impossible, these functions will throw a SEGFAULT exception.
 * @param: atomic: Throw an error if the operation cannot be performed atomically. */
INTDEF NONNULL((1)) u8  CC libvio_readb(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) u16 CC libvio_readw(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) u32 CC libvio_readl(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) void CC libvio_writeb(struct vioargs *__restrict args, vio_addr_t addr, u8  value);
INTDEF NONNULL((1)) void CC libvio_writew(struct vioargs *__restrict args, vio_addr_t addr, u16 value);
INTDEF NONNULL((1)) void CC libvio_writel(struct vioargs *__restrict args, vio_addr_t addr, u32 value);
INTDEF NONNULL((1)) u8  CC libvio_cmpxchb(struct vioargs *__restrict args, vio_addr_t addr, u8  oldvalue, u8  newvalue, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_cmpxchw(struct vioargs *__restrict args, vio_addr_t addr, u16 oldvalue, u16 newvalue, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_cmpxchl(struct vioargs *__restrict args, vio_addr_t addr, u32 oldvalue, u32 newvalue, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_cmpxch_or_writeb(struct vioargs *__restrict args, vio_addr_t addr, u8  oldvalue, u8  newvalue, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_cmpxch_or_writew(struct vioargs *__restrict args, vio_addr_t addr, u16 oldvalue, u16 newvalue, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_cmpxch_or_writel(struct vioargs *__restrict args, vio_addr_t addr, u32 oldvalue, u32 newvalue, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_xchb(struct vioargs *__restrict args, vio_addr_t addr, u8  newvalue, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_xchw(struct vioargs *__restrict args, vio_addr_t addr, u16 newvalue, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_xchl(struct vioargs *__restrict args, vio_addr_t addr, u32 newvalue, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_addb(struct vioargs *__restrict args, vio_addr_t addr, u8  value, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_addw(struct vioargs *__restrict args, vio_addr_t addr, u16 value, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_addl(struct vioargs *__restrict args, vio_addr_t addr, u32 value, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_subb(struct vioargs *__restrict args, vio_addr_t addr, u8  value, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_subw(struct vioargs *__restrict args, vio_addr_t addr, u16 value, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_subl(struct vioargs *__restrict args, vio_addr_t addr, u32 value, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_andb(struct vioargs *__restrict args, vio_addr_t addr, u8  mask, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_andw(struct vioargs *__restrict args, vio_addr_t addr, u16 mask, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_andl(struct vioargs *__restrict args, vio_addr_t addr, u32 mask, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_orb(struct vioargs *__restrict args, vio_addr_t addr, u8  mask, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_orw(struct vioargs *__restrict args, vio_addr_t addr, u16 mask, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_orl(struct vioargs *__restrict args, vio_addr_t addr, u32 mask, bool atomic);
INTDEF NONNULL((1)) u8  CC libvio_xorb(struct vioargs *__restrict args, vio_addr_t addr, u8  mask, bool atomic);
INTDEF NONNULL((1)) u16 CC libvio_xorw(struct vioargs *__restrict args, vio_addr_t addr, u16 mask, bool atomic);
INTDEF NONNULL((1)) u32 CC libvio_xorl(struct vioargs *__restrict args, vio_addr_t addr, u32 mask, bool atomic);

/* Copy memory to/from VIO, or exchange memory with VIO
 * NOTE: `oldbuf' and `newbuf' may no overlap, though with the exception that they are allowed to be identical */
INTDEF NONNULL((1)) void CC libvio_xchwithvio(struct vioargs *__restrict args, vio_addr_t offset, NCX void *oldbuf, NCX void const *newbuf, size_t num_bytes, bool atomic) THROWS(E_SEGFAULT, ...);
INTDEF NONNULL((1)) void CC libvio_copyfromvio(struct vioargs *__restrict args, vio_addr_t offset, NCX void *buf, size_t num_bytes) THROWS(E_SEGFAULT, ...);
INTDEF NONNULL((1)) void CC libvio_copytovio(struct vioargs *__restrict args, vio_addr_t offset, NCX void const *buf, size_t num_bytes) THROWS(E_SEGFAULT, ...);
INTDEF NONNULL((1)) void CC libvio_memset(struct vioargs *__restrict args, vio_addr_t offset, int byte, size_t num_bytes) THROWS(E_SEGFAULT, ...);
#ifdef __KERNEL__
INTDEF NONNULL((1)) void CC libvio_copyfromvio_to_phys(struct vioargs *__restrict args, vio_addr_t offset, physaddr_t buf, size_t num_bytes) THROWS(...);
INTDEF NONNULL((1)) void CC libvio_copytovio_from_phys(struct vioargs *__restrict args, vio_addr_t offset, physaddr_t buf, size_t num_bytes) THROWS(...);
#endif /* __KERNEL__ */

#if defined(LIBVIO_CONFIG_HAVE_QWORD) || defined(LIBVIO_CONFIG_HAVE_QWORD_CMPXCH)
INTDEF NONNULL((1)) u64 CC libvio_cmpxchq(struct vioargs *__restrict args, vio_addr_t addr, u64 oldvalue, u64 newvalue, bool atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD || LIBVIO_CONFIG_HAVE_QWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_XWORD_CMPXCH
INTDEF NONNULL((1)) uint128_t CC libvio_cmpxchx(struct vioargs *__restrict args, vio_addr_t addr, uint128_t oldvalue, uint128_t newvalue, bool atomic);
#endif /* LIBVIO_CONFIG_HAVE_XWORD_CMPXCH */
#ifdef LIBVIO_CONFIG_HAVE_QWORD
INTDEF NONNULL((1)) u64 CC libvio_cmpxch_or_writeq(struct vioargs *__restrict args, vio_addr_t addr, u64 oldvalue, u64 newvalue, bool atomic);
INTDEF NONNULL((1)) u64 CC libvio_readq(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) void CC libvio_writeq(struct vioargs *__restrict args, vio_addr_t addr, u64 value);
INTDEF NONNULL((1)) u64 CC libvio_xchq(struct vioargs *__restrict args, vio_addr_t addr, u64 newvalue, bool atomic);
INTDEF NONNULL((1)) u64 CC libvio_addq(struct vioargs *__restrict args, vio_addr_t addr, u64 value, bool atomic);
INTDEF NONNULL((1)) u64 CC libvio_subq(struct vioargs *__restrict args, vio_addr_t addr, u64 value, bool atomic);
INTDEF NONNULL((1)) u64 CC libvio_andq(struct vioargs *__restrict args, vio_addr_t addr, u64 mask, bool atomic);
INTDEF NONNULL((1)) u64 CC libvio_orq(struct vioargs *__restrict args, vio_addr_t addr, u64 mask, bool atomic);
INTDEF NONNULL((1)) u64 CC libvio_xorq(struct vioargs *__restrict args, vio_addr_t addr, u64 mask, bool atomic);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

/* Same as the function above, but these require the address to be aligned by the data type. */
INTDEF NONNULL((1)) u16 CC libvio_readw_aligned(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) u32 CC libvio_readl_aligned(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) void CC libvio_writew_aligned(struct vioargs *__restrict args, vio_addr_t addr, u16 value);
INTDEF NONNULL((1)) void CC libvio_writel_aligned(struct vioargs *__restrict args, vio_addr_t addr, u32 value);
#ifdef LIBVIO_CONFIG_HAVE_QWORD
INTDEF NONNULL((1)) u64 CC libvio_readq_aligned(struct vioargs *__restrict args, vio_addr_t addr);
INTDEF NONNULL((1)) void CC libvio_writeq_aligned(struct vioargs *__restrict args, vio_addr_t addr, u64 value);
#endif /* LIBVIO_CONFIG_HAVE_QWORD */

#define libvio_readb_aligned  libvio_readb
#define libvio_writeb_aligned libvio_writeb


#endif /* LIBVIO_CONFIG_ENABLED */

DECL_END

#endif /* !GUARD_LIBVIO_ACCESS_H */
