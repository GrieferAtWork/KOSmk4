/* HASH CRC-32:0xe2d870c2 */
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
#ifndef _KOS_NOPF_H
#define _KOS_NOPF_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <kos/bits/nopf.h>
#include <kos/anno.h>

#ifdef __CC__
__SYSDECL_BEGIN

/* Define nopf functions not already defined in `<kos/bits/nopf.h>' */

#if !defined(__memeq_nopf_defined) && defined(__CRT_HAVE_memeq_nopf)
#define __memeq_nopf_defined
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INS(1, 3) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW,memeq_nopf,(void const *__lhs, void const *__rhs, __SIZE_TYPE__ __num_bytes),(__lhs,__rhs,__num_bytes))
#endif /* !__memeq_nopf_defined && __CRT_HAVE_memeq_nopf */
#if !defined(__readb_nopf_defined) && defined(__CRT_HAVE_readb_nopf)
#define __readb_nopf_defined
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_NONNULL((2)),__BOOL,__NOTHROW,readb_nopf,(void const *__addr, __UINT8_TYPE__ *__presult),(__addr,__presult))
#endif /* !__readb_nopf_defined && __CRT_HAVE_readb_nopf */
#if !defined(__readw_nopf_defined) && defined(__CRT_HAVE_readw_nopf)
#define __readw_nopf_defined
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_NONNULL((2)),__BOOL,__NOTHROW,readw_nopf,(void const *__addr, __UINT16_TYPE__ *__presult),(__addr,__presult))
#endif /* !__readw_nopf_defined && __CRT_HAVE_readw_nopf */
#if !defined(__readl_nopf_defined) && defined(__CRT_HAVE_readl_nopf)
#define __readl_nopf_defined
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_NONNULL((2)),__BOOL,__NOTHROW,readl_nopf,(void const *__addr, __UINT32_TYPE__ *__presult),(__addr,__presult))
#endif /* !__readl_nopf_defined && __CRT_HAVE_readl_nopf */
#if !defined(__readq_nopf_defined) && defined(__CRT_HAVE_readq_nopf)
#define __readq_nopf_defined
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_NONNULL((2)),__BOOL,__NOTHROW,readq_nopf,(void const *__addr, __UINT64_TYPE__ *__presult),(__addr,__presult))
#endif /* !__readq_nopf_defined && __CRT_HAVE_readq_nopf */
#if !defined(__writeb_nopf_defined) && defined(__CRT_HAVE_writeb_nopf)
#define __writeb_nopf_defined
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writeb_nopf,(void *__addr, __UINT8_TYPE__ __val),(__addr,__val))
#endif /* !__writeb_nopf_defined && __CRT_HAVE_writeb_nopf */
#if !defined(__writew_nopf_defined) && defined(__CRT_HAVE_writew_nopf)
#define __writew_nopf_defined
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writew_nopf,(void *__addr, __UINT16_TYPE__ __val),(__addr,__val))
#endif /* !__writew_nopf_defined && __CRT_HAVE_writew_nopf */
#if !defined(__writel_nopf_defined) && defined(__CRT_HAVE_writel_nopf)
#define __writel_nopf_defined
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writel_nopf,(void *__addr, __UINT32_TYPE__ __val),(__addr,__val))
#endif /* !__writel_nopf_defined && __CRT_HAVE_writel_nopf */
#if !defined(__writeq_nopf_defined) && defined(__CRT_HAVE_writeq_nopf)
#define __writeq_nopf_defined
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writeq_nopf,(void *__addr, __UINT64_TYPE__ __val),(__addr,__val))
#endif /* !__writeq_nopf_defined && __CRT_HAVE_writeq_nopf */
#if !defined(__memcpy_nopf_defined) && defined(__CRT_HAVE_memcpy_nopf)
#define __memcpy_nopf_defined
/* >> memcpy_nopf(3)
 * Copy memory from `src' to `dst', but  stop if any sort of #PF  happens,
 * regardless of that #PF being handleable or not (aka: load-on-access, or
 * copy-on-write  will never be  triggered by this  function, and the same
 * also goes for VIO)
 * This function can be used to copy user-space memory whilst holding  an
 * atomic lock, allowing the caller to handle the PF by handling the next
 * data byte/word/etc. individually after releasing the atomic lock, thus
 * allowing a necessary #PF to run its course without the caller  holding
 * an atomic lock.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory ranges are:
 *               - `dst + num_bytes - return ... dst + num_bytes - 1'
 *               - `src + num_bytes - return ... src + num_bytes - 1' */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INS(2, 3) __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW,memcpy_nopf,(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes),(__dst,__src,__num_bytes))
