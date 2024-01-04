/* HASH CRC-32:0x41590c4b */
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

/* Define nopf functions */

#ifdef __arch_readb_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define readb_nopf(addr, presult) __arch_readb_nopf(addr, presult)
#elif defined(__CRT_HAVE_readb_nopf)
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,readb_nopf,(void const *__addr, __UINT8_TYPE__ *__presult),(__addr,__presult))
#elif defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)
#include <libc/local/kos.nopf/readb_nopf.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(readb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL readb_nopf)(void const *__addr, __UINT8_TYPE__ *__presult) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readb_nopf))(__addr, __presult); })
#endif /* ... */
#ifdef __arch_readw_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define readw_nopf(addr, presult) __arch_readw_nopf(addr, presult)
#elif defined(__CRT_HAVE_readw_nopf)
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,readw_nopf,(void const *__addr, __UINT16_TYPE__ *__presult),(__addr,__presult))
#elif defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
#include <libc/local/kos.nopf/readw_nopf.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(readw_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL readw_nopf)(void const *__addr, __UINT16_TYPE__ *__presult) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readw_nopf))(__addr, __presult); })
#endif /* ... */
#ifdef __arch_readl_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define readl_nopf(addr, presult) __arch_readl_nopf(addr, presult)
#elif defined(__CRT_HAVE_readl_nopf)
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,readl_nopf,(void const *__addr, __UINT32_TYPE__ *__presult),(__addr,__presult))
#elif defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
#include <libc/local/kos.nopf/readl_nopf.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(readl_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL readl_nopf)(void const *__addr, __UINT32_TYPE__ *__presult) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readl_nopf))(__addr, __presult); })
#endif /* ... */
#ifdef __arch_readq_nopf
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
#define readq_nopf(addr, presult) __arch_readq_nopf(addr, presult)
#elif defined(__CRT_HAVE_readq_nopf)
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2),__BOOL,__NOTHROW,readq_nopf,(void const *__addr, __UINT64_TYPE__ *__presult),(__addr,__presult))
#elif defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
#include <libc/local/kos.nopf/readq_nopf.h>
/* >> read[bwlq]_nopf(3)
 * Try to read from a possibly faulty `addr' into `*presult'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(readq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_IN_OPT(1) __ATTR_OUT(2) __BOOL __NOTHROW(__LIBCCALL readq_nopf)(void const *__addr, __UINT64_TYPE__ *__presult) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readq_nopf))(__addr, __presult); })
#endif /* ... */
#ifdef __arch_writeb_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define writeb_nopf(addr, val) __arch_writeb_nopf(addr, val)
#elif defined(__CRT_HAVE_writeb_nopf)
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writeb_nopf,(void *__addr, __UINT8_TYPE__ __val),(__addr,__val))
#elif defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
#include <libc/local/kos.nopf/writeb_nopf.h>
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__NAMESPACE_LOCAL_USING_OR_IMPL(writeb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL writeb_nopf)(void *__addr, __UINT8_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writeb_nopf))(__addr, __val); })
#endif /* ... */
#ifdef __arch_writew_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define writew_nopf(addr, val) __arch_writew_nopf(addr, val)
#elif defined(__CRT_HAVE_writew_nopf)
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writew_nopf,(void *__addr, __UINT16_TYPE__ __val),(__addr,__val))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf))
#include <libc/local/kos.nopf/writew_nopf.h>
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__NAMESPACE_LOCAL_USING_OR_IMPL(writew_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL writew_nopf)(void *__addr, __UINT16_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writew_nopf))(__addr, __val); })
#endif /* ... */
#ifdef __arch_writel_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define writel_nopf(addr, val) __arch_writel_nopf(addr, val)
#elif defined(__CRT_HAVE_writel_nopf)
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writel_nopf,(void *__addr, __UINT32_TYPE__ __val),(__addr,__val))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_writew_nopf) || defined(__CRT_HAVE_writew_nopf) || defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf))
#include <libc/local/kos.nopf/writel_nopf.h>
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__NAMESPACE_LOCAL_USING_OR_IMPL(writel_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL writel_nopf)(void *__addr, __UINT32_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writel_nopf))(__addr, __val); })
#endif /* ... */
#ifdef __arch_writeq_nopf
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
#define writeq_nopf(addr, val) __arch_writeq_nopf(addr, val)
#elif defined(__CRT_HAVE_writeq_nopf)
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1),__BOOL,__NOTHROW,writeq_nopf,(void *__addr, __UINT64_TYPE__ __val),(__addr,__val))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_writel_nopf) || defined(__CRT_HAVE_writel_nopf) || defined(__arch_writew_nopf) || defined(__CRT_HAVE_writew_nopf) || defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf))
#include <libc/local/kos.nopf/writeq_nopf.h>
/* >> write[bwlq]_nopf(3)
 * Try to write `val' into a possibly faulty `addr'
 * Return  `true'  on  success,  `false'  on  error */
__NAMESPACE_LOCAL_USING_OR_IMPL(writeq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_OUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL writeq_nopf)(void *__addr, __UINT64_TYPE__ __val) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(writeq_nopf))(__addr, __val); })
#endif /* ... */
#ifdef __arch_memcpy_nopf
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
#define memcpy_nopf(dst, src, num_bytes) __arch_memcpy_nopf(dst, src, num_bytes)
#elif defined(__CRT_HAVE_memcpy_nopf)
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
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf))
#include <libc/local/kos.nopf/memcpy_nopf.h>
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
__NAMESPACE_LOCAL_USING_OR_IMPL(memcpy_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INS(2, 3) __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW(__LIBCCALL memcpy_nopf)(void *__dst, void const *__src, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memcpy_nopf))(__dst, __src, __num_bytes); })
#endif /* ... */
#ifdef __arch_memset_nopf
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
#define memset_nopf(dst, byte, num_bytes) __arch_memset_nopf(dst, byte, num_bytes)
#elif defined(__CRT_HAVE_memset_nopf)
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_OUTS(1, 3),__SIZE_TYPE__,__NOTHROW,memset_nopf,(void *__dst, int __byte, __SIZE_TYPE__ __num_bytes),(__dst,__byte,__num_bytes))
#elif defined(__arch_writeb_nopf) || defined(__CRT_HAVE_writeb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)
#include <libc/local/kos.nopf/memset_nopf.h>
/* >> memset_nopf(3)
 * @return: * : The # of bytes that could not be accessed */
__NAMESPACE_LOCAL_USING_OR_IMPL(memset_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_OUTS(1, 3) __SIZE_TYPE__ __NOTHROW(__LIBCCALL memset_nopf)(void *__dst, int __byte, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memset_nopf))(__dst, __byte, __num_bytes); })
#endif /* ... */
#ifdef __arch_nopf_memeq
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
#define memeq_nopf(lhs, rhs, num_bytes) __arch_nopf_memeq(lhs, rhs, num_bytes)
#elif defined(__CRT_HAVE_memeq_nopf)
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INS(1, 3) __ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW,memeq_nopf,(void const *__lhs, void const *__rhs, __SIZE_TYPE__ __num_bytes),(__lhs,__rhs,__num_bytes))
#elif defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)
#include <libc/local/kos.nopf/memeq_nopf.h>
/* >> memeq_nopf(3)
 * Compare the data pointed to by 2 potentially faulty memory buffers.
 * @return: >0: The contents of the 2 buffers differ from each other.
 * @return:  0: The contents of the 2 buffers are identical.
 * @return: <0: At least one of the 2 buffers is faulty. */