#endif /* !__memcpy_nopf_defined && __CRT_HAVE_memcpy_nopf */
#if !defined(__memset_nopf_defined) && defined(__CRT_HAVE_memset_nopf)
#define __memset_nopf_defined
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW,memset_nopf,(void *__dst, int __byte, __SIZE_TYPE__ __num_bytes),(__dst,__byte,__num_bytes))
#endif /* !__memset_nopf_defined && __CRT_HAVE_memset_nopf */
#if !defined(__atomic_xchb_nopf_defined) && defined(__CRT_HAVE_atomic_xchb_nopf)
#define __atomic_xchb_nopf_defined
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_xchb_nopf,(void const *__addr, __UINT8_TYPE__ __newval, __UINT8_TYPE__ *__poldval),(__addr,__newval,__poldval))
#endif /* !__atomic_xchb_nopf_defined && __CRT_HAVE_atomic_xchb_nopf */
#if !defined(__atomic_xchw_nopf_defined) && defined(__CRT_HAVE_atomic_xchw_nopf)
#define __atomic_xchw_nopf_defined
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_xchw_nopf,(void const *__addr, __UINT16_TYPE__ __newval, __UINT16_TYPE__ *__poldval),(__addr,__newval,__poldval))
#endif /* !__atomic_xchw_nopf_defined && __CRT_HAVE_atomic_xchw_nopf */
#if !defined(__atomic_xchl_nopf_defined) && defined(__CRT_HAVE_atomic_xchl_nopf)
#define __atomic_xchl_nopf_defined
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_xchl_nopf,(void const *__addr, __UINT32_TYPE__ __newval, __UINT32_TYPE__ *__poldval),(__addr,__newval,__poldval))
#endif /* !__atomic_xchl_nopf_defined && __CRT_HAVE_atomic_xchl_nopf */
#if !defined(__atomic_xchq_nopf_defined) && defined(__CRT_HAVE_atomic_xchq_nopf)
#define __atomic_xchq_nopf_defined
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to ATOMIC_XCH  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_xchq_nopf,(void const *__addr, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__poldval),(__addr,__newval,__poldval))
#endif /* !__atomic_xchq_nopf_defined && __CRT_HAVE_atomic_xchq_nopf */
#if !defined(__atomic_fetchaddb_nopf_defined) && defined(__CRT_HAVE_atomic_fetchaddb_nopf)
#define __atomic_fetchaddb_nopf_defined
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to ATOMIC_FETCHADD at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_fetchaddb_nopf,(void const *__addr, __UINT8_TYPE__ __addend, __UINT8_TYPE__ *__poldval),(__addr,__addend,__poldval))
#endif /* !__atomic_fetchaddb_nopf_defined && __CRT_HAVE_atomic_fetchaddb_nopf */
#if !defined(__atomic_fetchaddw_nopf_defined) && defined(__CRT_HAVE_atomic_fetchaddw_nopf)
#define __atomic_fetchaddw_nopf_defined
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to ATOMIC_FETCHADD at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_fetchaddw_nopf,(void const *__addr, __UINT16_TYPE__ __addend, __UINT16_TYPE__ *__poldval),(__addr,__addend,__poldval))
#endif /* !__atomic_fetchaddw_nopf_defined && __CRT_HAVE_atomic_fetchaddw_nopf */
#if !defined(__atomic_fetchaddl_nopf_defined) && defined(__CRT_HAVE_atomic_fetchaddl_nopf)
#define __atomic_fetchaddl_nopf_defined
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to ATOMIC_FETCHADD at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_fetchaddl_nopf,(void const *__addr, __UINT32_TYPE__ __addend, __UINT32_TYPE__ *__poldval),(__addr,__addend,__poldval))
#endif /* !__atomic_fetchaddl_nopf_defined && __CRT_HAVE_atomic_fetchaddl_nopf */
#if !defined(__atomic_fetchaddq_nopf_defined) && defined(__CRT_HAVE_atomic_fetchaddq_nopf)
#define __atomic_fetchaddq_nopf_defined
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to ATOMIC_FETCHADD at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((3)),__BOOL,__NOTHROW,atomic_fetchaddq_nopf,(void const *__addr, __UINT64_TYPE__ __addend, __UINT64_TYPE__ *__poldval),(__addr,__addend,__poldval))
#endif /* !__atomic_fetchaddq_nopf_defined && __CRT_HAVE_atomic_fetchaddq_nopf */
#if !defined(__atomic_orb_nopf_defined) && defined(__CRT_HAVE_atomic_orb_nopf)
#define __atomic_orb_nopf_defined
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orb_nopf,(void *__addr, __UINT8_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_orb_nopf_defined && __CRT_HAVE_atomic_orb_nopf */
#if !defined(__atomic_orw_nopf_defined) && defined(__CRT_HAVE_atomic_orw_nopf)
#define __atomic_orw_nopf_defined
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orw_nopf,(void *__addr, __UINT16_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_orw_nopf_defined && __CRT_HAVE_atomic_orw_nopf */
#if !defined(__atomic_orl_nopf_defined) && defined(__CRT_HAVE_atomic_orl_nopf)
#define __atomic_orl_nopf_defined
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orl_nopf,(void *__addr, __UINT32_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_orl_nopf_defined && __CRT_HAVE_atomic_orl_nopf */
#if !defined(__atomic_orq_nopf_defined) && defined(__CRT_HAVE_atomic_orq_nopf)
#define __atomic_orq_nopf_defined
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orq_nopf,(void *__addr, __UINT64_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_orq_nopf_defined && __CRT_HAVE_atomic_orq_nopf */
#if !defined(__atomic_andb_nopf_defined) && defined(__CRT_HAVE_atomic_andb_nopf)
#define __atomic_andb_nopf_defined
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andb_nopf,(void *__addr, __UINT8_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_andb_nopf_defined && __CRT_HAVE_atomic_andb_nopf */
#if !defined(__atomic_andw_nopf_defined) && defined(__CRT_HAVE_atomic_andw_nopf)
#define __atomic_andw_nopf_defined
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andw_nopf,(void *__addr, __UINT16_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_andw_nopf_defined && __CRT_HAVE_atomic_andw_nopf */
#if !defined(__atomic_andl_nopf_defined) && defined(__CRT_HAVE_atomic_andl_nopf)
#define __atomic_andl_nopf_defined
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andl_nopf,(void *__addr, __UINT32_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_andl_nopf_defined && __CRT_HAVE_atomic_andl_nopf */
#if !defined(__atomic_andq_nopf_defined) && defined(__CRT_HAVE_atomic_andq_nopf)
#define __atomic_andq_nopf_defined
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andq_nopf,(void *__addr, __UINT64_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_andq_nopf_defined && __CRT_HAVE_atomic_andq_nopf */
#if !defined(__atomic_xorb_nopf_defined) && defined(__CRT_HAVE_atomic_xorb_nopf)
#define __atomic_xorb_nopf_defined
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorb_nopf,(void *__addr, __UINT8_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_xorb_nopf_defined && __CRT_HAVE_atomic_xorb_nopf */
#if !defined(__atomic_xorw_nopf_defined) && defined(__CRT_HAVE_atomic_xorw_nopf)
#define __atomic_xorw_nopf_defined
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorw_nopf,(void *__addr, __UINT16_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_xorw_nopf_defined && __CRT_HAVE_atomic_xorw_nopf */
#if !defined(__atomic_xorl_nopf_defined) && defined(__CRT_HAVE_atomic_xorl_nopf)
#define __atomic_xorl_nopf_defined
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorl_nopf,(void *__addr, __UINT32_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_xorl_nopf_defined && __CRT_HAVE_atomic_xorl_nopf */
#if !defined(__atomic_xorq_nopf_defined) && defined(__CRT_HAVE_atomic_xorq_nopf)
#define __atomic_xorq_nopf_defined
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorq_nopf,(void *__addr, __UINT64_TYPE__ __mask),(__addr,__mask))
#endif /* !__atomic_xorq_nopf_defined && __CRT_HAVE_atomic_xorq_nopf */
#if !defined(__atomic_cmpxchb_nopf_defined) && defined(__CRT_HAVE_atomic_cmpxchb_nopf)
#define __atomic_cmpxchb_nopf_defined
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__BOOL,__NOTHROW,atomic_cmpxchb_nopf,(void *__addr, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, __UINT8_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#endif /* !__atomic_cmpxchb_nopf_defined && __CRT_HAVE_atomic_cmpxchb_nopf */
#if !defined(__atomic_cmpxchw_nopf_defined) && defined(__CRT_HAVE_atomic_cmpxchw_nopf)
#define __atomic_cmpxchw_nopf_defined
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__BOOL,__NOTHROW,atomic_cmpxchw_nopf,(void *__addr, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, __UINT16_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#endif /* !__atomic_cmpxchw_nopf_defined && __CRT_HAVE_atomic_cmpxchw_nopf */
#if !defined(__atomic_cmpxchl_nopf_defined) && defined(__CRT_HAVE_atomic_cmpxchl_nopf)
#define __atomic_cmpxchl_nopf_defined
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__BOOL,__NOTHROW,atomic_cmpxchl_nopf,(void *__addr, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, __UINT32_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#endif /* !__atomic_cmpxchl_nopf_defined && __CRT_HAVE_atomic_cmpxchl_nopf */
#if !defined(__atomic_cmpxchq_nopf_defined) && defined(__CRT_HAVE_atomic_cmpxchq_nopf)
#define __atomic_cmpxchq_nopf_defined
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_NONNULL((4)),__BOOL,__NOTHROW,atomic_cmpxchq_nopf,(void *__addr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#endif /* !__atomic_cmpxchq_nopf_defined && __CRT_HAVE_atomic_cmpxchq_nopf */

#ifdef __memcpy_nopf_defined
#ifndef __readb_nopf_defined
#define __readb_nopf_defined 1
#define readb_nopf(addr, presult) (memcpy_nopf(presult, addr, 1) == 0)
#endif /* !__readb_nopf_defined */
#ifndef __readw_nopf_defined
#define __readw_nopf_defined 1
#define readw_nopf(addr, presult) (memcpy_nopf(presult, addr, 2) == 0)
#endif /* !__readw_nopf_defined */
#ifndef __readl_nopf_defined
#define __readl_nopf_defined 1
#define readl_nopf(addr, presult) (memcpy_nopf(presult, addr, 4) == 0)
#endif /* !__readl_nopf_defined */
#ifndef __readq_nopf_defined
#define __readq_nopf_defined 1
#define readq_nopf(addr, presult) (memcpy_nopf(presult, addr, 8) == 0)
#endif /* !__readq_nopf_defined */
#ifdef __NO_XBLOCK
#ifndef __writeb_nopf_defined
#define __writeb_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writeb_nopf)(__USER __CHECKED void *__addr, __uint8_t __val) {
	return memcpy_nopf(__addr, &__val, 1) == 0;
}
#endif /* !__writeb_nopf_defined */
#ifndef __writew_nopf_defined
#define __writew_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writew_nopf)(__USER __CHECKED void *__addr, __uint16_t __val) {
	return memcpy_nopf(__addr, &__val, 2) == 0;
}
#endif /* !__writew_nopf_defined */
#ifndef __writel_nopf_defined
#define __writel_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writel_nopf)(__USER __CHECKED void *__addr, __uint32_t __val) {
	return memcpy_nopf(__addr, &__val, 4) == 0;
}
#endif /* !__writel_nopf_defined */
#ifndef __writeq_nopf_defined
#define __writeq_nopf_defined 1
__FORCELOCAL __NOBLOCK __ATTR_ARTIFICIAL __ATTR_WUNUSED __ATTR_OUT_OPT(1) __BOOL
__NOTHROW(writeq_nopf)(__USER __CHECKED void *__addr, __uint64_t __val) {
	return memcpy_nopf(__addr, &__val, 8) == 0;
}
#endif /* !__writeq_nopf_defined */
#else /* __NO_XBLOCK */
#ifndef __writeb_nopf_defined
#define __writeb_nopf_defined 1
#define writeb_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint8_t __wnpf_val = (val);                     \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 1) == 0; \
	})
#endif /* !__writeb_nopf_defined */
#ifndef __writew_nopf_defined
#define __writew_nopf_defined 1
#define writew_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint16_t __wnpf_val = (val);                    \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 2) == 0; \
	})
#endif /* !__writew_nopf_defined */
#ifndef __writel_nopf_defined
#define __writel_nopf_defined 1
#define writel_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint32_t __wnpf_val = (val);                    \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 4) == 0; \
	})
#endif /* !__writel_nopf_defined */
#ifndef __writeq_nopf_defined
#define __writeq_nopf_defined 1
#define writeq_nopf(addr, val)                            \
	__XBLOCK({                                            \
		__uint64_t __wnpf_val = (val);                    \
		__XRETURN memcpy_nopf(addr, &__wnpf_val, 8) == 0; \
	})
#endif /* !__writeq_nopf_defined */
#endif /* !__NO_XBLOCK */
#endif /* __memcpy_nopf_defined */


/* Type-generic helper macros. */
#if (defined(__readb_nopf_defined) && defined(__readw_nopf_defined) && \
     defined(__readl_nopf_defined) && defined(__readq_nopf_defined))
#define read_nopf(addr, presult)                          \
	(sizeof(*(addr)) == 1                                 \
	 ? readb_nopf(addr, (__UINT8_TYPE__ *)(presult))      \
	 : sizeof(*(addr)) == 2                               \
	   ? readw_nopf(addr, (__UINT16_TYPE__ *)(presult))   \
	   : sizeof(*(addr)) == 4                             \
	     ? readl_nopf(addr, (__UINT32_TYPE__ *)(presult)) \
	     : readq_nopf(addr, (__UINT64_TYPE__ *)(presult)))
#endif /* __read[bwlq]_nopf_defined */
#if (defined(__writeb_nopf_defined) && defined(__writew_nopf_defined) && \
     defined(__writel_nopf_defined) && defined(__writeq_nopf_defined))
#define write_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                              \
	 ? writeb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                            \
	   ? writew_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                          \
	     ? writel_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : writeq_nopf(addr, (__UINT64_TYPE__)(value)))
#endif /* __write[bwlq]_nopf_defined */

#if (defined(__atomic_cmpxchb_nopf_defined) && defined(__atomic_cmpxchw_nopf_defined) && \
     defined(__atomic_cmpxchl_nopf_defined) && defined(__atomic_cmpxchq_nopf_defined))
#define atomic_cmpxch_nopf(addr, oldval, newval, preal_oldval)                                                                \
	(sizeof(*(addr)) == 1                                                                                                     \
	 ? atomic_cmpxchb_nopf(addr, (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(preal_oldval))        \
	 : sizeof(*(addr)) == 2                                                                                                   \
	   ? atomic_cmpxchw_nopf(addr, (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(preal_oldval))   \
	   : sizeof(*(addr)) == 4                                                                                                 \
	     ? atomic_cmpxchl_nopf(addr, (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(preal_oldval)) \
	     : atomic_cmpxchq_nopf(addr, (__UINT64_TYPE__)(oldval), (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(preal_oldval)))
#elif (defined(__atomic_cmpxchb_nopf_defined) && defined(__atomic_cmpxchw_nopf_defined) && defined(__atomic_cmpxchl_nopf_defined))
#define atomic_cmpxch_nopf(addr, oldval, newval, preal_oldval)                                                              \
	(sizeof(*(addr)) == 1                                                                                                   \
	 ? atomic_cmpxchb_nopf(addr, (__UINT8_TYPE__)(oldval), (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(preal_oldval))      \
	 : sizeof(*(addr)) == 2                                                                                                 \
	   ? atomic_cmpxchw_nopf(addr, (__UINT16_TYPE__)(oldval), (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(preal_oldval)) \
	   : atomic_cmpxchl_nopf(addr, (__UINT32_TYPE__)(oldval), (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(preal_oldval)))
#endif /* ... */

#if (defined(__atomic_xchb_nopf_defined) && defined(__atomic_xchw_nopf_defined) && \
     defined(__atomic_xchl_nopf_defined) && defined(__atomic_xchq_nopf_defined))
#define atomic_xch_nopf(addr, newval, poldval)                                             \
	(sizeof(*(addr)) == 1                                                                  \
	 ? atomic_xchb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))       \
	 : sizeof(*(addr)) == 2                                                                \
	   ? atomic_xchw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval))   \
	   : sizeof(*(addr)) == 4                                                              \
	     ? atomic_xchl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)) \
	     : atomic_xchq_nopf(addr, (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(poldval)))
#elif (defined(__atomic_xchb_nopf_defined) && defined(__atomic_xchw_nopf_defined) && defined(__atomic_xchl_nopf_defined))
#define atomic_xch_nopf(addr, newval, poldval)                                           \
	(sizeof(*(addr)) == 1                                                                \
	 ? atomic_xchb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))     \
	 : sizeof(*(addr)) == 2                                                              \
	   ? atomic_xchw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval)) \
	   : atomic_xchl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)))
#endif /* ... */

#if (defined(__atomic_fetchaddb_nopf_defined) && defined(__atomic_fetchaddw_nopf_defined) && \
     defined(__atomic_fetchaddl_nopf_defined) && defined(__atomic_fetchaddq_nopf_defined))
#define atomic_fetchadd_nopf(addr, newval, poldval)                                             \
	(sizeof(*(addr)) == 1                                                                       \
	 ? atomic_fetchaddb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))       \
	 : sizeof(*(addr)) == 2                                                                     \
	   ? atomic_fetchaddw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval))   \
	   : sizeof(*(addr)) == 4                                                                   \
	     ? atomic_fetchaddl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)) \
	     : atomic_fetchaddq_nopf(addr, (__UINT64_TYPE__)(newval), (__UINT64_TYPE__ *)(poldval)))
#elif (defined(__atomic_fetchaddb_nopf_defined) && defined(__atomic_fetchaddw_nopf_defined) && defined(__atomic_fetchaddl_nopf_defined))
#define atomic_fetchadd_nopf(addr, newval, poldval)                                           \
	(sizeof(*(addr)) == 1                                                                     \
	 ? atomic_fetchaddb_nopf(addr, (__UINT8_TYPE__)(newval), (__UINT8_TYPE__ *)(poldval))     \
	 : sizeof(*(addr)) == 2                                                                   \
	   ? atomic_fetchaddw_nopf(addr, (__UINT16_TYPE__)(newval), (__UINT16_TYPE__ *)(poldval)) \
	   : atomic_fetchaddl_nopf(addr, (__UINT32_TYPE__)(newval), (__UINT32_TYPE__ *)(poldval)))