__NAMESPACE_LOCAL_USING_OR_IMPL(memeq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INS(1, 3) __ATTR_INS(2, 3) __SSIZE_TYPE__ __NOTHROW(__LIBCCALL memeq_nopf)(void const *__lhs, void const *__rhs, __SIZE_TYPE__ __num_bytes) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(memeq_nopf))(__lhs, __rhs, __num_bytes); })
#endif /* ... */
#ifndef __atomic_xchb_nopf_defined
#define __atomic_xchb_nopf_defined
#ifdef __arch_atomic_xchb_nopf
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define atomic_xchb_nopf(addr, newval, poldval) __arch_atomic_xchb_nopf(addr, newval, poldval)
#elif defined(__CRT_HAVE_atomic_xchb_nopf)
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_xchb_nopf,(void *__addr, __UINT8_TYPE__ __newval, __UINT8_TYPE__ *__poldval),(__addr,__newval,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_atomic_cmpxchb_nopf) || defined(__CRT_HAVE_atomic_cmpxchb_nopf))
#include <libc/local/kos.nopf/atomic_xchb_nopf.h>
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xchb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_xchb_nopf)(void *__addr, __UINT8_TYPE__ __newval, __UINT8_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xchb_nopf))(__addr, __newval, __poldval); })
#else /* ... */
#undef __atomic_xchb_nopf_defined
#endif /* !... */
#endif /* !__atomic_xchb_nopf_defined */
#ifndef __atomic_xchw_nopf_defined
#define __atomic_xchw_nopf_defined
#ifdef __arch_atomic_xchw_nopf
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define atomic_xchw_nopf(addr, newval, poldval) __arch_atomic_xchw_nopf(addr, newval, poldval)
#elif defined(__CRT_HAVE_atomic_xchw_nopf)
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_xchw_nopf,(void *__addr, __UINT16_TYPE__ __newval, __UINT16_TYPE__ *__poldval),(__addr,__newval,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchw_nopf) || defined(__CRT_HAVE_atomic_cmpxchw_nopf))
#include <libc/local/kos.nopf/atomic_xchw_nopf.h>
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xchw_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_xchw_nopf)(void *__addr, __UINT16_TYPE__ __newval, __UINT16_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xchw_nopf))(__addr, __newval, __poldval); })
#else /* ... */
#undef __atomic_xchw_nopf_defined
#endif /* !... */
#endif /* !__atomic_xchw_nopf_defined */
#ifndef __atomic_xchl_nopf_defined
#define __atomic_xchl_nopf_defined
#ifdef __arch_atomic_xchl_nopf
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define atomic_xchl_nopf(addr, newval, poldval) __arch_atomic_xchl_nopf(addr, newval, poldval)
#elif defined(__CRT_HAVE_atomic_xchl_nopf)
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_xchl_nopf,(void *__addr, __UINT32_TYPE__ __newval, __UINT32_TYPE__ *__poldval),(__addr,__newval,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchl_nopf) || defined(__CRT_HAVE_atomic_cmpxchl_nopf))
#include <libc/local/kos.nopf/atomic_xchl_nopf.h>
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xchl_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_xchl_nopf)(void *__addr, __UINT32_TYPE__ __newval, __UINT32_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xchl_nopf))(__addr, __newval, __poldval); })
#else /* ... */
#undef __atomic_xchl_nopf_defined
#endif /* !... */
#endif /* !__atomic_xchl_nopf_defined */
#ifndef __atomic_xchq_nopf_defined
#define __atomic_xchq_nopf_defined
#ifdef __arch_atomic_xchq_nopf
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
#define atomic_xchq_nopf(addr, newval, poldval) __arch_atomic_xchq_nopf(addr, newval, poldval)
#elif defined(__CRT_HAVE_atomic_xchq_nopf)
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_xchq_nopf,(void *__addr, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__poldval),(__addr,__newval,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchq_nopf) || defined(__CRT_HAVE_atomic_cmpxchq_nopf))
#include <libc/local/kos.nopf/atomic_xchq_nopf.h>
/* >> atomic_xch[bwlq]_nopf(3)
 * Try  to atomic_xch  at a  possibly faulty  `addr', storing the
 * old value in `*poldval', and loading a new value from `newval'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xchq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_xchq_nopf)(void *__addr, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xchq_nopf))(__addr, __newval, __poldval); })
#else /* ... */
#undef __atomic_xchq_nopf_defined
#endif /* !... */
#endif /* !__atomic_xchq_nopf_defined */
#ifndef __atomic_fetchaddb_nopf_defined
#define __atomic_fetchaddb_nopf_defined
#ifdef __arch_atomic_fetchaddb_nopf
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
#define atomic_fetchaddb_nopf(addr, addend, poldval) __arch_atomic_fetchaddb_nopf(addr, addend, poldval)
#elif defined(__CRT_HAVE_atomic_fetchaddb_nopf)
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_fetchaddb_nopf,(void *__addr, __UINT8_TYPE__ __addend, __UINT8_TYPE__ *__poldval),(__addr,__addend,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_atomic_cmpxchb_nopf) || defined(__CRT_HAVE_atomic_cmpxchb_nopf))
#include <libc/local/kos.nopf/atomic_fetchaddb_nopf.h>
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_fetchaddb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_fetchaddb_nopf)(void *__addr, __UINT8_TYPE__ __addend, __UINT8_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_fetchaddb_nopf))(__addr, __addend, __poldval); })
#else /* ... */
#undef __atomic_fetchaddb_nopf_defined
#endif /* !... */
#endif /* !__atomic_fetchaddb_nopf_defined */
#ifndef __atomic_fetchaddw_nopf_defined
#define __atomic_fetchaddw_nopf_defined
#ifdef __arch_atomic_fetchaddw_nopf
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
#define atomic_fetchaddw_nopf(addr, addend, poldval) __arch_atomic_fetchaddw_nopf(addr, addend, poldval)
#elif defined(__CRT_HAVE_atomic_fetchaddw_nopf)
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_fetchaddw_nopf,(void *__addr, __UINT16_TYPE__ __addend, __UINT16_TYPE__ *__poldval),(__addr,__addend,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchw_nopf) || defined(__CRT_HAVE_atomic_cmpxchw_nopf))
#include <libc/local/kos.nopf/atomic_fetchaddw_nopf.h>
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_fetchaddw_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_fetchaddw_nopf)(void *__addr, __UINT16_TYPE__ __addend, __UINT16_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_fetchaddw_nopf))(__addr, __addend, __poldval); })
#else /* ... */
#undef __atomic_fetchaddw_nopf_defined
#endif /* !... */
#endif /* !__atomic_fetchaddw_nopf_defined */
#ifndef __atomic_fetchaddl_nopf_defined
#define __atomic_fetchaddl_nopf_defined
#ifdef __arch_atomic_fetchaddl_nopf
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
#define atomic_fetchaddl_nopf(addr, addend, poldval) __arch_atomic_fetchaddl_nopf(addr, addend, poldval)
#elif defined(__CRT_HAVE_atomic_fetchaddl_nopf)
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_fetchaddl_nopf,(void *__addr, __UINT32_TYPE__ __addend, __UINT32_TYPE__ *__poldval),(__addr,__addend,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchl_nopf) || defined(__CRT_HAVE_atomic_cmpxchl_nopf))
#include <libc/local/kos.nopf/atomic_fetchaddl_nopf.h>
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_fetchaddl_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_fetchaddl_nopf)(void *__addr, __UINT32_TYPE__ __addend, __UINT32_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_fetchaddl_nopf))(__addr, __addend, __poldval); })
#else /* ... */
#undef __atomic_fetchaddl_nopf_defined
#endif /* !... */
#endif /* !__atomic_fetchaddl_nopf_defined */
#ifndef __atomic_fetchaddq_nopf_defined
#define __atomic_fetchaddq_nopf_defined
#ifdef __arch_atomic_fetchaddq_nopf
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
#define atomic_fetchaddq_nopf(addr, addend, poldval) __arch_atomic_fetchaddq_nopf(addr, addend, poldval)
#elif defined(__CRT_HAVE_atomic_fetchaddq_nopf)
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3),__BOOL,__NOTHROW,atomic_fetchaddq_nopf,(void *__addr, __UINT64_TYPE__ __addend, __UINT64_TYPE__ *__poldval),(__addr,__addend,__poldval))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchq_nopf) || defined(__CRT_HAVE_atomic_cmpxchq_nopf))
#include <libc/local/kos.nopf/atomic_fetchaddq_nopf.h>
/* >> atomic_fetchadd[bwlq]_nopf(3)
 * Try to atomic_fetchadd at a possibly faulty `addr', storing  the
 * old value in `*poldval', and adding `newval' onto the stored val
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_fetchaddq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(3) __BOOL __NOTHROW(__LIBCCALL atomic_fetchaddq_nopf)(void *__addr, __UINT64_TYPE__ __addend, __UINT64_TYPE__ *__poldval) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_fetchaddq_nopf))(__addr, __addend, __poldval); })
#else /* ... */
#undef __atomic_fetchaddq_nopf_defined
#endif /* !... */
#endif /* !__atomic_fetchaddq_nopf_defined */
#ifndef __atomic_orb_nopf_defined
#define __atomic_orb_nopf_defined
#ifdef __arch_atomic_orb_nopf
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_orb_nopf(addr, mask) __arch_atomic_orb_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_orb_nopf)
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orb_nopf,(void *__addr, __UINT8_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_atomic_cmpxchb_nopf) || defined(__CRT_HAVE_atomic_cmpxchb_nopf))
#include <libc/local/kos.nopf/atomic_orb_nopf.h>
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_orb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_orb_nopf)(void *__addr, __UINT8_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_orb_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_orb_nopf_defined
#endif /* !... */
#endif /* !__atomic_orb_nopf_defined */
#ifndef __atomic_orw_nopf_defined
#define __atomic_orw_nopf_defined
#ifdef __arch_atomic_orw_nopf
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_orw_nopf(addr, mask) __arch_atomic_orw_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_orw_nopf)
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orw_nopf,(void *__addr, __UINT16_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchw_nopf) || defined(__CRT_HAVE_atomic_cmpxchw_nopf))
#include <libc/local/kos.nopf/atomic_orw_nopf.h>
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_orw_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_orw_nopf)(void *__addr, __UINT16_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_orw_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_orw_nopf_defined
#endif /* !... */
#endif /* !__atomic_orw_nopf_defined */
#ifndef __atomic_orl_nopf_defined
#define __atomic_orl_nopf_defined
#ifdef __arch_atomic_orl_nopf
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_orl_nopf(addr, mask) __arch_atomic_orl_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_orl_nopf)
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orl_nopf,(void *__addr, __UINT32_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchl_nopf) || defined(__CRT_HAVE_atomic_cmpxchl_nopf))
#include <libc/local/kos.nopf/atomic_orl_nopf.h>
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_orl_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_orl_nopf)(void *__addr, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_orl_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_orl_nopf_defined
#endif /* !... */
#endif /* !__atomic_orl_nopf_defined */
#ifndef __atomic_orq_nopf_defined
#define __atomic_orq_nopf_defined
#ifdef __arch_atomic_orq_nopf
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_orq_nopf(addr, mask) __arch_atomic_orq_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_orq_nopf)
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_orq_nopf,(void *__addr, __UINT64_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchq_nopf) || defined(__CRT_HAVE_atomic_cmpxchq_nopf))
#include <libc/local/kos.nopf/atomic_orq_nopf.h>
/* >> atomic_or[bwlq]_nopf(3)
 * Try to atomically turn on all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_orq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_orq_nopf)(void *__addr, __UINT64_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_orq_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_orq_nopf_defined
#endif /* !... */
#endif /* !__atomic_orq_nopf_defined */
#ifndef __atomic_andb_nopf_defined
#define __atomic_andb_nopf_defined
#ifdef __arch_atomic_andb_nopf
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_andb_nopf(addr, mask) __arch_atomic_andb_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_andb_nopf)
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andb_nopf,(void *__addr, __UINT8_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_atomic_cmpxchb_nopf) || defined(__CRT_HAVE_atomic_cmpxchb_nopf))
#include <libc/local/kos.nopf/atomic_andb_nopf.h>
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_andb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_andb_nopf)(void *__addr, __UINT8_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_andb_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_andb_nopf_defined
#endif /* !... */
#endif /* !__atomic_andb_nopf_defined */
#ifndef __atomic_andw_nopf_defined
#define __atomic_andw_nopf_defined
#ifdef __arch_atomic_andw_nopf
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_andw_nopf(addr, mask) __arch_atomic_andw_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_andw_nopf)
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andw_nopf,(void *__addr, __UINT16_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchw_nopf) || defined(__CRT_HAVE_atomic_cmpxchw_nopf))
#include <libc/local/kos.nopf/atomic_andw_nopf.h>
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_andw_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_andw_nopf)(void *__addr, __UINT16_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_andw_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_andw_nopf_defined
#endif /* !... */
#endif /* !__atomic_andw_nopf_defined */
#ifndef __atomic_andl_nopf_defined
#define __atomic_andl_nopf_defined
#ifdef __arch_atomic_andl_nopf
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_andl_nopf(addr, mask) __arch_atomic_andl_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_andl_nopf)
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andl_nopf,(void *__addr, __UINT32_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchl_nopf) || defined(__CRT_HAVE_atomic_cmpxchl_nopf))
#include <libc/local/kos.nopf/atomic_andl_nopf.h>
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_andl_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_andl_nopf)(void *__addr, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_andl_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_andl_nopf_defined
#endif /* !... */
#endif /* !__atomic_andl_nopf_defined */
#ifndef __atomic_andq_nopf_defined
#define __atomic_andq_nopf_defined
#ifdef __arch_atomic_andq_nopf
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_andq_nopf(addr, mask) __arch_atomic_andq_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_andq_nopf)
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_andq_nopf,(void *__addr, __UINT64_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchq_nopf) || defined(__CRT_HAVE_atomic_cmpxchq_nopf))
#include <libc/local/kos.nopf/atomic_andq_nopf.h>
/* >> atomic_and[bwlq]_nopf(3)
 * Try to atomically mask all bits with `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_andq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_andq_nopf)(void *__addr, __UINT64_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_andq_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_andq_nopf_defined
#endif /* !... */
#endif /* !__atomic_andq_nopf_defined */
#ifndef __atomic_xorb_nopf_defined
#define __atomic_xorb_nopf_defined
#ifdef __arch_atomic_xorb_nopf
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_xorb_nopf(addr, mask) __arch_atomic_xorb_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_xorb_nopf)
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorb_nopf,(void *__addr, __UINT8_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf)) && (defined(__arch_atomic_cmpxchb_nopf) || defined(__CRT_HAVE_atomic_cmpxchb_nopf))
#include <libc/local/kos.nopf/atomic_xorb_nopf.h>
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xorb_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_xorb_nopf)(void *__addr, __UINT8_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xorb_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_xorb_nopf_defined
#endif /* !... */
#endif /* !__atomic_xorb_nopf_defined */
#ifndef __atomic_xorw_nopf_defined
#define __atomic_xorw_nopf_defined
#ifdef __arch_atomic_xorw_nopf
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_xorw_nopf(addr, mask) __arch_atomic_xorw_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_xorw_nopf)
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorw_nopf,(void *__addr, __UINT16_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchw_nopf) || defined(__CRT_HAVE_atomic_cmpxchw_nopf))
#include <libc/local/kos.nopf/atomic_xorw_nopf.h>
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xorw_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_xorw_nopf)(void *__addr, __UINT16_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xorw_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_xorw_nopf_defined
#endif /* !... */
#endif /* !__atomic_xorw_nopf_defined */
#ifndef __atomic_xorl_nopf_defined
#define __atomic_xorl_nopf_defined
#ifdef __arch_atomic_xorl_nopf
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_xorl_nopf(addr, mask) __arch_atomic_xorl_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_xorl_nopf)
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorl_nopf,(void *__addr, __UINT32_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchl_nopf) || defined(__CRT_HAVE_atomic_cmpxchl_nopf))
#include <libc/local/kos.nopf/atomic_xorl_nopf.h>
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xorl_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_xorl_nopf)(void *__addr, __UINT32_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xorl_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_xorl_nopf_defined
#endif /* !... */
#endif /* !__atomic_xorl_nopf_defined */
#ifndef __atomic_xorq_nopf_defined
#define __atomic_xorq_nopf_defined
#ifdef __arch_atomic_xorq_nopf
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_xorq_nopf(addr, mask) __arch_atomic_xorq_nopf(addr, mask)
#elif defined(__CRT_HAVE_atomic_xorq_nopf)
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1),__BOOL,__NOTHROW,atomic_xorq_nopf,(void *__addr, __UINT64_TYPE__ __mask),(__addr,__mask))
#elif (defined(__arch_readb_nopf) || defined(__CRT_HAVE_readb_nopf) || defined(__arch_readw_nopf) || defined(__CRT_HAVE_readw_nopf) || defined(__arch_readl_nopf) || defined(__CRT_HAVE_readl_nopf) || defined(__arch_readq_nopf) || defined(__CRT_HAVE_readq_nopf) || defined(__arch_memcpy_nopf) || defined(__CRT_HAVE_memcpy_nopf)) && (defined(__arch_atomic_cmpxchq_nopf) || defined(__CRT_HAVE_atomic_cmpxchq_nopf))
#include <libc/local/kos.nopf/atomic_xorq_nopf.h>
/* >> atomic_xor[bwlq]_nopf(3)
 * Try to atomically flip all bits from `mask' at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__NAMESPACE_LOCAL_USING_OR_IMPL(atomic_xorq_nopf, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __BOOL __NOTHROW(__LIBCCALL atomic_xorq_nopf)(void *__addr, __UINT64_TYPE__ __mask) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(atomic_xorq_nopf))(__addr, __mask); })
#else /* ... */
#undef __atomic_xorq_nopf_defined
#endif /* !... */
#endif /* !__atomic_xorq_nopf_defined */
#ifndef __atomic_cmpxchb_nopf_defined
#define __atomic_cmpxchb_nopf_defined
#ifdef __arch_atomic_cmpxchb_nopf
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_cmpxchb_nopf(addr, oldval, newval, preal_oldval) __arch_atomic_cmpxchb_nopf(addr, oldval, newval, preal_oldval)
#elif defined(__CRT_HAVE_atomic_cmpxchb_nopf)
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(4),__BOOL,__NOTHROW,atomic_cmpxchb_nopf,(void *__addr, __UINT8_TYPE__ __oldval, __UINT8_TYPE__ __newval, __UINT8_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#else /* ... */
#undef __atomic_cmpxchb_nopf_defined
#endif /* !... */
#endif /* !__atomic_cmpxchb_nopf_defined */
#ifndef __atomic_cmpxchw_nopf_defined
#define __atomic_cmpxchw_nopf_defined
#ifdef __arch_atomic_cmpxchw_nopf
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_cmpxchw_nopf(addr, oldval, newval, preal_oldval) __arch_atomic_cmpxchw_nopf(addr, oldval, newval, preal_oldval)
#elif defined(__CRT_HAVE_atomic_cmpxchw_nopf)
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(4),__BOOL,__NOTHROW,atomic_cmpxchw_nopf,(void *__addr, __UINT16_TYPE__ __oldval, __UINT16_TYPE__ __newval, __UINT16_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#else /* ... */
#undef __atomic_cmpxchw_nopf_defined
#endif /* !... */
#endif /* !__atomic_cmpxchw_nopf_defined */
#ifndef __atomic_cmpxchl_nopf_defined
#define __atomic_cmpxchl_nopf_defined
#ifdef __arch_atomic_cmpxchl_nopf
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_cmpxchl_nopf(addr, oldval, newval, preal_oldval) __arch_atomic_cmpxchl_nopf(addr, oldval, newval, preal_oldval)
#elif defined(__CRT_HAVE_atomic_cmpxchl_nopf)
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(4),__BOOL,__NOTHROW,atomic_cmpxchl_nopf,(void *__addr, __UINT32_TYPE__ __oldval, __UINT32_TYPE__ __newval, __UINT32_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#else /* ... */
#undef __atomic_cmpxchl_nopf_defined
#endif /* !... */
#endif /* !__atomic_cmpxchl_nopf_defined */
#ifndef __atomic_cmpxchq_nopf_defined
#define __atomic_cmpxchq_nopf_defined
#ifdef __arch_atomic_cmpxchq_nopf
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
#define atomic_cmpxchq_nopf(addr, oldval, newval, preal_oldval) __arch_atomic_cmpxchq_nopf(addr, oldval, newval, preal_oldval)
#elif defined(__CRT_HAVE_atomic_cmpxchq_nopf)
/* >> atomic_cmpxch[bwlq]_nopf(3)
 * Try to do an atomic-compare-exchange at the possibly faulty `addr'
 * Return `true' on success, `false' on fault */
__CDECLARE(__ATTR_WUNUSED __NOBLOCK __ATTR_INOUT_OPT(1) __ATTR_OUT(4),__BOOL,__NOTHROW,atomic_cmpxchq_nopf,(void *__addr, __UINT64_TYPE__ __oldval, __UINT64_TYPE__ __newval, __UINT64_TYPE__ *__preal_oldval),(__addr,__oldval,__newval,__preal_oldval))
#else /* ... */
#undef __atomic_cmpxchq_nopf_defined
#endif /* !... */
#endif /* !__atomic_cmpxchq_nopf_defined */
#ifdef __arch_insb_nopf
#define insb_nopf __arch_insb_nopf
#endif /* __arch_insb_nopf */
#ifdef __arch_insw_nopf
#define insw_nopf __arch_insw_nopf
#endif /* __arch_insw_nopf */
#ifdef __arch_insl_nopf
#define insl_nopf __arch_insl_nopf
#endif /* __arch_insl_nopf */
#ifdef __arch_outsb_nopf
#define outsb_nopf __arch_outsb_nopf
#endif /* __arch_outsb_nopf */
#ifdef __arch_outsw_nopf
#define outsw_nopf __arch_outsw_nopf
#endif /* __arch_outsw_nopf */
#ifdef __arch_outsl_nopf
#define outsl_nopf __arch_outsl_nopf
#endif /* __arch_outsl_nopf */

/* Type-generic helper macros. */
#define read_nopf(addr, presult)                          \
	(sizeof(*(addr)) == 1                                 \
	 ? readb_nopf(addr, (__UINT8_TYPE__ *)(presult))      \
	 : sizeof(*(addr)) == 2                               \
	   ? readw_nopf(addr, (__UINT16_TYPE__ *)(presult))   \
	   : sizeof(*(addr)) == 4                             \
	     ? readl_nopf(addr, (__UINT32_TYPE__ *)(presult)) \
	     : readq_nopf(addr, (__UINT64_TYPE__ *)(presult)))
#define write_nopf(addr, value)                        \
	(sizeof(*(addr)) == 1                              \
	 ? writeb_nopf(addr, (__UINT8_TYPE__)(value))      \
	 : sizeof(*(addr)) == 2                            \
	   ? writew_nopf(addr, (__UINT16_TYPE__)(value))   \
	   : sizeof(*(addr)) == 4                          \
	     ? writel_nopf(addr, (__UINT32_TYPE__)(value)) \
	     : writeq_nopf(addr, (__UINT64_TYPE__)(value)))

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