#endif /* ... */

#if (defined(__atomic_orb_nopf_defined) && defined(__atomic_orw_nopf_defined) && \
     defined(__atomic_orl_nopf_defined) && defined(__atomic_orq_nopf_defined))
#define atomic_or_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                  \
	 ? atomic_orb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                \
	   ? atomic_orw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                              \
	     ? atomic_orl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_orq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif (defined(__atomic_orb_nopf_defined) && defined(__atomic_orw_nopf_defined) && defined(__atomic_orl_nopf_defined))
#define atomic_or_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                \
	 ? atomic_orb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                              \
	   ? atomic_orw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_orl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#if (defined(__atomic_andb_nopf_defined) && defined(__atomic_andw_nopf_defined) && \
     defined(__atomic_andl_nopf_defined) && defined(__atomic_andq_nopf_defined))
#define atomic_and_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                   \
	 ? atomic_andb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                 \
	   ? atomic_andw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                               \
	     ? atomic_andl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_andq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif (defined(__atomic_andb_nopf_defined) && defined(__atomic_andw_nopf_defined) && defined(__atomic_andl_nopf_defined))
#define atomic_and_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                 \
	 ? atomic_andb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                               \
	   ? atomic_andw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_andl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

#if (defined(__atomic_xorb_nopf_defined) && defined(__atomic_xorw_nopf_defined) && \
     defined(__atomic_xorl_nopf_defined) && defined(__atomic_xorq_nopf_defined))
#define atomic_xor_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                                   \
	 ? atomic_xorb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                                 \
	   ? atomic_xorw_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                               \
	     ? atomic_xorl_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : atomic_xorq_nopf(addr, (__UINT64_TYPE__)(value)))
#elif (defined(__atomic_xorb_nopf_defined) && defined(__atomic_xorw_nopf_defined) && defined(__atomic_xorl_nopf_defined))
#define atomic_xor_nopf(addr, value)                      \
	(sizeof(*(addr)) == 1                                 \
	 ? atomic_xorb_nopf(addr, (__UINT8_TYPE__)(value))    \
	 : sizeof(*(addr)) == 2                               \
	   ? atomic_xorw_nopf(addr, (__UINT16_TYPE__)(value)) \
	   : atomic_xorl_nopf(addr, (__UINT32_TYPE__)(value)))
#endif /* ... */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_NOPF_H */
